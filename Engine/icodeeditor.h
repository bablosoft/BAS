#ifndef ICODEEDITOR_H
#define ICODEEDITOR_H

#include "engine_global.h"

#include <QObject>
#include <QWidget>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ICodeEditor : public QObject
    {
        Q_OBJECT
    public:
        explicit ICodeEditor(QObject *parent = 0);
        virtual QWidget* GetWidget() = 0;
        virtual void SetText(const QString& Text) = 0;
        virtual QString GetText() = 0;
        virtual void Clear() = 0;

    signals:
        void ShowFinder();
        void SetSearchTerm(QString);
        void FindNext(bool);
        void Changed();
    public slots:

    };
}

#endif // ICODEEDITOR_H
