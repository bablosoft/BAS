#include "skincontroller.h"
#include <QStyleFactory>
#include <QPalette>
#ifdef HAVE_QT5
    #include <QApplication>
#else
    #include <QtGui/QApplication>
#endif
#include <QFont>
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    SkinController::SkinController(QObject *parent) :
        ISkinController(parent)
    {
    }

    void SkinController::ApplyTheme(const QString & theme)
    {

        if(theme == "DarkFusion")
        {

            qApp->setStyle(QStyleFactory::create("fusion"));


            QFont font = qApp->font();
            font.setPixelSize(13);
            qApp->setFont(font);

            QPalette palette;
            palette.setColor(QPalette::Window, QColor(53,53,53));
            palette.setColor(QPalette::WindowText, Qt::white);
            palette.setColor(QPalette::Base, QColor(35,35,35));
            palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
            palette.setColor(QPalette::ToolTipBase, Qt::white);
            palette.setColor(QPalette::ToolTipText, Qt::white);
            palette.setColor(QPalette::Text, Qt::white);
            palette.setColor(QPalette::Button, QColor(53,53,53));
            palette.setColor(QPalette::ButtonText, Qt::white);
            palette.setColor(QPalette::BrightText, Qt::red);

            palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
            palette.setColor(QPalette::HighlightedText, Qt::black);
            qApp->setPalette(palette);

            qApp->setStyleSheet("QToolTip { color: white; background-color: #232323; border-radius:4px;  border-width: 1px; border-style: solid; border-color:gray;}");
        }else if(theme == "WhiteFusion")
        {
            qApp->setStyle(QStyleFactory::create("fusion"));

            QFont font = qApp->font();
            font.setPixelSize(13);
            qApp->setFont(font);

            QPalette palette;
            qApp->setPalette(palette);


        }else if(theme == "BlueFusion")
        {
            qApp->setStyle(QStyleFactory::create("fusion"));

            QFont font = qApp->font();
            font.setPixelSize(13);
            qApp->setFont(font);

            QPalette palette;
            palette.setColor(QPalette::Window, QColor(220,220,227));
            palette.setColor(QPalette::Base, QColor(255,255,255));
            palette.setColor(QPalette::AlternateBase, QColor(255,255,255));
            palette.setColor(QPalette::Button, QColor(235,235,235));


            palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
            palette.setColor(QPalette::HighlightedText, Qt::black);
            qApp->setPalette(palette);
        }
    }
}
