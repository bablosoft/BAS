#include "multiselect.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include "dragsection.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    MultiSelect::MultiSelect(QWidget *parent) :
        QWidget(parent)
    {
        QVBoxLayout *l = new QVBoxLayout(this);
        l->setContentsMargins(0,0,0,0);
        setLayout(l);

    }

    void MultiSelect::Clear()
    {
        disconnect();
        while(layout()->count()>0)
        {
            QLayoutItem* item = layout()->itemAt(0);
            if(item)
            {
                layout()->removeItem( item );
                QWidget* widget = item->widget();
                if(widget)
                {
                    layout()->removeWidget(widget);
                    delete widget;
                }
                delete item;
            }
        }
    }

    void MultiSelect::DragAndDropChanged()
    {
        emit ValueChanged(GetSelectedValue());
    }

    void MultiSelect::RadioToggle(bool checked)
    {
        QRadioButton *radio = qobject_cast<QRadioButton *>(sender());
        emit ValueChanged(radio->text());
    }

    void MultiSelect::CheckBoxToggle()
    {
        emit ValueChanged(GetSelectedValue());
    }


    void MultiSelect::Update(const QString& Type, const QStringList &Lines, QList<int> Selected)
    {
        Clear();
        this->Type = Type;
        if(Type == "DragAndDrop")
        {
            DragSection * Drag = new DragSection(this);
            Drag->SetData(Lines,Selected);
            layout()->addWidget(Drag);
            connect(Drag,SIGNAL(ChangedDragSection()),this,SLOT(DragAndDropChanged()));
        }

        QComboBox * box = 0;

        if(Type == "Combo")
        {
            box = new QComboBox(this);
            layout()->addWidget(box);
            connect(box, SIGNAL(currentTextChanged(QString)), this, SIGNAL(ValueChanged(QString)));
        }
        QWidget * CheckArea = 0;
        if(Type == "Check" || Type == "Radio")
        {
            QScrollArea * Area = new QScrollArea(this);
            layout()->addWidget(Area);
            CheckArea = new QWidget(Area);
            Area->setWidget(CheckArea);
            QVBoxLayout *L = new QVBoxLayout(CheckArea);
            L->setSizeConstraint(QLayout::SetMinAndMaxSize);
            L->setAlignment(Qt::AlignVCenter);
            CheckArea->setLayout(L);
            Area->setWidgetResizable(true);
            CheckArea->setMinimumHeight(0);
            Area->setMinimumHeight(0);
            Area->setFrameShape(QFrame::NoFrame);
        }

        for(int i = 0;i<Lines.size();i++)
        {
            bool checked = Selected.contains(i);
            if(Type == "Radio")
            {
                QRadioButton *radio = new QRadioButton(CheckArea);
                connect(radio,SIGNAL(toggled(bool)),this,SLOT(RadioToggle(bool)));
                radio->setText(Lines.at(i));
                CheckArea->layout()->addWidget(radio);
                if(checked || i == 0)
                    radio->setChecked(true);
            }else if(Type == "Check")
            {
                QCheckBox *check = new QCheckBox(CheckArea);
                connect(check,SIGNAL(toggled(bool)),this,SLOT(CheckBoxToggle()));
                check->setText(Lines.at(i));
                CheckArea->layout()->addWidget(check);
                if(checked)
                    check->setChecked(true);
            }else if(Type == "Combo")
            {
                box->addItem(Lines.at(i));
            }
        }


        if(Type == "Combo" && Selected.length()>0)
            box->setCurrentIndex(Selected.at(0));



    }
    QString MultiSelect::GetSelectedValue()
    {
        QStringList res;
        QStringList Values = GetValues();
        foreach(int i, GetSelectedIndex())
        {
            if(i>=0 && i<Values.size())
            {
                res.append(Values.at(i));
            }
        }
        return res.join(",");

    }
    QList<int> MultiSelect::GetSelectedIndex()
    {
        QList<int> res;
        if(Type == "DragAndDrop")
        {
            DragSection *drag = findChild<DragSection *>();
            res = drag->SelectedItems();
        }else if(Type == "Combo")
        {
            QComboBox *combo = findChild<QComboBox *>();
            res = QList<int>()<<combo->currentIndex();
        }else if(Type == "Radio")
        {
            QList<QRadioButton *> radios = findChildren<QRadioButton *>();
            if(radios.length() > 0)
            {
                int index = 0;
                foreach(QRadioButton *radio,radios)
                {
                    if(radio->isChecked())
                    {
                        res = QList<int>()<<index;
                    }
                    index++;
                }
            }
        }else if(Type == "Check")
        {
            QList<QCheckBox *> checks = findChildren<QCheckBox *>();
            int index = 0;
            foreach(QCheckBox *check,checks)
            {
                if(check->isChecked())
                {
                    res.append(index);
                }
                index++;
            }
        }
        return res;
    }
    QString MultiSelect::GetType()
    {
        return Type;
    }


    QStringList MultiSelect::GetValues()
    {
        QStringList values;
        if(Type == "DragAndDrop")
        {
            DragSection *drag = findChild<DragSection *>();
            values = drag->GetData();
        }else if(Type == "Combo")
        {
            QComboBox *combo = findChild<QComboBox *>();
            int len = combo->count();
            for(int i = 0;i<len;i++)
                values.append(combo->itemText(i));

        }else if(Type == "Radio")
        {
            QList<QRadioButton *> radios = findChildren<QRadioButton *>();
            foreach(QRadioButton *radio,radios)
            {
                values.append(radio->text());
            }
        }else if(Type == "Check")
        {
            QList<QCheckBox *> checks = findChildren<QCheckBox *>();
            foreach(QCheckBox *check,checks)
            {
                values.append(check->text());
            }
        }
        return values;
    }



}
