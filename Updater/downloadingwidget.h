#ifndef DOWNLOADINGWIDGET_H
#define DOWNLOADINGWIDGET_H

#include <QWidget>

namespace Ui {
class DownloadingWidget;
}

class DownloadingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadingWidget(QWidget *parent = 0);
    ~DownloadingWidget();
    void SetProgress(int Progress);
    void HideSkip();
private slots:
    void on_SkipButton_clicked();

private:
    Ui::DownloadingWidget *ui;

signals:
    void Skip();
};

#endif // DOWNLOADINGWIDGET_H
