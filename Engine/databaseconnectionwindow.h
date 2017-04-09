#ifndef DATABASECONNECTIONWINDOW_H
#define DATABASECONNECTIONWINDOW_H


#include "engine_global.h"
#include <QObject>

#include "idatabaseconnectionwindow.h"
#include "databaseconnectiondialog.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DatabaseConnectionWindow : public IDatabaseConnectionWindow
    {
        Q_OBJECT

        DatabaseConnectionDialog * _DatabaseConnectionDialog;
        bool IsSilent;
        QString NewLabel;

    public:
        explicit DatabaseConnectionWindow(QObject *parent = 0);
        ~DatabaseConnectionWindow();
        virtual void SetIsSilent(bool IsSilent);
        virtual void Show();
        virtual void Hide();
        virtual void Failed(const QString& Message);

    private slots:
        void ActivateWindow();
        void Timeout();
    };
}

#endif // DATABASECONNECTIONWINDOW_H
