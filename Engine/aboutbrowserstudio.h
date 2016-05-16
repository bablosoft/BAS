#ifndef ABOUTBROWSERSTUDIO_H
#define ABOUTBROWSERSTUDIO_H

#include <QDialog>

namespace Ui {
class AboutBrowserStudio;
}

class AboutBrowserStudio : public QDialog
{
    Q_OBJECT

public:
    explicit AboutBrowserStudio(const QString& Version,const QString& ServerName,QWidget *parent = 0);
    ~AboutBrowserStudio();

private:
    Ui::AboutBrowserStudio *ui;
    void changeEvent(QEvent *e);
};

#endif // ABOUTBROWSERSTUDIO_H
