#ifndef MANUALCAPTCHASOLVER_H
#define MANUALCAPTCHASOLVER_H
#include "engine_global.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include "isolver.h"
#include "flowlayout.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ManualCaptchaSolver : public ISolver
    {
        Q_OBJECT
        int IdCounter;
        QScrollArea* Scroll;
        QWidget* Widget;
        FlowLayout *Layout;
        int Size;
    public:

        explicit ManualCaptchaSolver(QObject *parent = 0);
        ~ManualCaptchaSolver();
        virtual QString Solve(const QString& base64);
        virtual void SetProperty(const QString& name,const QString& value);
        virtual bool TimeLimited();

        QWidget* GetWidget();
        int GetSize();
    signals:
        void Done(const QString& val, const QString& id, bool res);
        void ChangedSize(int size);

    private slots:

        void DoneSlot(const QString& val, const QString& id, bool res);
    };
}

#endif // MANUALCAPTCHASOLVER_H
