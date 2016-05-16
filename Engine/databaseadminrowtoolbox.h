#ifndef DATABASEADMINROWTOOLBOX_H
#define DATABASEADMINROWTOOLBOX_H

#include <QWidget>
#include <QVariant>
namespace Ui {
class DatabaseAdminRowToolbox;
}

class DatabaseAdminRowToolbox : public QWidget
{
    Q_OBJECT
    QString Id;
public:
    explicit DatabaseAdminRowToolbox(QWidget *parent = 0);
    ~DatabaseAdminRowToolbox();
    void SetId(QString Id);

private:
    Ui::DatabaseAdminRowToolbox *ui;
signals:
    void Delete(QString Id);
    void Edit(QString Id);
private slots:
    void on_EditButton_clicked();
    void on_DeleteButton_clicked();
};

#endif // DATABASEADMINROWTOOLBOX_H
