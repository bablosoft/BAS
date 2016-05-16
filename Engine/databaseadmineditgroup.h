#ifndef DATABASEADMINEDITGROUP_H
#define DATABASEADMINEDITGROUP_H

#include <QDialog>

namespace Ui {
class DatabaseAdminEditGroup;
}

class DatabaseAdminEditGroup : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseAdminEditGroup(QWidget *parent = 0);
    ~DatabaseAdminEditGroup();
    void SetName(const QString& Name);
    void SetDescription(const QString& Description);
    QString GetName();
    QString GetDescription();
private:
    Ui::DatabaseAdminEditGroup *ui;
};

#endif // DATABASEADMINEDITGROUP_H
