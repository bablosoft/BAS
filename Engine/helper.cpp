#include "helper.h"
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMessageAuthenticationCode>

#include <QTextStream>
#include <QTextCodec>
#include <QImage>
#include <QBuffer>
#include <QUrl>
#include <QDateTime>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    Helper::Helper(QObject *parent) :
        IHelper(parent)
    {
    }

    QString Helper::md5(const QString& data)
    {
        return QString::fromUtf8(QCryptographicHash::hash(data.toUtf8(),QCryptographicHash::Md5).toHex());
    }

    QString Helper::base64_encode(const QString& data)
    {
        return data.toUtf8().toBase64();
    }

    QString Helper::base64_decode(const QString& data)
    {
        QByteArray d = QByteArray::fromBase64(data.toUtf8());
        return QString::fromUtf8(d);
    }


    void Helper::directory_create(const QString& dir)
    {
        QDir(dir).mkpath(".");
    }



    QString Helper::file_read(const QString& filename)
    {
        QFile f(filename);
        if (!f.open(QFile::ReadOnly | QFile::Text))
            return QString();
        QTextStream in(&f);
        QString res = in.readAll();
        f.close();
        return res;
    }

    QString Helper::file_read_base64(const QString& filename)
    {
        QFile f(filename);
        if (!f.open(QFile::ReadOnly))
        {
            return "";
        }


        QString res = QString::fromUtf8(f.readAll().toBase64());
        f.close();
        return res;
    }

    void Helper::file_write(const QString& filename, const QString& data)
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
            return;
        file.write(data.toUtf8());
        file.close();

    }

    void Helper::file_append(const QString& filename, const QString& data)
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
            return;
        file.write(data.toUtf8());
        file.close();
    }

    void Helper::file_write_base64(const QString& filename, const QString& data)
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
            return;
        file.write(QByteArray::fromBase64(data.toUtf8()));
        file.close();
    }

    void Helper::file_append_base64(const QString& filename, const QString& data)
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
            return;
        file.write(QByteArray::fromBase64(data.toUtf8()));
        file.close();

    }


    QString Helper::directory_of(const QString& file)
    {
        return QFileInfo(file).dir().absolutePath();
    }

    QString Helper::filename_of(const QString& file)
    {
        return QFileInfo(file).fileName();
    }

    QString Helper::combine_path(const QString& path1,const QString& path2)
    {
        return QDir::cleanPath(path1 + QDir::separator() + path2);
    }

    QString Helper::encode_string(const QString& string,const QString& codec)
    {
        QTextCodec *c = QTextCodec::codecForName(codec.toUtf8());
        return QString::fromUtf8(c->fromUnicode(string).toBase64());

    }

    QList<int> Helper::image_get_dimension(const QString& image_data_base64)
    {
        QImage image = QImage::fromData(QByteArray::fromBase64(image_data_base64.toUtf8()));
        QList<int> res;
        res.push_back(image.width());
        res.push_back(image.height());

        return res;
    }

    QString Helper::image_central_crop(const QString& image_data_base64, int x, int y)
    {
        QImage image = QImage::fromData(QByteArray::fromBase64(image_data_base64.toUtf8()));
        if(x > 0 && y > 0)
        {
            bool NeedResize = false;
            QRect rect;
            rect.setWidth(image.width());
            rect.setLeft(0);
            rect.setHeight(image.height());
            rect.setTop(0);

            if(image.width() > x)
            {
                NeedResize = true;
                rect.setLeft((image.width() - x)/2);
                rect.setWidth(x);
            }
            if(image.height() > y)
            {
                NeedResize = true;
                rect.setTop((image.height() - y)/2);
                rect.setHeight(y);
            }
            if(NeedResize)
            {
                image = image.copy(rect);
                QByteArray ba;
                QBuffer buffer(&ba);
                buffer.open(QIODevice::WriteOnly);

                image.save(&buffer, "PNG");
                buffer.close();
                return ba.toBase64();
            }
        }

        return image_data_base64;
    }


    QString Helper::oauth1_header(const QString& auth_token, const QString& consumer_secret_key, const QString& consumer_public_key, const QString& url, const QString& method, const QString& realm, QVariantMap params)
    {
        QByteArray base;
        base.append(method.toUtf8() + "&");
        base.append(QUrl::toPercentEncoding(QUrl(url).toString(QUrl::RemoveQuery)) + "&");

        QString timestamp = QString::number(QDateTime::currentDateTimeUtc().toTime_t());

        params.insert("oauth_consumer_key", consumer_public_key);
        QString nonce = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
        nonce.append(QString::number(qrand()));
        params.insert("oauth_nonce", nonce.toLatin1());
        params.insert("oauth_signature_method", "HMAC-SHA1");
        params.insert("oauth_timestamp", timestamp);
        params.insert("oauth_version", "1.0");

        QByteArray ret;
        bool first = true;

        QVariantMap::iterator i;
        for (i = params.begin(); i != params.end(); ++i)
        {
            if (first)
            {
                first = false;
            }else
            {
                ret.append("&");
            }
            ret.append(QUrl::toPercentEncoding(i.key()) + "=" + QUrl::toPercentEncoding(i.value().toString()));
        }
        base.append(QUrl::toPercentEncoding(ret));

        QByteArray secret = QUrl::toPercentEncoding(consumer_secret_key) + "&" + QUrl::toPercentEncoding(auth_token);
        QString signature = QUrl::toPercentEncoding(QMessageAuthenticationCode::hash(base, secret, QCryptographicHash::Sha1).toBase64());
        return QString("OAuth realm=\"" + realm + "\", oauth_version=\"1.0\", oauth_nonce=\"" + nonce + "\", oauth_timestamp=\"" + timestamp + "\", oauth_signature=\"" + signature + "\", oauth_consumer_key=\"" + consumer_public_key + "\", oauth_signature_method=\"HMAC-SHA1\"");
    }

    QString Helper::date_format(const QDateTime& date, const QString & format)
    {
        return date.toString(format);
    }






}
