#ifndef IRESOURCESVISUALIZER_H
#define IRESOURCESVISUALIZER_H
#include "engine_global.h"

#include <QObject>
#include "iresourcewatcher.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  IResourcesVisualizer : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourcesVisualizer(QObject *parent = 0);
        virtual void SetReportData(const QList<IResourceWatcher *>& Data) = 0;
    signals:
        void ChangedState(bool IsEmpty);
    public slots:
        virtual void ShowReport() = 0;
    };
}
#endif // IRESOURCESVISUALIZER_H
