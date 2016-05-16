#ifndef DATABASEADMINFILTERITEM_H
#define DATABASEADMINFILTERITEM_H

#include <QWidget>

namespace Ui {
class DatabaseAdminFilterItem;
}

class DatabaseAdminFilterItem : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseAdminFilterItem(QWidget *parent = 0);
    ~DatabaseAdminFilterItem();
    void SetText(const QString& Text);
private:
    Ui::DatabaseAdminFilterItem *ui;
signals:
    void NeedDelete();
private slots:
    void on_pushButton_clicked();
};

#endif // DATABASEADMINFILTERITEM_H
