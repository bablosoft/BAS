#ifndef IDATABASECONNECTIONWINDOW_H
#define IDATABASECONNECTIONWINDOW_H

#include "engine_global.h"
#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  IDatabaseConnectionWindow : public QObject
    {
        Q_OBJECT
    public:


        explicit IDatabaseConnectionWindow(QObject *parent = 0);

        virtual void SetIsSilent(bool IsSilent) = 0;
        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void Failed(const QString& Message) = 0;

    signals:
        void Cancel();
        void ContinueWithoutDatabase();
        void DatabaseConnectionOk();
        void ShowLog();


    };
}

#endif // IDATABASECONNECTIONWINDOW_H
