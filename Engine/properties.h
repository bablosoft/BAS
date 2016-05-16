#ifndef PROPERTIES_H
#define PROPERTIES_H
#include "engine_global.h"

#include <QObject>
#include <QHash>
#include <QSharedPointer>

#include "iproperties.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Properties : public IProperties
    {
        Q_OBJECT
        QHash<QString, QSharedPointer<QHash<QString, QString> > > Data;
    public:
        explicit Properties(QObject *parent = 0);

    signals:

    public slots:
        virtual QString Get(const QString& Group, const QString& Key);
        virtual void Set(const QString& Group, const QString& Key, const QString & Value);
        virtual void Clear(const QString& Group, const QString& Key);
    };
}

#endif // PROPERTIES_H
