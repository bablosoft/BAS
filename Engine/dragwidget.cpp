#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#include <QLabel>
#include <QDragEnterEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include "every_cpp.h"

#include <QScrollArea>

#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    this->setContentsMargins(0,0,0,0);
    this->setMinimumHeight(100);
    QVBoxLayout *MainLayout = new QVBoxLayout(this);

    QScrollArea *ScrollArea = new QScrollArea(this);
    ScrollArea->setStyleSheet("QScrollArea{border: 1px solid gray; border-radius: 4px; padding: 1px;}");

    MainLayout->addWidget(ScrollArea);
    MainLayout->setContentsMargins(0,0,0,0);
    ScrollArea->setContentsMargins(0,0,0,0);
    Data = new QWidget(ScrollArea);

    Layout = new QVBoxLayout(Data);
    Layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    Data->setLayout(Layout);

    ScrollArea->setWidget(Data);



    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setMinimumWidth(280);




    SetData(QStringList());
}

QStringList DragWidget::GetData()
{
    QStringList res;
    int index = 0;

    while(index < Layout->count())
    {
        QLayoutItem* item = Layout->itemAt(index);
        if(item)
        {
            if(item->widget())
            {
                QLabel *label = qobject_cast<QLabel *>(item->widget());
                if(label)
                {
                    res.append(label->text());
                }
            }

        }
        index++;
    }
    return res;
}

void DragWidget::SetData(const QStringList& list)
{
    Clear();
    foreach(QString item, list)
    {
        QLabel *label = new QLabel(Data);

        label->setText(item);
        label->show();
        label->setMouseTracking(true);
        QFont font;
        font.setPointSize(9);
        label->setFont(font);
        label->setCursor(QCursor(Qt::OpenHandCursor));
        label->setAttribute(Qt::WA_DeleteOnClose);
        Layout->addWidget(label);
    }
    Data->updateGeometry();
    Data->update();
    dynamic_cast<QBoxLayout *>(Layout)->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
}



void DragWidget::Clear()
{
    while(Layout->count()>0)
    {
        QLayoutItem* item = Layout->itemAt(0);
        if(item)
        {
            Layout->removeItem( item );
            QWidget* widget = item->widget();
            if(widget)
            {
                Layout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }
    }

}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
    } else
    {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
    } else
    {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;



        QLabel *newIcon = new QLabel(this);
        newIcon->setText(text);

        int index = 0;

        while(index < Layout->count())
        {
            QLayoutItem* item = Layout->itemAt(index);
            if(item)
            {
                if(!item->widget())
                {
                    break;
                }
                if(!((event->pos() - offset).y() > item->widget()->pos().y()))
                {
                    break;
                }
            }
            index++;
        }


        dynamic_cast<QBoxLayout *>(Layout)->insertWidget(index,newIcon);
        QFont font;
        font.setPointSize(9);
        newIcon->setFont(font);
        newIcon->show();
        newIcon->setMouseTracking(true);
        newIcon->setCursor(QCursor(Qt::OpenHandCursor));
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
        emit ChangedDragWidget();
    } else
    {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = dynamic_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QSize size = child->size();
    QRegion region = QRegion(0,0,size.width(),size.height());
    QPixmap pixmap(size);
    child->render(&pixmap, QPoint(),region );
    QString text = qobject_cast<QLabel *>(child)->text();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << text << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

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

    Qt::DropAction action = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    switch(action)
    {
        case Qt::MoveAction: child->close(); break;
        case Qt::CopyAction: child->close(); break;
        case Qt::IgnoreAction: child->show(); child->setText(text); break;
    }

}
