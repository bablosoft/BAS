#ifndef ISTRINGBUILDER_H
#define ISTRINGBUILDER_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IStringBuilder : public QObject
    {
        Q_OBJECT
    public:
        explicit IStringBuilder(QObject *parent = 0);

    signals:
        void Changed(const QString& str);
    public slots:
        virtual void AddAdditionalData(const QHash<QString,QString>& Data) = 0;
        virtual QString Expand(const QString& str) = 0;
        virtual void Show(const QString& str) = 0;
    };
}

#endif // ISTRINGBUILDER_H
