#ifndef IPROPERTIES_H
#define IPROPERTIES_H

#include "engine_global.h"

#include <QObject>



namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IProperties : public QObject
    {
        Q_OBJECT
    public:
        explicit IProperties(QObject *parent = 0);
        virtual QString Get(const QString& Group, const QString& Key) = 0;
        virtual void Set(const QString& Group, const QString& Key, const QString & Value) = 0;
        virtual void Clear(const QString& Group, const QString& Key) = 0;
    signals:

    public slots:

    };
}

#endif // IPROPERTIES_H
