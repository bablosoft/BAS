#ifndef CHECKFORUPDATESWIDGET_H
#define CHECKFORUPDATESWIDGET_H

#include <QWidget>

namespace Ui {
class CheckForUpdatesWidget;
}

class CheckForUpdatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckForUpdatesWidget(QWidget *parent = 0);
    ~CheckForUpdatesWidget();

private slots:
    void on_SkipButton_clicked();

private:
    Ui::CheckForUpdatesWidget *ui;
signals:
    void Skip();

};

#endif // CHECKFORUPDATESWIDGET_H
