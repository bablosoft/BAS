#include "additionalsettingswidgets.h"
#include <QHBoxLayout>
#include <QLabel>
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    AdditionalSettingsWidgets::AdditionalSettingsWidgets(QObject *parent) :
        QObject(parent)
    {
    }

    void AdditionalSettingsWidgets::SetDefault(const QString& Default)
    {
        this->Default = Default;
    }
    QWidget * AdditionalSettingsWidgets::GetWidget()
    {
        Widget = new QWidget();
        /*QVBoxLayout *layout = new QVBoxLayout(Widget);
        Widget->setLayout(layout);
        QLabel *label = new QLabel(Widget);
        label->setText(tr("Choose worker type :"));*/

        /*Multithreaded = new QRadioButton(Widget);
        Multithreaded->setText(tr("Multithreaded"));*/

        /*MultiProcessQt5 = new QRadioButton(Widget);
        MultiProcessQt5->setText(tr("Multiprocess Chrome"));*/

        /*MultiProcessFirefox = new QRadioButton(Widget);
        MultiProcessFirefox->setText(tr("Multiprocess Firefox"));*/


        /*MultiProcessQt5->setChecked(true);

        layout->addWidget(label);
        //layout->addWidget(Multithreaded);
        layout->addWidget(MultiProcessQt5);
        //layout->addWidget(MultiProcessFirefox);*/


        return Widget;
    }
    QString AdditionalSettingsWidgets::ParseWidget()
    {
        /*if(MultiProcessQt5->isChecked())
        {
            return "MultiProcessQt5";
        }*/
        return "MultiProcessQt5";
    }
}
