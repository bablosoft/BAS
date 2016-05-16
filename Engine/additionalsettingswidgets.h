#ifndef ADDITIONALSETTINGSWIDGETS_H
#define ADDITIONALSETTINGSWIDGETS_H
#include "engine_global.h"

#include <QWidget>
#include <QRadioButton>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT AdditionalSettingsWidgets : public QObject
    {
        Q_OBJECT
        QWidget *Widget;
        QRadioButton *MultiProcessQt5;
        QString Default;
    public:
        void SetDefault(const QString& Default);
        explicit AdditionalSettingsWidgets(QObject *parent = 0);
        QWidget * GetWidget();
        QString ParseWidget();
    signals:

    public slots:

    };
}

#endif // ADDITIONALSETTINGSWIDGETS_H
