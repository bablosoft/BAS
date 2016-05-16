#include "dragsection.h"
#include <QVBoxLayout>
#include <QLabel>
#include "every_cpp.h"

DragSection::DragSection(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *horizontalLayout = new QVBoxLayout(this);
    Top = new DragWidget(this);
    QLabel * LabelSelected = new QLabel(this);
    LabelSelected->setText(tr("Selected:"));
    LabelSelected->setStyleSheet("QLabel{color:gray;}");
    horizontalLayout->addWidget(LabelSelected);
    horizontalLayout->addWidget(Top);

    connect(Top,SIGNAL(ChangedDragWidget()),this,SIGNAL(ChangedDragSection()));
    Bottom = new DragWidget(this);
    QLabel * LabelAvailable = new QLabel(this);


    LabelAvailable->setText(tr("Available(use drag):"));
    LabelAvailable->setStyleSheet("QLabel{color:gray;margin-top:20px}");
    horizontalLayout->addWidget(LabelAvailable);

    horizontalLayout->addWidget(Bottom);
    connect(Bottom,SIGNAL(ChangedDragWidget()),this,SIGNAL(ChangedDragSection()));
    setLayout(horizontalLayout);

    setContentsMargins(0,0,0,0);
    horizontalLayout->setContentsMargins(0,0,0,0);



    show();
}


QStringList DragSection::GetData()
{
    return Data;
}

void DragSection::Clear()
{
    Top->Clear();
    Bottom->Clear();
    Data.clear();
}

void DragSection::SetData(const QStringList& list,const QList<int>& items)
{
    Clear();
    Data = list;
    QStringList list1;
    QStringList list2;
    for(int i = 0;i<items.size();i++)
    {
        if(items.at(i)>=0 && items.at(i)<list.size())
        {
             list1.append(list.at(items.at(i)));
        }
    }
    for(int i = 0;i<list.size();i++)
    {
        if(!items.contains(i))
        {
            list2.append(list.at(i));
        }
    }
    Top->SetData(list1);
    Bottom->SetData(list2);

    int size = list.size() * 25;
    if(size < 100)
        size = 100;
    else if(size > 250)
        size = 250;
    Top->setMinimumHeight(size);
    Bottom->setMinimumHeight(size);
}

QList<int> DragSection::SelectedItems()
{
     QList<int> res;
     foreach(QString r,Top->GetData())
     {
         int index = Data.indexOf(r);
         if(index >= 0)
         {
             res.append(index);
         }
     }

     return res;
}
