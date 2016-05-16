#ifndef POSTPREPARESTRATEGYURLENCODE_H
#define POSTPREPARESTRATEGYURLENCODE_H
#include "engine_global.h"
#include "ipostpreparestrategy.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PostPrepareStrategyUrlEncode : public IPostPrepareStrategy
    {
        Q_OBJECT
    public:
        explicit PostPrepareStrategyUrlEncode(QObject *parent = 0);
        virtual QByteArray GenerateData(const QHash<QString,ContentData> & params);
        virtual QByteArray GetContentType();
    signals:

    public slots:

    };
}
#endif // POSTPREPARESTRATEGYURLENCODE_H
