#ifndef IDATABASESCHEMAEDITOR_H
#define IDATABASESCHEMAEDITOR_H

#include <QObject>

#include "engine_global.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IDatabaseSchemaEditor : public QObject
    {
        Q_OBJECT
    public:
        explicit IDatabaseSchemaEditor(QObject *parent = 0);

        virtual QString GetXml(const QString& InputXml) = 0;

    public slots:

    };
}

#endif // IDATABASESCHEMAEDITOR_H
