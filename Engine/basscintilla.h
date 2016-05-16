#ifndef BASSCINTILLA_H
#define BASSCINTILLA_H
#include "engine_global.h"

#include <Qsci/qsciscintilla.h>
#include <QKeyEvent>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT BASScintilla : public QsciScintilla
    {
        Q_OBJECT
        QString Term;
        bool Searched;
        bool LastDirection;
    public:
        void Init();
        virtual void keyPressEvent(QKeyEvent *e);

    signals:
        void ShowFinder();
    public slots:
        void SetSearchTerm(const QString &Term);
        void FindNext(bool Direction);

    };
}

#endif // BASSCINTILLA_H
