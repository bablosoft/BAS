#ifndef HELPER_H
#define HELPER_H
#include "engine_global.h"

#include "ihelper.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Helper : public IHelper
    {
        Q_OBJECT
    public:
        explicit Helper(QObject *parent = 0);

    signals:

    public slots:
        virtual QString md5(const QString& data);
        virtual QString base64_encode(const QString& data);
        virtual QString base64_decode(const QString& data);
        virtual QString file_read(const QString& filename);
        virtual QString file_read_base64(const QString& filename);
        virtual void file_write_base64(const QString& filename, const QString& data);
        virtual void file_append_base64(const QString& filename, const QString& data);
        virtual void file_write(const QString& filename, const QString& data);
        virtual void file_append(const QString& filename, const QString& data);
        virtual void directory_create(const QString& dir);

        virtual QString directory_of(const QString& file);
        virtual QString filename_of(const QString& file);
        virtual QString combine_path(const QString& path1,const QString& path2);
        virtual QString encode_string(const QString& string,const QString& codec);
        virtual QList<int> image_get_dimension(const QString& image_data_base64);
        virtual QString image_central_crop(const QString& image_data_base64, int x, int y);
        virtual QString date_format(const QDateTime& date, const QString & format);

        virtual QString oauth1_header(const QString& auth_token,const QString& consumer_secret_key, const QString& consumer_public_key, const QString& url, const QString& method, const QString& realm, QVariantMap params);
    };
}

#endif // HELPER_H
