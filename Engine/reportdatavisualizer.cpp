#include "reportdatavisualizer.h"
#include <QMap>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    ReportDataVisualizer::ReportDataVisualizer(QObject *parent) :
        IReportDataVisualizer(parent)
    {
        VisualizerDialog = 0;
    }

    QString SecondsToDHMS(int duration)
    {
        QString res;
        int seconds = (int) (duration % 60);
        duration /= 60;
        int minutes = (int) (duration % 60);
        duration /= 60;
        int hours = (int) (duration % 24);
        int days = (int) (duration / 24);
        if((hours == 0)&&(days == 0))
            return res.sprintf("%02d:%02d", minutes, seconds);
        if (days == 0)
            return res.sprintf("%02d:%02d:%02d", hours, minutes, seconds);
        return res.sprintf("%dd%02d:%02d:%02d", days, hours, minutes, seconds);
    }

    void ReportDataVisualizer::SetReportData(IScriptMultiWorkerReportData* ReportData)
    {
        this->ReportData = ReportData;
    }

    QString ReportDataVisualizer::PrepareHash1(const QHash<QString, int>& hash, const QString& tab)
    {
        QString res;
        QMap<int, QStringList> temp;
        QHash<QString, int>::const_iterator i = hash.constBegin();
        while (i != hash.constEnd())
        {
            if(!temp.contains(i.value()))
                temp.insert(i.value(),QStringList()<<i.key());
            else
            {
                temp[i.value()].append(i.key());
            }
            i++;
        }

        QMapIterator<int, QStringList> i1(temp);
        i1.toBack();
        while (i1.hasPrevious())
        {
            i1.previous();
            foreach(QString str, i1.value())
            {
                res += tab + QString::number(i1.key()) + " - " + str + "\r\n";
            }

        }
        return res;


    }

    QString ReportDataVisualizer::PrepareHash2(const QHash<QString, QPair<int,int> >& hash, const QString& tab)
    {
        QString res;
        QHash<QString, QPair<int,int> >::const_iterator i = hash.constBegin();
        while (i != hash.constEnd())
        {
            res += i.key() + QString(" ") + tr("Solver Used") + QString(" - ") + QString::number(i.value().first) + "\r\n";
            res += tab + tr("Solver Fails") + " - " + QString::number(i.value().second) + "\r\n";
            i++;
        }
        return res;
    }

    QString ReportDataVisualizer::PrepareText()
    {
        if(!ReportData->IsRunAtLeastOnce())
        {
            return tr("Script was not run yet");
        }

        QString res;
        QString tab = "       ";
        res += tr("Success") + "(" + QString::number(ReportData->GetSuccessCount()) + ")\r\n";
        if(ReportData->GetSuccessCount()>0)
            res += tr("Messages") + QString(":\r\n");
        res += PrepareHash1(ReportData->GetSuccessMessages(), tab);
        res += "\r\n";

        if(ReportData->GetSuccessAndRescuedCount()>0)
        {
            res += tr("Success And Rescued") + "(" + QString::number(ReportData->GetSuccessAndRescuedCount()) + ")\r\n";
            res += tr("Messages") + QString(":\r\n");
            res += PrepareHash1(ReportData->GetSuccessAndRescuedMessages(), tab);
            res += "\r\n";
        }



        res += tr("Fails") + "(" + QString::number(ReportData->GetFailCount()) + ")\r\n";
        if(ReportData->GetFailCount()>0)
            res += tr("Messages") + ":\r\n";
        res += PrepareHash1(ReportData->GetFailMessages(), tab);
        res += "\r\n";

        if(ReportData->GetFailAndRescuedCount()>0)
        {
            res += tr("Fails And Rescued") + "(" + QString::number(ReportData->GetFailAndRescuedCount()) + ")\r\n";
            res += tr("Messages") + ":\r\n";
            res += PrepareHash1(ReportData->GetFailAndRescuedMessages(), tab);
            res += "\r\n";
        }

        res += PrepareHash2(ReportData->GetCaptchaStats(), tab);
        res += "\r\n";

        res += tr("Time Spent") + " : " + SecondsToDHMS(ReportData->GetSecondsSpent()) + "\r\n";
        res += "\r\n";
        QString Final = ReportData->GetFinal();
        if(ReportData->IsRunning())
            Final = tr("Still Running");

        res += tr("Final Message") + " : " + Final + "\r\n";
        return res;
    }

    void ReportDataVisualizer::ShowReport()
    {
        if(VisualizerDialog)
        {
            VisualizerDialog->SetData(PrepareText());
            VisualizerDialog->raise();
        }else
        {
            VisualizerDialog = new ReportDataVisualizerDialog();
            connect(VisualizerDialog,SIGNAL(Reload()),this,SLOT(ShowReport()));
            VisualizerDialog->SetData(PrepareText());
            VisualizerDialog->exec();
            delete VisualizerDialog;
            VisualizerDialog = 0;
        }
    }
}
