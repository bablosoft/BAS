#include "httpclient.h"
#include <QDateTime>
#include <QNetworkProxy>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QFile>
#include <QImage>
#include <QFileInfo>
#include <QBuffer>
#include "networkcookiejar.h"
#include <QSslConfiguration>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    HttpClient::HttpClient(QObject *parent) :
        IHttpClient(parent)
    {
        network_manager = new QNetworkAccessManager(this);
        network_manager->setCookieJar(new NetworkCookieJar(network_manager));
        connect(network_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
        request_holder = 0;
    }

    void HttpClient::SetPostPrepareStrategyFactory(IPostPrepareStrategyFactory* PostPrepareStrategyFactory)
    {
        this->PostPrepareStrategyFactory = PostPrepareStrategyFactory;
    }

    void HttpClient::sslErrors(QNetworkReply* reply,const QList<QSslError> &errors)
    {
         reply->ignoreSslErrors();
    }

    void HttpClient::Disconnect()
    {
        disconnected = true;
        disconnect();
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }
    }

    void HttpClient::Stop()
    {
        Disconnect();
    }

    void HttpClient::Connect(QObject *object, const char * slot)
    {
        //Disconnect finished callback from this HttpClient
        Disconnect();
        connect(this,SIGNAL(Finished()),object,slot);
    }

    void HttpClient::SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password)
    {
        if(server.isEmpty() || Port<=0)
        {
            network_manager->setProxy(QNetworkProxy::NoProxy);
        }else
        {
            QNetworkProxy proxy;
            if(IsHttp)
            {
                proxy.setType(QNetworkProxy::HttpProxy);
            }else
            {
                proxy.setType(QNetworkProxy::Socks5Proxy);
            }

            proxy.setHostName(server);
            proxy.setPort(Port);

            proxy.setUser(name);
            proxy.setPassword(password);

            network_manager->setProxy(proxy);
        }

    }

    QString HttpClient::GetLastUrl()
    {
        return LastUrl;
    }

    void HttpClient::Download(const QString &url, const QString &file)
    {


    }


    void HttpClient::Get(const QString &url, const GetOptions & Options)
    {
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }

        LastUrl = url;
        was_error = true;
        QNetworkRequest network_request = QNetworkRequest(QUrl(url));
        QSslConfiguration ssl_config = network_request.sslConfiguration();
        ssl_config.setPeerVerifyMode(QSslSocket::VerifyNone);
        network_request.setSslConfiguration(ssl_config);


        network_request.setRawHeader(QString("Cookie").toUtf8(),GetCookiesForUrl(url).toUtf8());
        QHash<QString, QString>::iterator i = Headers.begin();
        while (i != Headers.end())
        {
            network_request.setRawHeader(i.key().toUtf8(),i.value().toUtf8());
            ++i;
        }



        QNetworkReply *network_reply = network_manager->get(network_request);
        connect(network_reply,SIGNAL(downloadProgress(qint64,qint64)),this,SIGNAL(DownloadProgress(qint64,qint64)));
        request_holder = new QObject(network_manager);
        network_reply->setParent(request_holder);
        connect(network_reply,SIGNAL(finished()),this,SLOT(FinishedSlot()));
    }

    void HttpClient::AddHeader(const QString& name,const QString& value)
    {
        if(Headers.contains(name))
        {
            Headers[name] = value;
        }else
            Headers.insert(name,value);
    }

    void HttpClient::CleanHeader()
    {
        Headers.clear();
    }

    void HttpClient::Post(const QString &url, const QHash<QString,QString> & params, const PostOptions & Options)
    {
        QHash<QString,ContentData> Params;
        QHash<QString,QString>::const_iterator i;
        for(i = params.begin(); i != params.end(); ++i)
        {
            QPair<bool, ContentData> res = ParsePostArgument(i.value());
            ContentData Data = res.second;
            bool success = res.first;

            if(success)
                Params[i.key()] = Data;
            else
            {
                was_error =  true;
                last_error = QString("Failed to load file %1").arg(Data.DataString);

                disconnected = false;
                emit Finished();

                //Disconnect finished callback from this HttpClient
                if(!disconnected)
                    disconnect();
            }
        }

        Post(url,Params,Options);
    }

    QPair<bool, ContentData> HttpClient::ParsePostArgument(const QString& str)
    {
        QPair<bool, ContentData> res;
        ContentData Data;
        if(str.startsWith("file://"))
        {
            QString FileAndContentType = str;
            FileAndContentType = FileAndContentType.replace("file://","");
            QStringList FileAndContentTypeList = FileAndContentType.split(";");
            QString FileName = FileAndContentTypeList.at(0);

            QString ContentType;
            if(FileAndContentTypeList.length()>1)
                ContentType = FileAndContentTypeList.at(1);
            else
            {
                if(FileName.endsWith(".jpg") || FileName.endsWith(".jpeg"))
                {
                    ContentType = "image/jpeg";
                }else if(FileName.endsWith(".png"))
                {
                    ContentType = "image/png";
                }else if(FileName.endsWith(".gif"))
                {
                    ContentType = "image/gif";
                }else
                    ContentType = "application/octet-stream";
            }


            QFile f(FileName);

            if (!f.open(QFile::ReadOnly))
            {
                res.first = false;
                Data.DataString = FileName;
                res.second = Data;
                return res;
            }
            QFileInfo fi(FileName);

            Data.DataRaw = f.readAll();
            Data.FileName = fi.fileName();
            Data.ContentType = ContentType;
            f.close();
        }else if(str.startsWith("base64://"))
        {
            QString RawString = str;
            RawString = RawString.replace("base64://","");
            Data.DataRaw = QByteArray::fromBase64(RawString.toUtf8());
        }else if(str.startsWith("filebase64://"))
        {
            QString RawString = str;
            RawString = RawString.replace("filebase64://","").split(";").first();

            QRegExp r("scale\\=(\\d+)\\*(\\d+)");
            int scalex = -1;
            int scaley = -1;

            if(r.indexIn(str)>0)
            {
                scalex = r.cap(1).toInt();
                scaley = r.cap(2).toInt();
            }

            QFile f(RawString);
            if (!f.open(QFile::ReadOnly))
            {
                res.first = false;
                Data.DataString = str;
                res.second = Data;
                return res;
            }

            QByteArray data = f.readAll();
            if(scalex > 0 && scaley > 0)
            {
                QImage image = QImage::fromData(data);
                bool NeedResize = false;
                bool Scaled = false;
                QRect rect;
                rect.setWidth(image.width());
                rect.setLeft(0);
                rect.setHeight(image.height());
                rect.setTop(0);

                if(image.width() > scalex)
                {
                    NeedResize = true;
                    rect.setLeft((image.width() - scalex)/2);
                    rect.setWidth(scalex);
                }
                if(image.height() > scaley)
                {
                    NeedResize = true;
                    rect.setTop((image.height() - scaley)/2);
                    rect.setHeight(scaley);
                }
                if(NeedResize)
                {
                    image = image.copy(rect);
                }
                if(image.width() != scalex || image.height() != scaley)
                {
                    Scaled = true;
                    image = image.scaled(scalex,scaley);
                }
                if(NeedResize || Scaled)
                {
                    QByteArray ba;
                    QBuffer buffer(&ba);
                    buffer.open(QIODevice::WriteOnly);

                    image.save(&buffer, "PNG");
                    buffer.close();
                    data = ba;
                }

            }
            Data.DataString = QString::fromUtf8(data.toBase64());
            f.close();
        }else
        {
            Data.DataString = str;
        }


        res.first = true;
        res.second = Data;
        return res;
    }

    void HttpClient::Post(const QString &url, const QHash<QString,ContentData> & params, const PostOptions & Options)
    {
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }
        LastUrl = url;
        was_error = true;
        QNetworkRequest network_request = QNetworkRequest(QUrl(url));
        QSslConfiguration ssl_config = network_request.sslConfiguration();
        ssl_config.setPeerVerifyMode(QSslSocket::VerifyNone);
        network_request.setSslConfiguration(ssl_config);

        //network_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        network_request.setRawHeader(QString("Cookie").toUtf8(),GetCookiesForUrl(url).toUtf8());
        QHash<QString, QString>::iterator i = Headers.begin();
        while (i != Headers.end())
        {
            if(!i.value().isEmpty())
                network_request.setRawHeader(i.key().toUtf8(),i.value().toUtf8());
            ++i;
        }


        IPostPrepareStrategy *strategy = PostPrepareStrategyFactory->Create(Options.PrepareStrategy);
        QByteArray data = strategy->GenerateData(params);
        QByteArray k,v;
        k.append("Content-Type");
        v.append(strategy->GetContentType());
        delete strategy;
        network_request.setRawHeader(k, v);
        network_request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));


        QNetworkReply * network_reply = network_manager->post(network_request,data);

        request_holder = new QObject(network_manager);
        network_reply->setParent(request_holder);

        QObject::connect(network_reply,SIGNAL(finished()),this,SLOT(FinishedSlot()));

    }

    QString HttpClient::GetHeader(const QString& header)
    {
        int len = ReturnHeaders.length();
        QByteArray HeaderArray = header.toUtf8();
        for(int i = 0;i<len;i++)
        {
            QPair<QByteArray, QByteArray> pair = ReturnHeaders.at(i);
            if(pair.first.toLower() == HeaderArray.toLower())
            {
                return QString::fromUtf8(pair.second);
            }
        }
        return "";
    }

    void HttpClient::FinishedSlot()
    {
        QNetworkReply *network_reply = ((QNetworkReply *)sender());
        QObject::disconnect(network_reply,SIGNAL(finished()),this,SLOT(FinishedSlot()));

        was_error = network_reply->error() != QNetworkReply::NoError;

        if(network_reply->error()>=201 && network_reply->error()<=299)
            was_error = false;

        if(was_error)
            last_error = network_reply->errorString();
        else
            last_error = QString();

        ReturnHeaders = network_reply->rawHeaderPairs();

        QList<QNetworkCookie> cookies = QNetworkCookie::parseCookies(network_reply->rawHeader("Set-Cookie"));

        #if QT_VERSION >= 0x050000
            foreach(QNetworkCookie cookie,cookies)
                network_manager->cookieJar()->insertCookie(cookie);
        #else
            foreach(QNetworkCookie cookie,cookies)
                network_manager->cookieJar()->setCookiesFromUrl(QList<QNetworkCookie>()<<cookie,cookie.domain());
        #endif



        page_data = network_reply->readAll();

        page_content = QString::fromUtf8(page_data);

        status = network_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        network_reply->deleteLater();

        network_reply = 0;

        disconnected = false;
        emit Finished();

        //Disconnect finished callback from this HttpClient
        if(!disconnected)
            disconnect();
    }

    bool HttpClient::WasError()
    {
        return was_error;
    }

    QString HttpClient::GetErrorString()
    {
        return last_error;
    }

    QString HttpClient::GetContent()
    {
        return page_content;
    }

    QByteArray HttpClient::GetPageData()
    {
        return page_data;
    }

    QString HttpClient::GetBase64()
    {
        return QString::fromUtf8(page_data.toBase64());
    }

    int HttpClient::GetStatus()
    {
        return status;
    }

    QString HttpClient::GetCookiesForUrl(const QString& url)
    {
        QNetworkCookieJar * jar = network_manager->cookieJar();

        QString res;
        bool first = true;
        foreach(QNetworkCookie cookie,jar->cookiesForUrl(QUrl(url)))
        {
            if(!first)
                res.append(";");
            first = false;
            res.append(cookie.toRawForm(QNetworkCookie::NameAndValueOnly));

        }
        return res;

    }


    QString HttpClient::SaveCookies()
    {

        NetworkCookieJar * jar = qobject_cast<NetworkCookieJar*>(network_manager->cookieJar());

        QString res;
        bool first = true;
        foreach(QNetworkCookie cookie,jar->AllCookies())
        {
            if(!first)
                res.append(";");
            first = false;

            res.append(cookie.toRawForm(QNetworkCookie::Full).toBase64());
        }
        return res;
    }

    void HttpClient::RestoreCookies(const QString& cookies)
    {

        NetworkCookieJar * jar = qobject_cast<NetworkCookieJar*>(network_manager->cookieJar());

        foreach(QNetworkCookie cookie,jar->AllCookies())
        {
            jar->deleteCookie(cookie);
        }


        QStringList list = cookies.split(";");

        foreach(QString cookie,list)
        {
            QString cookieText = cookie;
            QByteArray cookieData = QByteArray::fromBase64(cookieText.toLatin1());
            QList<QNetworkCookie> cs = QNetworkCookie::parseCookies(cookieData);
            if(!cs.isEmpty())
            {
                jar->insertCookie(cs.first());
            }
        }
    }

}
