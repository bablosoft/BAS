#ifndef UPDATEPROGRESS_H
#define UPDATEPROGRESS_H

#include <QMainWindow>

namespace Ui {
class UpdateProgress;
}

#include "checkforupdateswidget.h"
#include "newversionwidget.h"
#include "downloadingwidget.h"

class UpdateProgress : public QMainWindow
{
    Q_OBJECT
    CheckForUpdatesWidget *_CheckForUpdatesWidget;
    NewVersionWidget *_NewVersionWidget;
    DownloadingWidget *_DownloadingWidget;
public:
    explicit UpdateProgress(QWidget *parent = 0);
    ~UpdateProgress();

    void SetStageCheckForUpdates();
    void SetStageNewVersion();
    void SetStageDownloading(bool CanSkip);

    void SetVersionNumber(const QString &Version);
    void SetChangelog(const QString &Changelog);
    void SetProgress(int Progress);

signals:
    void Skip();
    void Update();

private:
    Ui::UpdateProgress *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // UPDATEPROGRESS_H
