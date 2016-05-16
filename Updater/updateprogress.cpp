#include "updateprogress.h"
#include "ui_updateprogress.h"
#include <QTimer>

UpdateProgress::UpdateProgress(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateProgress)
{
    ui->setupUi(this);
}

UpdateProgress::~UpdateProgress()
{
    delete ui;
}

void UpdateProgress::SetStageCheckForUpdates()
{
    if(centralWidget())
    {
        centralWidget()->deleteLater();
    }
    _NewVersionWidget = 0;
    _CheckForUpdatesWidget = 0;
    _DownloadingWidget = 0;

    _CheckForUpdatesWidget = new CheckForUpdatesWidget(this);
    connect(_CheckForUpdatesWidget,SIGNAL(Skip()),this,SIGNAL(Skip()));
    this->setMinimumHeight(_CheckForUpdatesWidget->height());
    this->setMaximumHeight(_CheckForUpdatesWidget->height());
    this->setMinimumWidth(_CheckForUpdatesWidget->width());
    this->setMaximumWidth(_CheckForUpdatesWidget->width());

    setCentralWidget(_CheckForUpdatesWidget);
    QTimer::singleShot(1000,this,SLOT(show()));
}

void UpdateProgress::SetStageNewVersion()
{

    if(centralWidget())
    {
        centralWidget()->deleteLater();
    }

    _NewVersionWidget = 0;
    _CheckForUpdatesWidget = 0;
    _DownloadingWidget = 0;

    _NewVersionWidget = new NewVersionWidget(this);
    connect(_NewVersionWidget,SIGNAL(Skip()),this,SIGNAL(Skip()));
    connect(_NewVersionWidget,SIGNAL(Update()),this,SIGNAL(Update()));
    this->setMinimumHeight(_NewVersionWidget->height());
    this->setMaximumHeight(_NewVersionWidget->height());
    this->setMinimumWidth(_NewVersionWidget->width());
    this->setMaximumWidth(_NewVersionWidget->width());

    setCentralWidget(_NewVersionWidget);
    show();
}

void UpdateProgress::closeEvent(QCloseEvent *event)
{
    emit Skip();
}

void UpdateProgress::SetStageDownloading(bool CanSkip)
{
    if(centralWidget())
    {
        centralWidget()->deleteLater();
    }
    _NewVersionWidget = 0;
    _CheckForUpdatesWidget = 0;
    _DownloadingWidget = 0;

    _DownloadingWidget = new DownloadingWidget(this);
    if(!CanSkip)
        _DownloadingWidget->HideSkip();
    connect(_DownloadingWidget,SIGNAL(Skip()),this,SIGNAL(Skip()));
    this->setMinimumHeight(_DownloadingWidget->height());
    this->setMaximumHeight(_DownloadingWidget->height());
    this->setMinimumWidth(_DownloadingWidget->width());
    this->setMaximumWidth(_DownloadingWidget->width());

    setCentralWidget(_DownloadingWidget);
}

void UpdateProgress::SetVersionNumber(const QString &Version)
{
    if(_NewVersionWidget)
        _NewVersionWidget ->SetVersion(Version);
}

void UpdateProgress::SetChangelog(const QString &Changelog)
{
    if(_NewVersionWidget)
        _NewVersionWidget ->SetChangelog(Changelog);
}

void UpdateProgress::SetProgress(int Progress)
{
    if(_DownloadingWidget)
        _DownloadingWidget ->SetProgress(Progress);
}
