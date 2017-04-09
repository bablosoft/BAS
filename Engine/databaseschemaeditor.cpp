#include "databaseschemaeditor.h"
#include "databaseschemaeditordialog.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DatabaseSchemaEditor::DatabaseSchemaEditor(QObject *parent) :
        IDatabaseSchemaEditor(parent)
    {

    }

    QString DatabaseSchemaEditor::GetXml(const QString& InputXml)
    {
        DatabaseSchemaEditorDialog dialog;
        dialog.ParseXml(InputXml);
        dialog.exec();
        return dialog.GetXml();
    }


}
