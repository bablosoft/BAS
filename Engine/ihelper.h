#ifndef IHELPER_H
#define IHELPER_H
#include "engine_global.h"

#include <QObject>
#include <QScriptValue>
#include <QVariant>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IHelper : public QObject
    {
        Q_OBJECT
    public:
        explicit IHelper(QObject *parent = 0);

    signals:

    public slots:
        virtual QString md5(const QString& data) = 0;
        virtual QString base64_encode(const QString& data) = 0;
        virtual QString base64_decode(const QString& data) = 0;
        virtual QString file_read(const QString& filename) = 0;
        virtual QString file_read_base64(const QString& filename) = 0;
        virtual void file_write(const QString& filename, const QString& data) = 0;
        virtual void file_write_base64(const QString& filename, const QString& data) = 0;
        virtual void file_append(const QString& filename, const QString& data) = 0;
        virtual void file_append_base64(const QString& filename, const QString& data) = 0;
        virtual void directory_create(const QString& dir) = 0;
        virtual QString directory_of(const QString& file) = 0;
        virtual QString filename_of(const QString& file) = 0;
        virtual QString combine_path(const QString& path1,const QString& path2) = 0;
        virtual QString encode_string(const QString& string,const QString& codec) = 0;
        virtual QList<int> image_get_dimension(const QString& image_data_base64) = 0;
        virtual QString image_central_crop(const QString& image_data_base64, int x, int y) = 0;
        virtual QString date_format(const QDateTime& date, const QString & format) = 0;

        virtual QString oauth1_header(const QString& auth_token,const QString& consumer_secret_key, const QString& consumer_public_key, const QString& url, const QString& method, const QString& realm, QVariantMap params) = 0;
    };
}

#endif // IHELPER_H
