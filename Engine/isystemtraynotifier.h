#ifndef ISYSTEMTRAYNOTIFIER_H
#define ISYSTEMTRAYNOTIFIER_H

#include "engine_global.h"

#include <QObject>
#include <QMenu>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ISystemTrayNotifier: public QObject
    {
            Q_OBJECT
        public:
            explicit ISystemTrayNotifier(QObject *parent = 0);

        signals:
            void Show();
        public slots:
            virtual void Init() = 0;
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void ShowMessage(const QString& title,const QString& message) = 0;
            virtual void SetContextmenu(QMenu * menu) = 0;

    };
}
#endif // ISYSTEMTRAYNOTIFIER_H
