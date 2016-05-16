#ifndef RECENTSWIDGET_H
#define RECENTSWIDGET_H

#include <QWidget>

namespace Ui {
class RecentsWidget;
}

class RecentsWidget : public QWidget
{
    Q_OBJECT
    bool WasReload;
public:
    explicit RecentsWidget(QWidget *parent = 0);
    ~RecentsWidget();
    void Reload(const QString& CurrentFile);
    void OpenFile(const QString& File);

signals:
    void FileSelected(QString);

private:
    Ui::RecentsWidget *ui;
private slots:
    void ButtonClicked();

};

#endif // RECENTSWIDGET_H
