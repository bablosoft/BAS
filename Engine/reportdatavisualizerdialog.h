#ifndef REPORTDATAVISUALIZERDIALOG_H
#define REPORTDATAVISUALIZERDIALOG_H
#include "engine_global.h"

#include <QObject>
#include <QDialog>

namespace Ui {
class ReportDataVisualizerDialog;
}


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ReportDataVisualizerDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit ReportDataVisualizerDialog(QWidget *parent = 0);
        ~ReportDataVisualizerDialog();
        void SetData(const QString& Data);
        void SetHtml(const QString& Html);
    private:
        Ui::ReportDataVisualizerDialog *ui;
        void changeEvent(QEvent *e);
    public slots:
        void Copy();
    signals:
        void Reload();
    };
}

#endif // REPORTDATAVISUALIZERDIALOG_H
