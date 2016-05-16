#include "plaincodeeditor.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PlainCodeEditor::PlainCodeEditor(QObject *parent) :
        ICodeEditor(parent)

    {
        Edit = new QPlainTextEdit();
        connect(Edit,SIGNAL(textChanged()),this,SIGNAL(Changed()));

    }

    QWidget* PlainCodeEditor::GetWidget()
    {
        return Edit;
    }

    void PlainCodeEditor::SetText(const QString& Text)
    {
        Edit->setPlainText(Text);
    }

    QString PlainCodeEditor::GetText()
    {
        return Edit->toPlainText();
    }

    void PlainCodeEditor::Clear()
    {
        Edit->clear();
    }
}
