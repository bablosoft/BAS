#ifndef DATABASESCHEMAEDITOR_H
#define DATABASESCHEMAEDITOR_H

#include <QObject>

#include "engine_global.h"
#include "idatabaseschemaeditor.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DatabaseSchemaEditor : public IDatabaseSchemaEditor
    {
        Q_OBJECT

    public:
        explicit DatabaseSchemaEditor(QObject *parent = 0);

        virtual QString GetXml(const QString& InputXml);

    };
}

#endif // DATABASESCHEMAEDITOR_H
