#ifndef SAFEAPPLICATION_H
#define SAFEAPPLICATION_H

#include <QApplication>
#include "engine_global.h"
#include "ilogger.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  SafeApplication : public QApplication
    {
        Q_OBJECT
        ILogger *Logger;
    public:
        SafeApplication(int &argc, char *argv[]);
        void SetLogger(ILogger *Logger);
        virtual bool notify(QObject * receiver, QEvent * event);
    signals:

    public slots:

    };
}
#endif // SAFEAPPLICATION_H
