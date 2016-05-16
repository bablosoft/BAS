#include "waiterconnector.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    WaiterConnector::WaiterConnector(QObject *parent) :
        QObject(parent)
    {
    }
    void WaiterConnector::slot()
    {
        emit signal();
        this->disconnect();
        this->deleteLater();
    }
    void WaiterConnector::end()
    {
        this->disconnect();
        this->deleteLater();
    }
}
