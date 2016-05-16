#ifndef CSVHELPER_H
#define CSVHELPER_H

#include "engine_global.h"
#include "icsvhelper.h"
#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT CsvHelper : public ICsvHelper
    {
        Q_OBJECT
    public:
        explicit CsvHelper(QObject *parent = 0);
        virtual QString Generate(const QStringList& List, QChar Separator);
        virtual QStringList Parse(const QString& Line);
    signals:

    public slots:

    };
}

#endif // CSVHELPER_H
