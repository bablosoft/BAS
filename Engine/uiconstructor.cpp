#include "uiconstructor.h"
#include "ui_uiconstructor.h"
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include "iresourcewidget.h"

#include "tabinputdialog.h"

UIConstructor::UIConstructor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIConstructor)
{
    ui->setupUi(this);
    ui->TabsList->layout()->setAlignment(Qt::AlignTop);
    setAcceptDrops(true);
    TabDragTimer = new QTimer(this);
    TabDragTimer->setSingleShot(true);
    TabDragTimer->setInterval(400);
    connect(TabDragTimer,SIGNAL(timeout()),this,SLOT(StartDragTab()));


}

bool UIConstructor::IsClear()
{
    return Tabs.isEmpty();
}

void UIConstructor::StartDragTab()
{
    int index = Tabs.indexOf(DragTabName);
    if(index<0)
        return;
    QPushButton * TabButton = qobject_cast<QPushButton *>(ui->TabsList->layout()->itemAt(index + 1)->widget());

    QSize size = TabButton->size();
    QRegion region = QRegion(0,0,size.width(),size.height());
    QPixmap pixmap(size);
    TabButton->render(&pixmap, QPoint(),region );
    QString text = TabButton->text();
    if(text == tr("<No Tab>"))
        text.clear();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << text;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnduiconstructdatatab", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(-10,-10));

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    Qt::DropAction action = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
}

void UIConstructor::SetLanguage(const QString& Language)
{
    this->Language = Language;
}

void UIConstructor::AddUnit(const QString& UnitName,MultiLanguageString& TabNameMulti, QWidget* WidgetToShow)
{
    QString TabName = TabNameMulti.GetTranslation(Language);
    Unit u;
    u.Name = UnitName;
    u.WidgetEdit = WidgetToShow;
    QWidget *w;
    if(Data.contains(TabName))
    {
        w = ui->stackedWidget->widget(Tabs.indexOf(TabName));
    }else
    {
        w = new QWidget();
        QVBoxLayout *l = new QVBoxLayout(w);
        l->setAlignment(Qt::AlignTop);
        w->setLayout(l);
        l->setSpacing(1);
        l->setContentsMargins(0,0,0,0);
        ui->stackedWidget->addWidget(w);

        Tabs.append(TabName);
        TabsMultilang.append(TabNameMulti);

        QPushButton * TabButton = new QPushButton(ui->TabsList);


        TabButton->installEventFilter(this);
        connect(TabButton,SIGNAL(clicked(bool)),this,SLOT(TabChanged()));
        TabButton->setCheckable(true);
        if(Data.isEmpty())
        {
            TabButton->setChecked(true);
            CurrentTab = TabName;
        }
        if(TabName.isEmpty())
        {
            TabButton->setText(tr("<No Tab>"));
        }else
            TabButton->setText(TabName);

        ui->TabsList->layout()->addWidget(TabButton);

    }

    QLabel *l = new QLabel(w);
    l->installEventFilter(this);


    l->setMouseTracking(true);
    l->setCursor(QCursor(Qt::OpenHandCursor));

    l->setStyleSheet("*{border:1px solid gray}");
    l->setText(UnitName);
    l->setMargin(7);
    //l->setAttribute(Qt::WA_DeleteOnClose);

    w->layout()->addWidget(l);

    Data[TabName].append(u);


}

void UIConstructor::AddUnitToCurrentTab(const QString& UnitName,QWidget* WidgetToShow)
{
    MultiLanguageString TabNameMulti;
    if(!Data.isEmpty())
    {
        int index = Tabs.indexOf(CurrentTab);
        TabNameMulti = TabsMultilang[index];
    }
    else
    {
        CurrentTab.clear();
    }
    AddUnit(UnitName,TabNameMulti,WidgetToShow);
    emit ChangeTab(WidgetToShow,TabNameMulti);
}


void UIConstructor::TabChanged()
{
    QPushButton * ClickButton = qobject_cast<QPushButton *>(sender());
    for(QPushButton * b:ui->TabsList->findChildren<QPushButton *>())
    {
        if(b!=ClickButton)
        {
            b->setChecked(false);
        }
    }
    ClickButton->setChecked(true);
    QString text = ClickButton->text();
    if(text == tr("<No Tab>"))
    {
        text.clear();
    }

    ui->stackedWidget->setCurrentIndex(Tabs.indexOf(text));
    CurrentTab = text;

}

void UIConstructor::ChangeTab(const QString& TabName)
{
    for(QPushButton * b:ui->TabsList->findChildren<QPushButton *>())
    {
        QString Text = b->text();
        if(Text == tr("<No Tab>"))
        {
            Text.clear();
        }
        b->setChecked(Text == TabName);

    }
    ui->stackedWidget->setCurrentIndex(Tabs.indexOf(TabName));
    CurrentTab = TabName;
}

void UIConstructor::EditTab(QPushButton *TabButton)
{
    TabInputDialog Dialog;
    QString Text;
    Text = TabButton->text();
    if(Text == tr("<No Tab>"))
    {
        Text.clear();
    }
    MultiLanguageString ms;
    int index = Tabs.indexOf(Text);
    ms = TabsMultilang[index];
    Dialog.SetTabNameEn(ms.GetTranslation("en"));
    Dialog.SetTabNameRu(ms.GetTranslation("ru"));
    if(Dialog.exec())
    {
        ms.SetTranslation("en",Dialog.GetTabNameEn());
        ms.SetTranslation("ru",Dialog.GetTabNameRu());
        TabsMultilang[index] = ms;
        QString TextNew = ms.GetTranslation(Language);
        if(!Tabs.contains(TextNew))
        {
            if(CurrentTab == Text)
            {
               CurrentTab = TextNew;
            }
            Tabs[index] = TextNew;
            TabButton->setText((TextNew.isEmpty())? tr("<No Tab>") : TextNew );

            QList<Unit> & List = Data[Text];
            for(Unit& u:List)
            {
                emit ChangeTab(u.WidgetEdit,ms);


            }
            Data[TextNew] = List;
            Data.remove(Text);
        }else
        {
            QMessageBox msgBox;
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
            msgBox.setText(tr("This tab is already exists"));
            msgBox.exec();
        }
        PrintTabs();
    }
}

bool UIConstructor::eventFilter(QObject *obj, QEvent *event)
{
    QPushButton *TabButton = qobject_cast<QPushButton *>(obj);

    if(TabButton)
    {
        QMouseEvent * mouseevent = dynamic_cast<QMouseEvent *>(event);
        if(mouseevent && mouseevent->button() == Qt::RightButton && event->type() == QEvent::MouseButtonPress)
        {
            QMenu Menu;
            QAction * EditAction = Menu.addAction(tr("Edit"));
            QAction * DeleteAction = Menu.addAction(tr("Delete"));
            QAction * ActionRes = Menu.exec(QCursor::pos());
            if(ActionRes == EditAction)
            {
                EditTab(TabButton);
            }
            if(ActionRes == DeleteAction)
            {
                QMessageBox msgBox;
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
                msgBox.setText(tr("Are you sure, that you want to delete tab?"));
                if(msgBox.exec() == QMessageBox::Ok)
                {
                    PrintTabs();
                    QString Text;
                    Text = TabButton->text();
                    if(Text == tr("<No Tab>"))
                    {
                        Text.clear();
                    }

                    int index = Tabs.indexOf(Text);
                    Tabs.removeAt(index);
                    TabsMultilang.removeAt(index);
                    for(Unit &u:Data[Text])
                    {
                        emit RemoveWidget(u.WidgetEdit);
                    }
                    Data.remove(Text);

                    if(CurrentTab == Text)
                    {
                        if(!Tabs.isEmpty())
                        {
                            ChangeTab(Tabs.first());
                        }
                    }

                    for(QPushButton * b:ui->TabsList->findChildren<QPushButton *>())
                    {
                        QString text = b->text();
                        if(text == tr("<No Tab>"))
                        {
                            text.clear();
                        }
                        if(text == Text)
                        {
                            b->deleteLater();
                            break;
                        }
                    }
                    QWidget *w = ui->stackedWidget->widget(index);
                    ui->stackedWidget->removeWidget(w);
                    w->deleteLater();

                    PrintTabs();
                }
            }
            return true;
        }
    }

    if(event->type() == QEvent::MouseButtonDblClick && TabButton)
    {
        EditTab(TabButton);
        return true;
    }

    if (TabButton)
    {
        QMouseEvent * mouseevent = dynamic_cast<QMouseEvent *>(event);
        if(mouseevent && mouseevent->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonPress)
        {
            DragTabName = TabButton->text();
            if(DragTabName == tr("<No Tab>"))
                DragTabName.clear();
            TabDragTimer->start();
        }
        if(mouseevent && mouseevent->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonRelease)
        {
            TabDragTimer->stop();
        }
    }



    QLabel *Label = qobject_cast<QLabel *>(obj);

    if(event->type() == QEvent::MouseButtonDblClick && Label)
    {
        QMouseEvent * mouseevent = dynamic_cast<QMouseEvent *>(event);
        if(mouseevent)
        {
            int index = ui->stackedWidget->currentWidget()->layout()->indexOf(Label);
            if(index>=0)
            {
                EditUnit(index);
            }
            return true;
        }

    }


    if(Label)
    {
        QMouseEvent * mouseevent = dynamic_cast<QMouseEvent *>(event);
        if(mouseevent && mouseevent->button() == Qt::RightButton && event->type() == QEvent::MouseButtonPress)
        {
            QMenu Menu;
            QAction * EditAction = Menu.addAction(tr("Edit"));
            QAction * DeleteAction = Menu.addAction(tr("Delete"));
            QAction * ActionRes = Menu.exec(QCursor::pos());
            if(ActionRes == EditAction)
            {

                int index = ui->stackedWidget->currentWidget()->layout()->indexOf(Label);
                if(index>=0)
                {
                    EditUnit(index);
                    return true;
                }
            }
            if(ActionRes == DeleteAction)
            {
                QMessageBox msgBox;
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowIcon(QIcon(":/engine/images/Logo.png"));
                msgBox.setText(tr("Are you sure, that you want to delete this resource?"));
                if(msgBox.exec() == QMessageBox::Ok)
                {
                    int index = ui->stackedWidget->currentWidget()->layout()->indexOf(Label);
                    if(index>=0)
                    {
                        ui->stackedWidget->currentWidget()->layout()->itemAt(index)->widget()->deleteLater();
                        emit RemoveWidget(Data[CurrentTab][index].WidgetEdit);
                        Data[CurrentTab].removeAt(index);
                        if(Data[CurrentTab].isEmpty())
                        {
                            QString OldTabName = CurrentTab;



                            int IndexTab = Tabs.indexOf(OldTabName);
                            Data.remove(OldTabName);
                            Tabs.removeAt(IndexTab);
                            emit UpdateClearState();
                            TabsMultilang.removeAt(IndexTab);
                            QWidget *w = ui->stackedWidget->widget(IndexTab);
                            ui->stackedWidget->removeWidget(w);
                            w->deleteLater();
                            QPushButton *OldTab = 0;

                            for(QPushButton *Button:ui->TabsList->findChildren<QPushButton *>())
                            {
                                if(Button->text() == OldTabName || (OldTabName.isEmpty() && Button->text() == tr("<No Tab>")))
                                {
                                    OldTab = Button;
                                    break;
                                }

                            }
                            OldTab->deleteLater();
                            if(!Tabs.isEmpty())
                            {
                                ChangeTab(Tabs.first());
                            }
                        }

                        PrintTabs();
                    }

                }
                return true;
            }

        }
    }


    return QWidget::eventFilter(obj, event);
}

void UIConstructor::EditUnit(int index)
{
    QDialog d;
    d.setMinimumWidth(400);
    d.setWindowTitle(tr("Edit resource"));
    d.setLayout(new QVBoxLayout(&d));
    d.layout()->setAlignment(Qt::AlignTop);
    QWidget *WidgetResource = Data[CurrentTab][index].WidgetEdit;
    QWidget *WidgetParent = WidgetResource->parentWidget();
    QVBoxLayout *LayoutParent = dynamic_cast<QVBoxLayout *>(WidgetParent->layout());
    int Index = LayoutParent->indexOf(WidgetResource);
    QScrollArea *Scroll = new QScrollArea(&d);
    Scroll->setWidgetResizable(true);
    QWidget *ScrollWidget = new QWidget(Scroll);
    ScrollWidget->setLayout(new QVBoxLayout(ScrollWidget));
    ScrollWidget->layout()->addWidget(WidgetResource);
    ScrollWidget->layout()->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    Scroll->setWidget(ScrollWidget);
    d.layout()->addWidget(Scroll);

    QWidget *WidgetButtons = new QWidget(&d);
    WidgetButtons->setLayout(new QHBoxLayout(WidgetButtons));
    WidgetButtons->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Maximum);
    QPushButton * Ok = new QPushButton(WidgetButtons);
    connect(Ok,SIGNAL(clicked(bool)),&d,SLOT(accept()));
    Ok->setText("Close");
    /*QPushButton * Cancel = new QPushButton(WidgetButtons);
    Cancel->setText("Cancel");
    connect(Cancel,SIGNAL(clicked(bool)),&d,SLOT(reject()));*/
    WidgetButtons->layout()->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    WidgetButtons->layout()->addWidget(Ok);
    //WidgetButtons->layout()->addWidget(Cancel);
    d.layout()->addWidget(WidgetButtons);
    d.exec();

    WidgetResource->setParent(WidgetParent);
    LayoutParent->insertWidget(Index,WidgetResource);

    QString NewName;
    foreach(QObject * i,WidgetResource->children())
    {
        IResourceWidget* w = qobject_cast<IResourceWidget*>(i);

        if(w)
        {
            NewName = w->GetVariableName();
        }
    }

    qobject_cast<QLabel *>(ui->stackedWidget->currentWidget()->layout()->itemAt(index)->widget())->setText(NewName);

    Data[CurrentTab][index].Name = NewName;
    PrintTabs();

}

void UIConstructor::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnduiconstructdata"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
        return;
    }

    if (event->mimeData()->hasFormat("application/x-dnduiconstructdatatab"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
        return;
    }

    event->ignore();
}

void UIConstructor::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnduiconstructdata")
            && (event->pos().x() >= ui->UnitList->pos().x() && event->pos().y() >= ui->UnitList->pos().y() || dynamic_cast<QPushButton*>(childAt(event->pos())) || ui->CreateNewTab == dynamic_cast<QLabel*>(childAt(event->pos())))
        )
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
        return;
    }
    if (event->mimeData()->hasFormat("application/x-dnduiconstructdatatab")
            && (dynamic_cast<QPushButton*>(childAt(event->pos())))
        )
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
        return;
    }

    event->ignore();

}

void UIConstructor::MoveToTab(const QString& Text, int offset)
{
    PrintTabs();
    int IndexNew = Tabs.indexOf(Text);
    int IndexOld = Tabs.indexOf(CurrentTab);

    QWidget *WidgetTo = (Data[Text].isEmpty()) ? 0 :Data[Text][0].WidgetEdit;

    emit MoveUnitInsideTab(Data[CurrentTab][offset].WidgetEdit,WidgetTo,false);
    emit ChangeTab(Data[CurrentTab][offset].WidgetEdit,TabsMultilang[IndexNew]);

    Unit unit = Data[CurrentTab][offset];

    Data[CurrentTab].removeAt(offset);
    Data[Text].insert(0,unit);
    QWidget * widget= ui->stackedWidget->currentWidget()->layout()->itemAt(offset)->widget();
    ui->stackedWidget->currentWidget()->layout()->removeWidget(widget);
    ui->stackedWidget->setCurrentIndex(IndexNew);
    ((QVBoxLayout*)ui->stackedWidget->currentWidget()->layout())->insertWidget(0,widget);
    QPushButton *OldTab = 0;
    QPushButton *NewTab = 0;


    for(QPushButton *Button:ui->TabsList->findChildren<QPushButton *>())
    {
        if(Button->text() == CurrentTab || (CurrentTab.isEmpty() && Button->text() == tr("<No Tab>")))
        {
            OldTab = Button;
        }
        if(Button->text() == Text || (Text.isEmpty() && Button->text() == tr("<No Tab>")))
        {
            NewTab = Button;
        }
        Button->setChecked(false);
    }
    NewTab->setChecked(true);
    if(Data[CurrentTab].isEmpty())
    {
        Data.remove(CurrentTab);
        Tabs.removeAt(IndexOld);
        TabsMultilang.removeAt(IndexOld);
        QWidget *w = ui->stackedWidget->widget(IndexOld);
        ui->stackedWidget->removeWidget(w);
        w->deleteLater();
        OldTab->deleteLater();
    }


    CurrentTab = Text;

    PrintTabs();
}

void UIConstructor::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnduiconstructdatatab"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnduiconstructdatatab");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QString text;
        dataStream >> text;
        QPushButton* Button = (dynamic_cast<QPushButton*>(childAt(event->pos())));
        QString ButtonText = Button->text();
        if(ButtonText == tr("<No Tab>"))
            ButtonText.clear();
        event->accept();

        if(Button)
        {
            int offset = Tabs.indexOf(text);
            int i = Tabs.indexOf(ButtonText);
            if(text == ButtonText)
                return;

            bool before = false;

            if(event->pos().y() < ui->TabsList->layout()->itemAt(i + 1)->widget()->pos().y() + ui->TabsList->layout()->itemAt(i + 1)->widget()->size().height() / 2)
            {
                before = true;
                i--;
            }

            if(offset>i)
            {
                i++;
            }

            QWidget *SendToWidget = 0;
            QList<Unit>& List = Data[ButtonText];
            if(before)
            {
                SendToWidget = List[0].WidgetEdit;
            }else
            {
                SendToWidget = List[List.length() - 1].WidgetEdit;
            }


            for(Unit & u:Data[text])
            {
                emit MoveUnitInsideTab(u.WidgetEdit,SendToWidget,!before);
                if(!before)
                    SendToWidget = u.WidgetEdit;
            }

            QLayoutItem *item = ui->TabsList->layout()->itemAt(offset + 1);

            ui->TabsList->layout()->removeItem(item);
            ((QVBoxLayout *)ui->TabsList->layout())->insertItem(i + 1,item);
            Tabs.move(offset,i);
            TabsMultilang.move(offset,i);

            QWidget *Units = ui->stackedWidget->widget(offset);
            ui->stackedWidget->removeWidget(Units);
            ui->stackedWidget->insertWidget(i,Units);
            if(text == CurrentTab)
            {
                ui->stackedWidget->setCurrentIndex(i);
            }

            PrintTabs();

        }


    }
    if (event->mimeData()->hasFormat("application/x-dnduiconstructdata"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnduiconstructdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        int offset;
        dataStream >> text >> offset;

        if(event->pos().x() >= ui->UnitList->pos().x() && event->pos().y() >= ui->UnitList->pos().y())
        {
            PrintTabs();
            QVBoxLayout * Layout = dynamic_cast<QVBoxLayout *>(ui->stackedWidget->currentWidget()->layout());

            int i = FindUnitNumberOfEvent(event->pos());

            event->accept();

            QLayoutItem *item = Layout->itemAt(offset);

            if(event->pos().y() < Layout->itemAt(i)->widget()->pos().y() + Layout->itemAt(i)->widget()->size().height() / 2)
            {
                i--;
            }

            if(offset>i)
            {
                i++;
            }

            Layout->removeItem(item);
            Layout->insertItem(i,item);

            QWidget *To = 0;
            bool after = true;
            if(offset<i)
            {
                To = Data[CurrentTab][i].WidgetEdit;
            }else
            {
                if(i > 0)
                    To = Data[CurrentTab][i-1].WidgetEdit;
                else
                {
                    To = Data[CurrentTab][0].WidgetEdit;
                    after = false;

                }
            }

            emit MoveUnitInsideTab(Data[CurrentTab][offset].WidgetEdit,To,after);

            Data[CurrentTab].move(offset,i);
            PrintTabs();
            return;
        }else
        {
            QPushButton* Target = dynamic_cast<QPushButton*>(childAt(event->pos()));
            if(Target)
            {
                QString Text = Target->text();
                if(Text == tr("<No Tab>"))
                {
                    Text.clear();
                }
                if(Text!=CurrentTab)
                {
                    MoveToTab(Text, offset);

                    return;
                }
            }

            if(ui->CreateNewTab == dynamic_cast<QLabel*>(childAt(event->pos())))
            {
                TabInputDialog Dialog;
                if(Dialog.exec())
                {
                    MultiLanguageString ms;
                    ms.SetTranslation("en",Dialog.GetTabNameEn());
                    ms.SetTranslation("ru",Dialog.GetTabNameRu());
                    QString Text = ms.GetTranslation(Language);
                    if(Tabs.contains(Text))
                    {
                        MoveToTab(Text, offset);
                    }else
                    {
                        QWidget *w = new QWidget();
                        QVBoxLayout *l = new QVBoxLayout(w);
                        l->setAlignment(Qt::AlignTop);
                        w->setLayout(l);
                        l->setSpacing(1);
                        l->setContentsMargins(0,0,0,0);
                        ui->stackedWidget->insertWidget(0,w);

                        Tabs.insert(0,Text);
                        TabsMultilang.insert(0,ms);

                        QPushButton * TabButton = new QPushButton(ui->TabsList);
                        TabButton->installEventFilter(this);
                        connect(TabButton,SIGNAL(clicked(bool)),this,SLOT(TabChanged()));
                        TabButton->setCheckable(true);

                        if(Text.isEmpty())
                        {
                            TabButton->setText(tr("<No Tab>"));
                        }else
                            TabButton->setText(Text);

                        ((QVBoxLayout *)ui->TabsList->layout())->insertWidget(1,TabButton);

                        Data[Text] = QList<Unit>();

                        MoveToTab(Text, offset);

                    }
                }
            }

        }
    }
    event->ignore();
}


int UIConstructor::FindUnitNumberOfEvent(const QPoint& Point)
{
    QVBoxLayout * Layout = dynamic_cast<QVBoxLayout *>(ui->stackedWidget->currentWidget()->layout());
    int size = Data[CurrentTab].length();

    int i;
    for(i = 0;i<size;i++)
    {
        QLayoutItem* item = Layout->itemAt(i);
        if(item)
        {
            if(!item->widget())
            {
                break;
            }
            if(!(Point.y() > item->widget()->pos().y()))
            {
                break;
            }
        }
    }
    return i - 1;
}


void UIConstructor::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        return;
    QLabel *child = dynamic_cast<QLabel*>(childAt(event->pos()));
    if (child)
    {
        if(child == ui->CreateNewTab)
            return;

        QSize size = child->size();
        QRegion region = QRegion(0,0,size.width(),size.height());
        QPixmap pixmap(size);
        child->render(&pixmap, QPoint(),region );
        QString text = qobject_cast<QLabel *>(child)->text();

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << text << FindUnitNumberOfEvent(event->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnduiconstructdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(-10,-10));

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        child->setPixmap(tempPixmap);
        child->setStyleSheet("*{border:0px solid gray}");
        child->setMargin(0);

        Qt::DropAction action = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        child->setStyleSheet("*{border:1px solid gray}");
        child->setMargin(7);
        child->setText(text);
    }



}

void UIConstructor::PrintTabs()
{
    /*qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    qDebug()<<"CurrentTab"<<CurrentTab;
    qDebug()<<"Tabs"<<Tabs;
    QStringList tm;
    for(MultiLanguageString ms:TabsMultilang)
    {
        tm.append(ms.GetTranslation("en"));
    }
    qDebug()<<"TabsMultilang"<<tm;

    for(QString key:Data.keys())
    {
        qDebug()<<"Key"<<key;
        for(Unit& u:Data[key])
        {
            qDebug()<<"     "<<u.Name;
        }
    }*/


}


UIConstructor::~UIConstructor()
{
    delete ui;
}
