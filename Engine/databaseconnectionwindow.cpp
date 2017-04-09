#include "databaseconnectionwindow.h"
#include <QTimer>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    DatabaseConnectionWindow::DatabaseConnectionWindow(QObject *parent) :
         IDatabaseConnectionWindow(parent)
    {
        _DatabaseConnectionDialog = 0;
        IsSilent = false;
    }

    DatabaseConnectionWindow::~DatabaseConnectionWindow()
    {
        if(_DatabaseConnectionDialog)
            delete _DatabaseConnectionDialog;
    }

    void DatabaseConnectionWindow::SetIsSilent(bool IsSilent)
    {
        this->IsSilent = IsSilent;
    }
    void DatabaseConnectionWindow::Show()
    {
        if(IsSilent)
        {
            QTimer::singleShot(20000,this,SLOT(Timeout()));
        }else
        {
            QTimer::singleShot(3000,this,SLOT(ActivateWindow()));
        }
    }

    void DatabaseConnectionWindow::Timeout()
    {
        emit Cancel();
    }

    void DatabaseConnectionWindow::ActivateWindow()
    {
        if(!_DatabaseConnectionDialog)
        {
            _DatabaseConnectionDialog = new DatabaseConnectionDialog();
            connect(_DatabaseConnectionDialog,SIGNAL(RunWithoutDatabase()),this,SIGNAL(ContinueWithoutDatabase()));
            connect(_DatabaseConnectionDialog,SIGNAL(Close()),this,SIGNAL(Cancel()));
            connect(_DatabaseConnectionDialog,SIGNAL(ShowLog()),this,SIGNAL(ShowLog()));
            if(NewLabel.length() > 0)
                _DatabaseConnectionDialog->SetLabel(NewLabel);
            _DatabaseConnectionDialog->show();
        }
    }

    void DatabaseConnectionWindow::Hide()
    {
        emit DatabaseConnectionOk();
    }
    void DatabaseConnectionWindow::Failed(const QString& Message)
    {
        if(IsSilent)
        {
            emit Cancel();
        }else
        {
            if(!_DatabaseConnectionDialog)
            {
                NewLabel = Message;
            }else
            {
                _DatabaseConnectionDialog->SetLabel(Message);
            }
        }
    }
}
