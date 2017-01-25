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
        virtual QString Solve(const QString& base64,const QStringList& props);
        virtual void ReportBad(const QString& id);
        virtual bool TimeLimited();

        QWidget* GetWidget();
        int GetSize();
    signals:
        void ChangedSize(int size);

    private slots:
        void DoneAdapter(const QString& val, const QString& id, bool res);
        void DoneSlot(const QString& val, const QString& id, bool res,const QString& solver_id);
    };
}

#endif // MANUALCAPTCHASOLVER_H
