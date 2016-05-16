#ifndef DRAGSECTION_H
#define DRAGSECTION_H

#include <QWidget>
#include "dragwidget.h"

class DragSection : public QWidget
{
    Q_OBJECT
    DragWidget* Bottom;
    DragWidget* Top;
    QStringList Data;
signals:
    void ChangedDragSection();
public:
    explicit DragSection(QWidget *parent = 0);
    void Clear();
    void SetData(const QStringList& list,const QList<int>& items);
    QStringList GetData();
    QList<int> SelectedItems();
signals:

private slots:

};

#endif // DRAGSECTION_H
