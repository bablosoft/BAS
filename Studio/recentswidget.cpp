#include "recentswidget.h"
#include "ui_recentswidget.h"
#include <QSettings>
#include <QByteArray>
#include <QLabel>
#include <QFileInfo>
#include <QWidget>
#include <QDebug>

RecentsWidget::RecentsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecentsWidget)
{
    ui->setupUi(this);
    WasReload = false;
}

void RecentsWidget::Reload(const QString& CurrentFile)
{
    if(WasReload)
        return;

    WasReload = true;

    QSettings Settings("settings.ini",QSettings::IniFormat);
    QString RecentProjects = Settings.value("RecentProjects",QString()).toString();
    int it = 0;
    for(QString RecentEncoded:RecentProjects.split(","))
    {
        if(it>=5)
            break;
        QString Recent = QString::fromUtf8(QByteArray::fromBase64(RecentEncoded.toUtf8()));
        if(Recent == CurrentFile)
        {
            continue;
        }
        if(QFileInfo(Recent).exists())
        {
            QLabel * Label = new QLabel(this);

            Label->setProperty("file",QVariant(Recent));
            connect(Label,SIGNAL(linkActivated(QString)),this,SLOT(ButtonClicked()));
            QString FileName = QFileInfo(Recent).fileName();
            QString FilePath = Recent;
            int max_lent = 100;
            if(FileName.length()>max_lent)
                FileName = FileName.left(max_lent - 3) + "...";
            if(FilePath.length()>max_lent)
                FilePath = FilePath.left(max_lent - 3) + "...";
            Label->setText(QString("<html><head/><body><a href=\"bas://loadproject\" style=\" text-decoration: none;\"> <table style=\"margin-bottom:10px\"><tr><td rowspan=\"2\"><img src=\":/engine/images/open.png\"/></td><td><div>&nbsp;&nbsp;<span style=\" text-decoration: underline; color:white\">%1</span></div></td></tr><tr><td><div>&nbsp;&nbsp;<span style=\"color:gray;\">%2</span></div></td></tr></table></a></body></html>").arg(FileName).arg(FilePath));
            Label->setToolTip(Recent);
            ui->Container->layout()->addWidget(Label);
            it++;
        }

    }
    if(!it)
        setVisible(false);
}

void RecentsWidget::ButtonClicked()
{
    QString File = sender()->property("file").toString();
    emit FileSelected(File);
}

void RecentsWidget::OpenFile(const QString& File)
{
    if(File.isEmpty())
        return;
    QSettings Settings("settings.ini",QSettings::IniFormat);

    QString RecentProjects = Settings.value("RecentProjects",QString()).toString();
    QStringList List = RecentProjects.split(",");
    QString FileEncrypted = QString::fromUtf8(File.toUtf8().toBase64());
    List.removeAll(FileEncrypted);
    List.push_front(FileEncrypted);
    List = List.mid(0,20);
    Settings.setValue("RecentProjects",List.join(","));
}

RecentsWidget::~RecentsWidget()
{
    delete ui;
}
