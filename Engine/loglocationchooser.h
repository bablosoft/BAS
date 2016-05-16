#ifndef LOGLOCATIONCHOOSER_H
#define LOGLOCATIONCHOOSER_H
#include "engine_global.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class LogLocationChooser;
}

class ENGINESHARED_EXPORT LogLocationChooser : public QDialog
{
    Q_OBJECT
public:
    explicit LogLocationChooser(QWidget *parent = 0);
    ~LogLocationChooser();
    QString GetLogLocation();
    void SetLogLocation(const QString& Location);
private slots:
    void on_pushButton_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::LogLocationChooser *ui;
};

#endif // LOGLOCATIONCHOOSER_H
