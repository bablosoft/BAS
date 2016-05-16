#ifndef ICSVHELPER_H
#define ICSVHELPER_H

#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ICsvHelper : public QObject
    {
        Q_OBJECT
    public:
        explicit ICsvHelper(QObject *parent = 0);
        virtual QString Generate(const QStringList& List, QChar Separator) = 0;
        virtual QStringList Parse(const QString& Line) = 0;
    signals:

    public slots:

    };
}

#endif // ICSVHELPER_H
