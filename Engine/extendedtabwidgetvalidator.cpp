#include "extendedtabwidgetvalidator.h"
#include "toprightpositioner.h"
#include <QFontMetrics>
#include <QFont>
#include "every_cpp.h"



ExtendedTabWidgetValidator::ExtendedTabWidgetValidator(QObject *parent) :
    QObject(parent)
{
}

void ExtendedTabWidgetValidator::SetTabWidget(ExtendedTabWidget * Widget)
{
    this->Widget = Widget;

    int len = Data.length();
    for(int i = 0;i<len;i++)
    {
        QList<IResourceWidget *> list = Data.at(i);

        foreach(IResourceWidget * w,list)
        {
            connect(w,SIGNAL(RequiresValidationStateChanged(bool)),this,SLOT(ValidationChanged()));
        }

    }

    ValidateAll();
    ResizeAll();

}

void ExtendedTabWidgetValidator::ResizeAll()
{
    int len = Data.length();


    for(int i = 0;i<len;i++)
    {
        QPushButton *button = Widget->GetButton(i);
        QFontMetrics Metrics(button->font());
        button->setMinimumWidth(Metrics.boundingRect(button->text()).width()+50);
    }

}


void ExtendedTabWidgetValidator::SetValidation(int index, bool visibility)
{
    QPushButton *button = Widget->GetButton(index);
    QLabel* label;
    if(!ValidationLabels.contains(button))
    {
        label = new QLabel();
        QPixmap pixmap(":/engine/images/invalid.png");
        pixmap = pixmap.scaled(pixmap.width(),button->sizeHint().height() - 2);

        //pixmap.scaled()
        label->setPixmap(pixmap);

        label->setMaximumWidth(pixmap.width());
        label->setMinimumWidth(pixmap.width());
        label->setMaximumHeight(pixmap.height());
        label->setMinimumHeight(pixmap.height());
        TopRightPositioner *Pos = new TopRightPositioner(this);
        Pos->SetChild(label);
        Pos->SetParent(button);
        Pos->SetMarginRight(1);
        Pos->SetMarginTop(1);
        Pos->Start();

        ValidationLabels[button] = label;
    }else
    {
        label = ValidationLabels.value(button);
    }
    label->setVisible(visibility);

}

void ExtendedTabWidgetValidator::ValidateAll()
{
    int len = Data.length();
    for(int i = 0;i<len;i++)
    {
        QList<IResourceWidget *> list = Data.at(i);
        bool IsValid = true;
        foreach(IResourceWidget * w,list)
        {
            if(!w->IsValid() && w->GetRequiresValidation())
            {
                IsValid = false;
                break;
            }
        }
        SetValidation(i,!IsValid);
    }
}

void ExtendedTabWidgetValidator::ValidationChanged()
{
    IResourceWidget * Widget = qobject_cast<IResourceWidget *>(sender());
    int len = Data.length();
    for(int i = 0;i<len;i++)
    {
        QList<IResourceWidget *> list = Data.at(i);
        if(list.contains(Widget))
        {
            bool IsValid = true;
            foreach(IResourceWidget * w,list)
            {
                if(!w->IsValid() && w->GetRequiresValidation() )
                {
                    IsValid = false;
                    break;
                }
            }
            SetValidation(i,!IsValid);
            break;
        }
    }
}


void ExtendedTabWidgetValidator::InsertResourceWidget(int index,IResourceWidget* Widget)
{
    connect(Widget,SIGNAL(ValidationStateChanged()),this,SLOT(ValidationChanged()));
    //connect(Widget,SIGNAL(VisibilityChanged(bool)),this,SLOT(ValidationChanged()));

    while(index>=Data.count())
        Data.append(QList<IResourceWidget*>());

    Data[index].append(Widget);


}
