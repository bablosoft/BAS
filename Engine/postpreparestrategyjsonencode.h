#ifndef POSTPREPARESTRATEGYJSONENCODE_H
#define POSTPREPARESTRATEGYJSONENCODE_H

#include "engine_global.h"
#include "ipostpreparestrategy.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PostPrepareStrategyJsonEncode : public IPostPrepareStrategy
    {
    public:
        PostPrepareStrategyJsonEncode();
        virtual QByteArray GenerateData(const QHash<QString,ContentData> & params);
        virtual QByteArray GetContentType();
    };
}

#endif // POSTPREPARESTRATEGYJSONENCODE_H
