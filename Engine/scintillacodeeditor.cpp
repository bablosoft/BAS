#include "scintillacodeeditor.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ScintillaCodeEditor::ScintillaCodeEditor(QObject *parent) :
        ICodeEditor(parent)
    {
        Scintilla = new BASScintilla();
        Scintilla->Init();
        connect(this,SIGNAL(SetSearchTerm(QString)),Scintilla,SLOT(SetSearchTerm(QString)));
        connect(this,SIGNAL(FindNext(bool)),Scintilla,SLOT(FindNext(bool)));
        connect(Scintilla,SIGNAL(ShowFinder()),this,SIGNAL(ShowFinder()));
        connect(Scintilla,SIGNAL(textChanged()),this,SIGNAL(Changed()));
    }

    QWidget* ScintillaCodeEditor::GetWidget()
    {
        return Scintilla;
    }

    void ScintillaCodeEditor::SetText(const QString& Text)
    {
        Scintilla->setText(Text);
    }

    QString ScintillaCodeEditor::GetText()
    {
        return Scintilla->text();
    }

    void ScintillaCodeEditor::Clear()
    {
        Scintilla->clear();
    }
}
