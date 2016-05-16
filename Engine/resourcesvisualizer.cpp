#include "resourcesvisualizer.h"
#include <QIcon>
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    ResourcesVisualizer::ResourcesVisualizer(QObject *parent) :
        IResourcesVisualizer(parent)
    {
        Enabled = false;
        VisualizerDialog = 0;
        Timer = new QTimer(this);
        Timer->setInterval(5000);
        Timer->setSingleShot(false);
        connect(Timer,SIGNAL(timeout()),this,SLOT(CheckEnabled()));
        Timer->start();
    }
    void ResourcesVisualizer::CheckEnabled()
    {
        if(!Enabled)
            return;

        bool IsEmpty = false;
        for(int i = 0;i<Data.length();i++)
        {
            IResourceWatcher *Watcher = Data.at(i);
            if(Watcher->IsDisabled())
            {
                continue;
            }
            int IntReadyNumber = Watcher->GetReadyCount();
            if(IntReadyNumber <= 0)
            {
                IsEmpty = true;
                break;
            }
        }
        emit ChangedState(IsEmpty);
    }

    QString ResourcesVisualizer::SecondsToDHMS(int duration)
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

    void ResourcesVisualizer::SetReportData(const QList<IResourceWatcher *>& Data)
    {
        this->Data = Data;
    }
    QString ResourcesVisualizer::PrepareText()
    {
        if(!Enabled)
            return QString();
        if(Data.length() == 0)
            return tr("Resources list is empty");


        QString res;
        for(int i = 0;i<Data.length();i++)
        {
            IResourceWatcher *Watcher = Data.at(i);
            if(Watcher->IsDisabled())
            {
                continue;
            }
            res += QString("<strong>") + Watcher->GetName() + QString("</strong>");
            res += QString(": ");
            int IntReadyNumber = Watcher->GetReadyCount();
            QString StringReadyNumber = QString("<strong>") + QString::number(IntReadyNumber) + QString("</strong>");

            if(IntReadyNumber == 0)
            {
                StringReadyNumber = QString("<span style='color:red'>") + StringReadyNumber + QString("</span>");
            }
            res += StringReadyNumber;
            int RenewInSeconds = Watcher->GetRenewInSeconds();
            if(RenewInSeconds >= 0)
                res += QString(", ") + tr("Renew in ") + SecondsToDHMS(RenewInSeconds);
            res += "<br>";
        }

        return res;
    }
    void ResourcesVisualizer::ShowReport()
    {
        if(!Enabled)
            return;
        if(VisualizerDialog)
        {
            VisualizerDialog->SetHtml(PrepareText());
            VisualizerDialog->raise();
        }else
        {
            VisualizerDialog = new ReportDataVisualizerDialog();
            VisualizerDialog->setWindowIcon(QIcon(":/engine/images/resources_ok.png"));
            VisualizerDialog->setWindowTitle(tr("Resources Report"));
            connect(VisualizerDialog,SIGNAL(Reload()),this,SLOT(ShowReport()));
            VisualizerDialog->SetHtml(PrepareText());
            VisualizerDialog->exec();
            delete VisualizerDialog;
            VisualizerDialog = 0;
        }
    }
    void ResourcesVisualizer::SetDisabled()
    {
        if(VisualizerDialog)
        {
            VisualizerDialog->hide();
        }
        Enabled = false;
    }
    void ResourcesVisualizer::SetEnabled()
    {
        Enabled = true;
    }

}
