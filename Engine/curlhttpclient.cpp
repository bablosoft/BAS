#include "curlhttpclient.h"
#include <QTextCodec>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    CurlHttpClient::CurlHttpClient(QObject *parent) :
        IHttpClient(parent)
    {
        request_holder = 0;
        Thread = 0;
    }

    QThread *CurlHttpClient::GetThread()
    {
        if(!Thread)
        {
            Thread = new QThread();
            connect(Thread,SIGNAL(finished()),Thread,SLOT(deleteLater()));
        }
        return Thread;
    }

    CurlHttpClient::~CurlHttpClient()
    {
        if(Thread)
            Thread->quit();
    }


    void CurlHttpClient::Download(const QString &url, const QString &file)
    {
        QFileInfo(file).absoluteDir().mkpath(".");
        GetOptions Options;
        GetInternal(url,file,Options);
    }

    void CurlHttpClient::Get(const QString &url, const GetOptions & Options)
    {
        GetInternal(url,QString(),Options);
    }

    void CurlHttpClient::GetInternal(const QString &url,const QString &filename, const GetOptions & Options)
    {
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }

        Curl = new CurlExecutor(this);
        Curl->SetThread(GetThread());
        Curl->SetFilter("*");
        request_holder = new QObject(this);
        Curl->setParent(request_holder);

        QtCUrl::Options* options = Curl->GetOptions();

        LastUrl = url;
        was_error = true;


        QHash<QString, QString>::iterator i = Headers.begin();

        QStringList HeadersList;
        HeadersList<<QString("Cookie: ") + GetCookiesForUrl(url);
        while (i != Headers.end())
        {
            if(i.key().toLower() == "accept-encoding")
            {
                options->insert(CURLOPT_ACCEPT_ENCODING,i.value());
                i++;
                continue;
            }
            HeadersList.append(i.key() + ": " + i.value());
            i++;
        }

        options->insert(CURLOPT_HTTPHEADER,HeadersList);

        if(!ProxyString.isEmpty())
        {
            options->insert(CURLOPT_PROXY,ProxyString);
            if(!ProxyAuthString.isEmpty())
                options->insert(CURLOPT_PROXYUSERPWD,ProxyAuthString);
        }

        QString Method = Options.Method.toUpper();
        if(Method == "HEAD")
            options->insert(CURLOPT_NOBODY, 1);
        else if(Method != "GET")
            options->insert(CURLOPT_CUSTOMREQUEST, Method);

        options->insert(CURLOPT_URL,url);
        options->insert(CURLOPT_FOLLOWLOCATION,0);

        if(!filename.isEmpty())
        {
            Curl->SetFilename(filename);
        }

        connect(Curl,SIGNAL(Done()),this,SLOT(FinishedSlot()));
        Curl->Execute();
    }

    void CurlHttpClient::Post(const QString &url, const QHash<QString,ContentData> & params, const PostOptions & Options)
    {
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }

        Curl = new CurlExecutor(this);
        Curl->SetThread(GetThread());
        Curl->SetFilter("*");
        request_holder = new QObject(this);
        Curl->setParent(request_holder);

        QtCUrl::Options* options = Curl->GetOptions();

        LastUrl = url;
        was_error = true;

        options->insert(CURLOPT_URL,url);

        QHash<QString, QString>::iterator i = Headers.begin();

        QStringList HeadersList;
        HeadersList<<QString("Cookie: ") + GetCookiesForUrl(url);
        while (i != Headers.end())
        {
            if(i.key().toLower() == "accept-encoding")
            {
                options->insert(CURLOPT_ACCEPT_ENCODING,i.value());
                i++;
                continue;
            }
            HeadersList.append(i.key() + ": " + i.value());
            i++;
        }

        QString Method = Options.Method.toUpper();
        if(Method != "POST")
            options->insert(CURLOPT_CUSTOMREQUEST, Method);

        IPostPrepareStrategy *strategy = PostPrepareStrategyFactory->Create(Options.PrepareStrategy);
        QByteArray data = strategy->GenerateData(params);

        HeadersList<<QString("Content-Type: ") + strategy->GetContentType();
        delete strategy;

        options->insert(CURLOPT_POSTFIELDSIZE, data.size());
        options->insert(CURLOPT_COPYPOSTFIELDS,data);
        options->insert(CURLOPT_HTTPHEADER,HeadersList);
        options->insert(CURLOPT_FOLLOWLOCATION,0);
        if(!ProxyString.isEmpty())
        {
            options->insert(CURLOPT_PROXY,ProxyString);
            if(!ProxyAuthString.isEmpty())
                options->insert(CURLOPT_PROXYUSERPWD,ProxyAuthString);
        }

        connect(Curl,SIGNAL(Done()),this,SLOT(FinishedSlot()));
        Curl->Execute();
    }


    void CurlHttpClient::FinishedSlot()
    {
        this->Curl = 0;
        CurlExecutor *Curl = ((CurlExecutor *)sender());
        QObject::disconnect(Curl,SIGNAL(Done()),this,SLOT(FinishedSlot()));

        was_error = !Curl->GetResult();

        if(was_error)
            last_error = QString::fromUtf8(Curl->GetDataByteArray());
        else
            last_error = QString();

        //int index = Curl->GetLogByteArray().indexOf('\n');

        status = -1;

        QByteArray httpHeaders = Curl->GetLogByteArray();//Curl->GetLogByteArray().mid(index + 1).trimmed();
        QString Codec = "utf-8";
        ReturnHeaders.clear();
        foreach(QByteArray line, httpHeaders.split('\n')) {

            if(line.toLower().startsWith("http/"))
            {
                QRegExp r1("\\d\\d\\d");
                if(r1.indexIn(line) != -1)
                {
                    status = r1.cap(0).toInt();
                }
            }

            int colon = line.indexOf(':');
            if(colon>=0)
            {
                QByteArray headerName = line.left(colon).trimmed();

                QByteArray headerValue = line.mid(colon + 1).trimmed();
                if(headerName.toLower() == "set-cookie")
                {
                    QList<QNetworkCookie> cookies = QNetworkCookie::parseCookies(headerValue);
                    foreach(QNetworkCookie cookie,cookies)
                    {
                        if(cookie.domain().length()>0 && !cookie.domain().startsWith("."))
                            cookie.setDomain(QString(".") + cookie.domain());
                        if(cookie.domain().isEmpty())
                        {
                            cookie.setDomain(QString(".") + QUrl(LastUrl).host());
                        }
                        Cookies.insertCookie(cookie);
                    }
                }else if(headerName.toLower() == "content-type")
                {
                    QRegExp r("charset\\=([^\\\"\\\']+)");
                    if(r.indexIn(headerValue) != -1)
                    {
                        Codec = r.cap(1);
                    }
                }
                QPair<QByteArray, QByteArray> p;
                p.first = headerName;
                p.second = headerValue;
                ReturnHeaders.append(p);
            }
        }



        page_data = Curl->GetDataByteArray();
        QTextCodec *codec = QTextCodec::codecForName(Codec.toUtf8());
        if(codec)
            page_content = codec->toUnicode(page_data);
        else
            page_content = QString::fromUtf8(page_data);

        Curl->deleteLater();

        disconnected = false;
        emit Finished();

        //Disconnect finished callback from this HttpClient
        if(!disconnected)
            disconnect();

    }


    void CurlHttpClient::Post(const QString &url, const QHash<QString,QString> & params, const PostOptions & Options)
    {
        QHash<QString,ContentData> Params;
        QHash<QString,QString>::const_iterator i;
        for(i = params.begin(); i != params.end(); ++i)
        {
            QPair<bool, ContentData> res = ParsePostArgument(i.value(),Options.ContentTypeEncoding);
            ContentData Data = res.second;
            bool success = res.first;

            if(success)
                Params[i.key()] = Data;
            else
            {
                was_error =  true;
                last_error = tr("Failed to load file %1").arg(Data.DataString);

                disconnected = false;
                emit Finished();

                //Disconnect finished callback from this HttpClient
                if(!disconnected)
                    disconnect();
            }
        }

        Post(url,Params,Options);
    }

    bool CurlHttpClient::WasError()
    {
        return was_error;
    }
    QString CurlHttpClient::GetErrorString()
    {
        return last_error;
    }
    QString CurlHttpClient::GetContent()
    {
        return page_content;
    }
    QByteArray CurlHttpClient::GetPageData()
    {
        return page_data;
    }
    QString CurlHttpClient::GetBase64()
    {
        return QString::fromUtf8(page_data.toBase64());
    }
    int CurlHttpClient::GetStatus()
    {
        return status;
    }
    QString CurlHttpClient::GetLastUrl()
    {
        return LastUrl;
    }

    void CurlHttpClient::Connect(QObject *object, const char * slot)
    {
        Disconnect();
        connect(this,SIGNAL(Finished()),object,slot);
    }
    void CurlHttpClient::Disconnect()
    {
        disconnected = true;
        disconnect();
        if(request_holder)
        {
            request_holder->deleteLater();
            request_holder = 0;
        }
    }
    void CurlHttpClient::Stop()
    {
        Disconnect();

    }
    QString CurlHttpClient::GetHeader(const QString& header)
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
    void CurlHttpClient::AddHeader(const QString& name,const QString& value)
    {
        if(Headers.contains(name))
        {
            Headers[name] = value;
        }else
            Headers.insert(name,value);
    }

    void CurlHttpClient::CleanHeader()
    {
        Headers.clear();
    }

    void CurlHttpClient::SetProxy(const QString& server, int Port, bool IsHttp, const QString& name, const QString& password)
    {
        ProxyString.clear();
        ProxyAuthString.clear();
        if(!name.isEmpty())
            ProxyAuthString = name + ":" + password;

        if(!server.isEmpty())
        {
            ProxyString = server + ":" + QString::number(Port);
            if(!IsHttp)
            {
                ProxyString = QString("socks5://") + ProxyString;
            }
        }

    }
    QString CurlHttpClient::GetCookiesForUrl(const QString& url)
    {
        QString res;
        bool first = true;
        foreach(QNetworkCookie cookie,Cookies.cookiesForUrl(QUrl(url)))
        {
            if(!first)
                res.append(";");
            first = false;
            res.append(cookie.toRawForm(QNetworkCookie::NameAndValueOnly));

        }
        return res;
    }
    void CurlHttpClient::SetPostPrepareStrategyFactory(IPostPrepareStrategyFactory* PostPrepareStrategyFactory)
    {
        this->PostPrepareStrategyFactory = PostPrepareStrategyFactory;
    }

    QString CurlHttpClient::SaveCookies()
    {
        QString res;
        bool first = true;
        QVariantList CookiesJson;
        foreach(QNetworkCookie cookie,Cookies.AllCookies())
        {
            if(!first)
                res.append(";");
            first = false;

            QVariantMap res;

            res.insert("value",QString::fromUtf8(cookie.value()));
            res.insert("name",QString::fromUtf8(cookie.name()));
            res.insert("domain",cookie.domain());
            res.insert("path",cookie.path());
            res.insert("creation",SerializeTime(QDateTime(QDate(2010,1,1))));
            res.insert("expires",SerializeTime(cookie.expirationDate()));
            res.insert("has_expires",(!cookie.isSessionCookie()) ? "1" : "0");
            res.insert("httponly",(cookie.isHttpOnly()) ? "1" : "0");
            res.insert("last_access",SerializeTime(QDateTime(QDate(2010,1,1))));
            res.insert("secure",(cookie.isSecure()) ? "1" : "0");

            CookiesJson.append(res);


        }
        QVariantMap Res;
        Res.insert("cookies",CookiesJson);
        QJsonObject object = QJsonObject::fromVariantMap(Res);

        QJsonDocument document;
        document.setObject(object);

        return QString::fromUtf8(document.toJson());
    }
    void CurlHttpClient::RestoreCookies(const QString& cookies)
    {
        foreach(QNetworkCookie cookie,Cookies.AllCookies())
        {
            Cookies.deleteCookie(cookie);
        }

        {
            QJsonDocument InputObject;
            QJsonParseError err;
            InputObject = QJsonDocument::fromJson(cookies.toUtf8(),&err);
            if(err.error)
                return;

            for(QJsonValue val: InputObject.object()["cookies"].toArray())
            {
                QNetworkCookie c;
                c.setValue(val.toObject()["value"].toString().toUtf8());
                c.setName(val.toObject()["name"].toString().toUtf8());
                c.setDomain(val.toObject()["domain"].toString());
                c.setPath(val.toObject()["path"].toString());
                c.setExpirationDate(DeserializeTime(val.toObject()["expires"].toObject()));
                c.setHttpOnly(val.toObject()["httponly"].toString() == "1");
                c.setSecure(val.toObject()["secure"].toString() == "1");
                Cookies.insertCookie(c);

            }
        }
    }

    QPair<bool, ContentData> CurlHttpClient::ParsePostArgument(const QString& str, const QString& encoding)
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
            Data.FileName = "file.jpg";
            Data.ContentType = "image/jpeg";
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
            if(encoding != "UTF-8")
            {
                QTextCodec *codec = QTextCodec::codecForName( encoding.toUtf8() );

                if(codec)
                {
                    Data.DataRaw = codec->fromUnicode(str);
                }
                else
                    Data.DataString = str;
            }else
            {
                Data.DataString = str;
            }
        }


        res.first = true;
        res.second = Data;
        return res;
    }
}
