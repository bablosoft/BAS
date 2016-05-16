#include "imapclient.h"
#include <iostream>
#include "splifyheaders.h"

#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    ImapClient::ImapClient(QObject *parent) :
        IImapClient(parent)
    {

        Port = -1;
        Encryption = SSL;
        InboxFolder = "INBOX";

        MessageNumber = 0;

        Status = false;
        LastError = "";
        Curl = new CurlExecutor(this);
    }


    void ImapClient::SetHost(const QString &Host)
    {
        this->Host = Host;
    }

    void ImapClient::SetHostPort(int Port)
    {
        this->Port = Port;
    }

    void ImapClient::SetUserName(const QString &UserName)
    {
        this->Username = UserName;
    }

    void ImapClient::SetPassword(const QString &Password)
    {
        this->Password = Password;
    }

    void ImapClient::SetEncryption(EncryptionType Encryption)
    {
        this->Encryption = Encryption;
    }

    void ImapClient::SetEncryptionString(const QString& EncryptionString)
    {
        if(EncryptionString.toLower() == "ssl")
        {
            this->Encryption = SSL;
        }else
            this->Encryption = None;
    }
    void ImapClient::SetInboxFolder(const QString& Inbox)
    {
        this->InboxFolder = Inbox;
    }

    void ImapClient::SetProxy(const QString &ProxyServer, int ProxyPort, bool IsHttp, QString ProxyLogin , QString ProxyPassword)
    {
        this->ProxyServer = ProxyServer;
        this->ProxyPort = ProxyPort;
        this->IsHttp = IsHttp;
        this->ProxyLogin = ProxyLogin;
        this->ProxyPassword = ProxyPassword;
    }


    void ImapClient::PullNumberOfMessages()
    {
        Curl->Stop();
        Curl->disconnect();

        SetProxyToCurl();
        Curl->GetOptions()->insert(CURLOPT_USERNAME, Username);
        Curl->GetOptions()->insert(CURLOPT_PASSWORD, Password);
        Curl->GetOptions()->insert(CURLOPT_URL, GenerateUrl());
        Curl->GetOptions()->insert(CURLOPT_CUSTOMREQUEST, QString("EXAMINE ") + InboxFolder);
        connect(Curl,SIGNAL(Done()),this,SLOT(PullNumberOfMessagesDone()));
        Curl->Execute();
    }



    QString ImapClient::GenerateUrl()
    {


        QString Url;
        if(Encryption == SSL)
        {
            Url = "imaps";
            Curl->GetOptions()->insert(CURLOPT_USE_SSL,(int)CURLUSESSL_ALL);
        }
        else
        {
            Url = "imap";
            Curl->GetOptions()->insert(CURLOPT_USE_SSL,(int)CURLUSESSL_NONE);
        }
        Url += "://" + Host;
        if(Port > 0)
        {
            Url += QString(":") + QString::number(Port);
        }

        Url += "/";

        return Url;
    }

    void ImapClient::PullNumberOfMessagesDone()
    {
        Status = Curl->GetResult();
        if(Status)
        {
            QRegExp regexp("\\s+(\\d+)\\s+EXISTS");

            int pos = regexp.indexIn(QString::fromUtf8(Curl->GetDataByteArray()));
            if (pos > -1)
            {
                MessageNumber = regexp.cap(1).toInt();
            }else
            {
                Status = false;
                LastError = "Examine Inbox didn't match";
            }
        }else
        {
            LastError = QString::fromUtf8(Curl->GetDataByteArray());
        }

        emit Result();
    }

    int ImapClient::GetNumberOfMessages()
    {
        return MessageNumber;
    }

    bool ImapClient::GetStatus()
    {
        return Status;
    }
    QString ImapClient::GetLastError()
    {
          return LastError;
    }

    void ImapClient::SetProxyToCurl()
    {
        if(ProxyServer.isEmpty())
        {
            Curl->GetOptions()->insert(CURLOPT_PROXY, "");
            return;
        }

        QString proxy;
        if(IsHttp)
        {
            proxy += "http://";
        }else
        {
            proxy += "socks5://";
        }

        proxy += ProxyServer + ":" + QString::number(ProxyPort);
        Curl->GetOptions()->insert(CURLOPT_PROXY, proxy);

        if(!ProxyLogin.isEmpty())
        {
            Curl->GetOptions()->insert(CURLOPT_PROXYUSERNAME, ProxyLogin);
            Curl->GetOptions()->insert(CURLOPT_PROXYPASSWORD, ProxyPassword);
        }
    }


    void ImapClient::SearchMessages(const QString& Sender,const QString& Subject,const QString& Body)
    {

        QString SearchTerm = "SEARCH";
        bool IsNull = true;
        if(!Sender.isEmpty())
        {
            SearchTerm += QString(" FROM \"") + Sender + "\"";
            IsNull = false;
        }

        if(!Body.isEmpty())
        {
            SearchTerm += QString(" BODY \"") + Body + "\"";
            IsNull = false;
        }

        if(!Subject.isEmpty())
        {
            SearchTerm += QString(" SUBJECT \"") + Subject + "\"";
            IsNull = false;
        }
        if(IsNull)
            SearchTerm += QString(" ALL");
        SearchCustomMessages(SearchTerm);

    }

    void ImapClient::SearchCustomMessages(const QString& SearchTerm)
    {
        Curl->Stop();
        Curl->disconnect();

        SetProxyToCurl();
        Curl->GetOptions()->insert(CURLOPT_USERNAME, Username);
        Curl->GetOptions()->insert(CURLOPT_PASSWORD, Password);
        Curl->GetOptions()->insert(CURLOPT_URL, GenerateUrl() + InboxFolder);
        Curl->GetOptions()->insert(CURLOPT_CUSTOMREQUEST, SearchTerm);
        connect(Curl,SIGNAL(Done()),this,SLOT(SearchMessagesDone()));
        Curl->Execute();
    }

    void ImapClient::SearchMessagesDone()
    {
        Status = Curl->GetResult();
        if(Status)
        {
            QStringList res = QString::fromUtf8(Curl->GetDataByteArray()).split(QRegExp("\\s+"));
            SearchResult.clear();
            QRegExp OnlyDigits("\\d+");
            foreach(QString r, res)
            {
                if(OnlyDigits.exactMatch(r))
                    SearchResult.append(r);
            }
        }else
        {
            LastError = QString::fromUtf8(Curl->GetDataByteArray());
        }

        emit Result();
    }



    QStringList ImapClient::GetSearchResult()
    {
        return SearchResult;
    }

    void ImapClient::PullMessage(const QString& uid)
    {
        Curl->Stop();
        Curl->disconnect();
        if(uid.isEmpty())
        {
            Status = true;
            Message.clear();
            LastError.clear();
            emit Result();
            return;
        }

        SetProxyToCurl();
        Curl->GetOptions()->insert(CURLOPT_USERNAME, Username);
        Curl->GetOptions()->insert(CURLOPT_PASSWORD, Password);
        QString url = GenerateUrl() + InboxFolder + "/;UID=" + uid;
        Curl->GetOptions()->insert(CURLOPT_URL, url);
        connect(Curl,SIGNAL(Done()),this,SLOT(PullMessageDone()));
        Curl->Execute();
    }

    void ImapClient::PullMessageDone()
    {
        Status = Curl->GetResult();
        if(Status)
        {
            Message = QString::fromStdString(SimplifyEmail(QString::fromUtf8(Curl->GetDataByteArray()).toStdString()));
        }else
        {
            LastError = QString::fromUtf8(Curl->GetDataByteArray());
        }

        emit Result();
    }

    QString ImapClient::GetLastMessage()
    {
        return Message;
    }

    void ImapClient::CustomQuery(const QString& Url, const QString& query, const QString& filter)
    {
        Curl->Stop();
        Curl->disconnect();
        Curl->SetFilter(filter);
        QString baseurl = GenerateUrl();
        QString UrlCopy = Url;
        QString url = UrlCopy.replace("%base",baseurl).replace("%folder",InboxFolder);

        SetProxyToCurl();
        Curl->GetOptions()->insert(CURLOPT_USERNAME, Username);
        Curl->GetOptions()->insert(CURLOPT_PASSWORD, Password);

        Curl->GetOptions()->insert(CURLOPT_URL, url);
        if(!query.isEmpty())
            Curl->GetOptions()->insert(CURLOPT_CUSTOMREQUEST, query);
        connect(Curl,SIGNAL(Done()),this,SLOT(CustomQueryDone()));
        Curl->Execute();
    }


    void ImapClient::CustomQueryDone()
    {
        Status = Curl->GetResult();
        if(Status)
        {
            CustomQueryData = QString::fromUtf8(Curl->GetDataByteArray());
            CustomQueryAll = QString::fromUtf8(Curl->GetLogByteArray());
        }else
        {
            LastError = QString::fromUtf8(Curl->GetDataByteArray());
        }

        emit Result();
    }

    QString ImapClient::CustomQueryResult()
    {
        return CustomQueryData;
    }

    QString ImapClient::CustomQueryLog()
    {
        return CustomQueryAll;
    }
}
