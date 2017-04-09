#ifndef MAINWINDOWTABBLINK_H
#define MAINWINDOWTABBLINK_H

#include <QObject>
#include "engine_global.h"
#include "itabblink.h"

#include <QTimer>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT MainWindowTabBlink : public ITabBlink
    {
        Q_OBJECT
        QTimer *Timer;
        QWidget *Widget;
        QString FindText;
        bool StateOn;
    public:
        explicit MainWindowTabBlink(QObject *parent = 0);
        void SetWidget(QWidget *Widget);
        void SetText(const QString& Text);
    signals:

    public slots:
        virtual void Stop();
        virtual void Start();
    private slots:
        void time();
        void show();
        void hide();
    };
}

#endif // MAINWINDOWTABBLINK_H
