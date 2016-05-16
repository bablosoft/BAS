#ifndef EXTENDEDTABWIDGETVALIDATOR_H
#define EXTENDEDTABWIDGETVALIDATOR_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QLabel>
#include "ExtendedTabWidget.h"
#include "iresourcewidget.h"
#include "toprightpositioner.h"

using namespace BrowserAutomationStudioFramework;

class ExtendedTabWidgetValidator : public QObject
{
    Q_OBJECT
    ExtendedTabWidget *Widget;
    QList<QList<IResourceWidget*> >Data;
    void SetValidation(int index, bool visibility);
    QHash<QPushButton *,QLabel* > ValidationLabels;
public:
    explicit ExtendedTabWidgetValidator(QObject *parent = 0);
    void SetTabWidget(ExtendedTabWidget * Widget);
    void InsertResourceWidget(int index,IResourceWidget* Widget);
signals:

public slots:
private slots:
    void ValidateAll();
    void ResizeAll();
    void ValidationChanged();
};

#endif // EXTENDEDTABWIDGETVALIDATOR_H
