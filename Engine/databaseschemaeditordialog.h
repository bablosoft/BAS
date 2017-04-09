#ifndef DATABASESCHEMAEDITORDIALOG_H
#define DATABASESCHEMAEDITORDIALOG_H

#include <QDialog>
#include <QList>
#include <QMenuBar>

namespace Ui {
class DatabaseSchemaEditorDialog;
}

class DatabaseSchemaEditorDialog : public QDialog
{
    Q_OBJECT

    struct Column
    {
        QString Name;
        QString DescriptionEn;
        QString DescriptionRu;
        int Id;
        QString Type;
    };

    struct Table
    {
        QString Name;
        QString DescriptionEn;
        QString DescriptionRu;
        int Id;
        QList<Column> Columns;
    };

    struct Model
    {
       QList<Table> Tables;
    }_Model;

    int TableIndex = 1;
    bool IsAccept = false;
    int CurrentTableId = -1;
    QMenuBar * Menu;

public:
    explicit DatabaseSchemaEditorDialog(QWidget *parent = 0);
    ~DatabaseSchemaEditorDialog();
    bool GetIsAccept();
    void ParseXml(const QString& Xml);
    QString GetXml();



private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void ShowContextMenu(const QPoint &pos);
    void ShowContextMenu2(const QPoint &pos);
    void TableChanged();
    void EraseItem();
    void EraseItem2();
    void EditItem2();
    void MoveUp();
    void MoveDown();
    void MoveUp2();
    void MoveDown2();

    void RawMode();
    void ConstructorMode();

    void on_TableName_textEdited(const QString &arg1);

    void on_TableDescriptionEn_textEdited(const QString &arg1);

    void on_TableDescriptionRu_textEdited(const QString &arg1);

    void on_pushButton_AddColumn_clicked();
    int GetMaxTableId();
    int GetMaxColumnId();

private:
    Ui::DatabaseSchemaEditorDialog *ui;


};

#endif // DATABASESCHEMAEDITORDIALOG_H
