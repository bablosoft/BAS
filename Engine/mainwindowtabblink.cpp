#include "mainwindowtabblink.h"
#include <QTabBar>
#include <QIcon>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    MainWindowTabBlink::MainWindowTabBlink(QObject *parent) :
        ITabBlink(parent)
    {
        Timer = 0;
        StateOn = false;
    }

    void MainWindowTabBlink::SetWidget(QWidget *Widget)
    {
        this->Widget = Widget;
    }
    void MainWindowTabBlink::SetText(const QString& Text)
    {
        FindText = Text;
    }


    void MainWindowTabBlink::Stop()
    {
        if(Timer)
            Timer->stop();
        hide();
    }

    void MainWindowTabBlink::time()
    {
        if(StateOn)
        {
            hide();
        }else
        {
            show();
        }
    }

    void MainWindowTabBlink::show()
    {
        for(QTabBar* bar:Widget->findChildren<QTabBar*>())
        {
            for(int i = 0;i<bar->count();i++)
            {
                if(bar->tabText(i).startsWith(FindText))
                {
                    bar->setTabIcon(i,QIcon(":/engine/images/redball.png"));
                }
            }

        }
        StateOn = true;

    }

    void MainWindowTabBlink::hide()
    {
        for(QTabBar* bar:Widget->findChildren<QTabBar*>())
        {
            for(int i = 0;i<bar->count();i++)
            {
                if(bar->tabText(i).startsWith(FindText))
                {
                    bar->setTabIcon(i,QIcon("://images/grayball.png"));
                }
            }

        }
        StateOn = false;

    }

    void MainWindowTabBlink::Start()
    {
        if(!Timer)
        {
            Timer = new QTimer(this);
            Timer->setSingleShot(false);
            Timer->setInterval(1000);
            connect(Timer,SIGNAL(timeout()),this,SLOT(time()));
        }
        Timer->start();


    }
}
