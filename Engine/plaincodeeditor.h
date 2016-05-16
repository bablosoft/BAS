#ifndef PLAINCODEEDITOR_H
#define PLAINCODEEDITOR_H
#include "engine_global.h"

#include <QObject>
#include <QPlainTextEdit>
#include "icodeeditor.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT PlainCodeEditor : public ICodeEditor
    {
        Q_OBJECT
        QPlainTextEdit *Edit;
    public:
        explicit PlainCodeEditor(QObject *parent = 0);
        virtual QWidget* GetWidget();
        virtual void SetText(const QString& Text);
        virtual QString GetText();
        virtual void Clear();
    signals:

    public slots:

    };
}

#endif // PLAINCODEEDITOR_H
