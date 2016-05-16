#ifndef IREPORTDATAVISUALIZER_H
#define IREPORTDATAVISUALIZER_H
#include "engine_global.h"

#include <QObject>
#include "iscriptmultiworkerreportdata.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IReportDataVisualizer : public QObject
    {

        Q_OBJECT
    public:
        explicit IReportDataVisualizer(QObject *parent = 0);
        virtual void SetReportData(IScriptMultiWorkerReportData* ReportData) = 0;
    signals:

    public slots:
        virtual void ShowReport() = 0;
    };
}

#endif // IREPORTDATAVISUALIZER_H
