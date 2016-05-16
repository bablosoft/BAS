#ifndef SYSTEMTRAYNOTIFIER_H
#define SYSTEMTRAYNOTIFIER_H
#include "engine_global.h"
#include <QSystemTrayIcon>
#include <QMovie>
#include <QObject>
#include "isystemtraynotifier.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SystemTrayNotifier : public ISystemTrayNotifier
    {
        Q_OBJECT
        void ShowAnimation();
        void ShowStaticPicture();

        bool IsAnimated;
        QSystemTrayIcon *TrayIcon;
        QMovie *Movie;
    public:
        explicit SystemTrayNotifier(QObject *parent = 0);

    signals:

    public slots:
        virtual void Init();
        virtual void Start();
        virtual void Stop();
        virtual void SetContextmenu(QMenu * menu);
        virtual void ShowMessage(const QString& title,const QString& message);
    private slots:
        void UpdateIcon();
        void Activated(QSystemTrayIcon::ActivationReason Reason);
    };
}

#endif // SYSTEMTRAYNOTIFIER_H
