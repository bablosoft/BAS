#ifndef DATABASEADMIN_H
#define DATABASEADMIN_H

#include <QWidget>
#include "engine_global.h"
#include "idatabaseconnector.h"
#include "databasegroupwidget.h"
#include <QLabel>
#include <QMovie>


namespace Ui {
class DatabaseAdmin;
}

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DatabaseAdmin : public QWidget
    {
        Q_OBJECT
        IDatabaseConnector *DatabaseConnector;

        void RefreshTable();
        QList<DatabaseGroupWidget *> GroupWidgets;
        void InsertGroupInsideInterface(DatabaseGroup Group, int index);
        int GetGroupArrayIndexByDatabaseId(QString Id);
        enum SelectTarget{Delete,Raw};
        QList<DatabaseGroupWidget *> GetSelectedGroups(SelectTarget Target);
        void SetGroupsToTable();

        QWidget * DeactivateWidget;
        QLabel * DeactivateLabel;
        QMovie * Movie;
        bool IsDeactivated;

    public:
        explicit DatabaseAdmin(QWidget *parent = 0);
        ~DatabaseAdmin();
        void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);

    private:
        Ui::DatabaseAdmin *ui;
    public slots:
        void Show();
    signals:


    private slots:
        void on_RefreshButton_clicked();
        void on_Tables_activated(int index);
        void DeleteWithData(QString Id);
        void DeleteWithoutData(QString Id);
        void ClearData(QString Id);
        void EditGroup(QString Id,QString Name,QString Description);
        void CopyGroup(QString Id,QString Name,QString Description);
        void SelectedGroup(QString GroupId, bool IsSelected);
        void on_AddGroup_clicked();
        void on_SelectAllGroups_clicked();
        void on_SelectNoGroups_clicked();
        void on_DeleteSelectedGroups_clicked();
        void on_EditGroupFilter_textChanged(const QString &arg1);
        void on_ClearDatabaseFilter_clicked();
        void on_DeleteAllButton_clicked();
        void Deactivate();
        void Activate();
        void on_ImportCsv_clicked();
        void on_ExportCsv_clicked();
        void on_Backup_clicked();
        void on_Restore_clicked();
        void on_ExportXls_clicked();
        void on_MenuButton_clicked();
        void RefreshData();
    };
}

#endif // DATABASEADMIN_H
