#ifndef DATABASEGROUPWIDGET_H
#define DATABASEGROUPWIDGET_H

#include <QWidget>
#include <QVariant>
namespace Ui {
class DatabaseGroupWidget;
}

class DatabaseGroupWidget : public QWidget
{
    Q_OBJECT
    QString Id;
    bool IsSelected;
    void UpdateIsSelected();
    QString Filter;
    QString ColorSelected;
    QString ColorNotSelected;
public:
    void SetName(const QString& Name);
    void SetDescription(const QString& Description);
    void SetId(QString Id);
    QString GetId();
    void SetFilter(const QString& Filter);
    bool IsFiltered();
    QString GetName();
    QString GetDescription();
    void SetSelected(bool IsSelected);
    bool GetSelected();
    explicit DatabaseGroupWidget(QWidget *parent = 0);
    ~DatabaseGroupWidget();
    void mouseReleaseEvent( QMouseEvent * event );

private:
    Ui::DatabaseGroupWidget *ui;
signals:
    void DeleteWithData(QString);
    void DeleteWithoutData(QString);
    void ClearData(QString);
    void Edit(QString, QString, QString);
    void Copy(QString, QString, QString);
    void Selected(QString, bool);
private slots:
    void on_EditButton_clicked();
    void on_CopyButton_clicked();
    void on_DeleteButton_clicked();

    //void on_SelectedButton_clicked();
};

#endif // DATABASEGROUPWIDGET_H
