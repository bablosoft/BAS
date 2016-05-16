#include "toprightpositioner.h"
#include <QWidget>
#include <QEvent>
#include <QResizeEvent>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    TopRightPositioner::TopRightPositioner(QObject *parent) :
        QObject(parent)
    {
        MarginRight = 35;
        MarginTop = 15;
    }

    void TopRightPositioner::SetParent(QWidget *Parent)
    {
        this->Parent = Parent;
    }

    void TopRightPositioner::SetChild(QWidget *Child)
    {
        this->Child = Child;
    }

    void TopRightPositioner::Start()
    {
        Child->setParent(Parent);

        Parent->installEventFilter(this);
        Move();
    }

    void TopRightPositioner::SetMarginTop(int MarginTop)
    {
        this->MarginTop = MarginTop;
    }
    void TopRightPositioner::SetMarginRight(int MarginRight)
    {
        this->MarginRight = MarginRight;
    }


    void TopRightPositioner::Move()
    {

        Child->move(Parent->width() - Child->width() - MarginRight, MarginTop);
    }

    bool TopRightPositioner::eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::Resize && obj == Parent)
        {
            Move();
            return true;
        } else
        {
            return QObject::eventFilter(obj, event);
        }
    }

}
