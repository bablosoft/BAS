#ifndef IPOSTPREPARESTRATEGY_H
#define IPOSTPREPARESTRATEGY_H
#include "engine_global.h"

#include <QObject>
#include "ihttpclient.h"

namespace BrowserAutomationStudioFramework
{
    struct ContentData;


    class ENGINESHARED_EXPORT IPostPrepareStrategy : public QObject
    {
        Q_OBJECT
    public:
        explicit IPostPrepareStrategy(QObject *parent = 0);
        virtual QByteArray GenerateData(const QHash<QString,ContentData> & params) = 0;
        virtual QByteArray GetContentType() = 0;
    signals:

    public slots:

    };
}

#endif // IPOSTPREPARESTRATEGY_H
