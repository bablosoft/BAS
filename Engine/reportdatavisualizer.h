#ifndef REPORTDATAVISUALIZER_H
#define REPORTDATAVISUALIZER_H
#include "engine_global.h"

#include <QObject>
#include "ireportdatavisualizer.h"
#include "reportdatavisualizerdialog.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ReportDataVisualizer : public IReportDataVisualizer
    {
        Q_OBJECT
        ReportDataVisualizerDialog *VisualizerDialog;
        IScriptMultiWorkerReportData* ReportData;
        QString PrepareText();
        QString PrepareHash1(const QHash<QString, int>& hash, const QString& tab);
        QString PrepareHash2(const QHash<QString, QPair<int,int> >& hash, const QString& tab);
    public:
        explicit ReportDataVisualizer(QObject *parent = 0);
        virtual void SetReportData(IScriptMultiWorkerReportData* ReportData);
    signals:

    public slots:
        virtual void ShowReport();
    };
}

#endif // REPORTDATAVISUALIZER_H
