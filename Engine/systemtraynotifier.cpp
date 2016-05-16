#include "systemtraynotifier.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    SystemTrayNotifier::SystemTrayNotifier(QObject *parent) :
        ISystemTrayNotifier(parent)
    {
        TrayIcon = new QSystemTrayIcon(this);
        connect(TrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),SLOT(Activated(QSystemTrayIcon::ActivationReason)));
        Movie = new QMovie(":/engine/images/LogoAnimation.gif",QByteArray(), this);

        connect(Movie, SIGNAL(frameChanged(int)), this, SLOT(UpdateIcon()));
        IsAnimated = false;

    }

    void SystemTrayNotifier::ShowMessage(const QString& title,const QString& message)
    {
        TrayIcon->showMessage(title,message);
    }

    void SystemTrayNotifier::Activated(QSystemTrayIcon::ActivationReason Reason)
    {
        switch(Reason)
        {
            case QSystemTrayIcon::Trigger:
                emit Show();
            break;
        }
    }

    void SystemTrayNotifier::SetContextmenu(QMenu * menu)
    {
        TrayIcon->setContextMenu(menu);
    }

    void SystemTrayNotifier::UpdateIcon()
    {
        if(IsAnimated)
        {
            TrayIcon->setIcon(Movie->currentPixmap());
        }
    }

    void SystemTrayNotifier::ShowAnimation()
    {
        IsAnimated = true;
        Movie->start();
        TrayIcon->show();

    }

    void SystemTrayNotifier::ShowStaticPicture()
    {
        IsAnimated = false;
        Movie->stop();

        TrayIcon->setIcon(QIcon(":/engine/images/Logo.png"));
        TrayIcon->show();
    }

    void SystemTrayNotifier::Init()
    {
        ShowStaticPicture();
    }
    void SystemTrayNotifier::Start()
    {
        ShowAnimation();
    }
    void SystemTrayNotifier::Stop()
    {
        ShowStaticPicture();
    }
}
