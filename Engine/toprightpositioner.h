#ifndef TOPRIGHTPOSITIONER_H
#define TOPRIGHTPOSITIONER_H
#include "engine_global.h"
#include <QObject>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT TopRightPositioner : public QObject
    {
        Q_OBJECT
        QWidget *Parent;
        QWidget *Child;
        int MarginTop;
        int MarginRight;
        bool eventFilter(QObject *obj, QEvent *event);
        void Move();
    public:
        explicit TopRightPositioner(QObject *parent = 0);

    signals:

    public slots:
        void Start();
        void SetMarginTop(int MarginTop);
        void SetMarginRight(int MarginRight);
        void SetParent(QWidget *Parent);
        void SetChild(QWidget *Child);
    };
}

#endif // TOPRIGHTPOSITIONER_H
