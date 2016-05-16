#ifndef DATABASEADMINMOVETOGROUP_H
#define DATABASEADMINMOVETOGROUP_H

#include <QDialog>

namespace Ui {
class DatabaseAdminMoveToGroup;
}

class DatabaseAdminMoveToGroup : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseAdminMoveToGroup(QWidget *parent = 0);
    ~DatabaseAdminMoveToGroup();
    void SetNumberRows(int RowsNumber);
    void SetGroups(QStringList Groups);
    int GetSelectedGroupIndex();
private:
    Ui::DatabaseAdminMoveToGroup *ui;
};

#endif // DATABASEADMINMOVETOGROUP_H
