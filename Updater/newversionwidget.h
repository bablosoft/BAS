#ifndef NEWVERSIONWIDGET_H
#define NEWVERSIONWIDGET_H

#include <QWidget>

namespace Ui {
class NewVersionWidget;
}

class NewVersionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewVersionWidget(QWidget *parent = 0);
    ~NewVersionWidget();
    void SetVersion(const QString& Version);
    void SetChangelog(const QString& Changelog);

private slots:
    void on_SkipButton_clicked();

    void on_ApplyButton_clicked();

private:
    Ui::NewVersionWidget *ui;
signals:
    void Skip();
    void Update();
};

#endif // NEWVERSIONWIDGET_H
