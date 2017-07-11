#ifndef UICONSTRUCTOR_H
#define UICONSTRUCTOR_H

#include <QWidget>
#include <QList>
#include <QHash>
#include <QTimer>
#include <QPushButton>
#include "multilanguagestring.h"

namespace Ui {
class UIConstructor;
}

using namespace BrowserAutomationStudioFramework;

class UIConstructor : public QWidget
{
    Q_OBJECT

    struct Unit
    {
        QString Name;
        QWidget* WidgetEdit;
    };
    QTimer *TabDragTimer;
    QString DragTabName;
    QString CurrentTab;
    QHash<QString, QList<Unit> > Data;
    QList<QString> Tabs;
    QList<MultiLanguageString> TabsMultilang;
    QString Language;
    int FindUnitNumberOfEvent(const QPoint& Point);
    void PrintTabs();
    bool eventFilter(QObject *target, QEvent *event);
    void MoveToTab(const QString& Text, int offset);
    void EditTab(QPushButton *TabButton);
    void ChangeTab(const QString& TabName);
    void EditUnit(int index);

public:
    explicit UIConstructor(QWidget *parent = 0);
    ~UIConstructor();
    void SetLanguage(const QString& Language);
    void AddUnit(const QString& UnitName,MultiLanguageString& TabNameMulti, QWidget* WidgetToShow);
    void AddUnitToCurrentTab(const QString& UnitName,QWidget* WidgetToShow);
    bool IsClear();
private slots:
    void TabChanged();
    void StartDragTab();
private:
    Ui::UIConstructor *ui;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);


signals:
    void MoveUnitInsideTab(QWidget *From, QWidget *To, bool after);
    void ChangeTab(QWidget *From, MultiLanguageString& TabName);
    void RemoveWidget(QWidget *From);
    void UpdateClearState();
};

#endif // UICONSTRUCTOR_H
