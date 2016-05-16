#ifndef DATABASEADMINDELETEGROUP_H
#define DATABASEADMINDELETEGROUP_H

#include <QDialog>

namespace Ui {
class DatabaseAdminDeleteGroup;
}

class DatabaseAdminDeleteGroup : public QDialog
{
    Q_OBJECT
    void UpdateChecked();
public:
    explicit DatabaseAdminDeleteGroup(QWidget *parent = 0);
    ~DatabaseAdminDeleteGroup();
    int GetTaskType();
    void SetGroupList(const QString& Groups);
    void Disable(int TaskType);
private:
    Ui::DatabaseAdminDeleteGroup *ui;
};

#endif // DATABASEADMINDELETEGROUP_H
