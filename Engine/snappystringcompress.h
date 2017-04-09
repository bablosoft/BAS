#ifndef SNAPPYSTRINGCOMPRESS_H
#define SNAPPYSTRINGCOMPRESS_H

#include "engine_global.h"
#include "istringcompress.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SnappyStringCompress : public IStringCompress
    {
        Q_OBJECT
    public:
        explicit SnappyStringCompress(QObject *parent = 0);

    public:
        virtual QString Compress(const QString& data);
        virtual QString Uncompress(const QString& data);
    };
}


#endif // SNAPPYSTRINGCOMPRESS_H
