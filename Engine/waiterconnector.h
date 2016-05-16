#ifndef WAITERCONNECTOR_H
#define WAITERCONNECTOR_H

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class WaiterConnector : public QObject
    {
        Q_OBJECT
    public:
        explicit WaiterConnector(QObject *parent = 0);

    signals:
        void signal();
    public slots:
        void slot();
        void end();
    };
}

#endif // WAITERCONNECTOR_H
