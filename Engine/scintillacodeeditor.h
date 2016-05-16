#ifndef SCINTILLACODEEDITOR_H
#define SCINTILLACODEEDITOR_H
#include "engine_global.h"

#include <QObject>
#include <QSharedPointer>
#include "icodeeditor.h"
#include "basscintilla.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScintillaCodeEditor : public ICodeEditor
    {
        Q_OBJECT
        BASScintilla* Scintilla;
    public:
        explicit ScintillaCodeEditor(QObject *parent = 0);
        virtual QWidget* GetWidget();
        virtual void SetText(const QString& Text);
        virtual QString GetText();
        virtual void Clear();
    signals:

    public slots:

    };
}

#endif // SCINTILLACODEEDITOR_H
