#ifndef TABINPUTDIALOG_H
#define TABINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class TabInputDialog;
}

class TabInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TabInputDialog(QWidget *parent = 0);
    ~TabInputDialog();
    QString GetTabNameEn();
    QString GetTabNameRu();
    void SetTabNameEn(const QString& TabNameEn);
    void SetTabNameRu(const QString& TabNameRu);


private:
    Ui::TabInputDialog *ui;
};

#endif // TABINPUTDIALOG_H
