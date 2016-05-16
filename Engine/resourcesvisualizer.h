#ifndef RESOURCESVISUALIZER_H
#define RESOURCESVISUALIZER_H
#include "engine_global.h"

#include <QObject>
#include <QTimer>
#include "iresourcesvisualizer.h"
#include "reportdatavisualizerdialog.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  ResourcesVisualizer : public IResourcesVisualizer
    {
        Q_OBJECT
        bool Enabled;
        QList<IResourceWatcher *> Data;
        ReportDataVisualizerDialog *VisualizerDialog;
        QString PrepareText();
        QTimer * Timer;
        QString SecondsToDHMS(int duration);
    public:
        explicit ResourcesVisualizer(QObject *parent = 0);
        virtual void SetReportData(const QList<IResourceWatcher *>& Data);
    signals:

    public slots:
        virtual void ShowReport();
        void SetDisabled();
        void SetEnabled();
    private slots:
        void CheckEnabled();
    };
}

#endif // RESOURCESVISUALIZER_H
