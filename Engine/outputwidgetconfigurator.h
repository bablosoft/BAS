#ifndef OUTPUTWIDGETCONFIGURATOR_H
#define OUTPUTWIDGETCONFIGURATOR_H
#include "engine_global.h"
#include <QWidget>
#include "ilanguagemodel.h"
#include "multilanguagestring.h"
#include "multilanguagetextbox.h"

namespace Ui {
class OutputWidgetConfigurator;
}

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT OutputWidgetConfigurator : public QWidget
    {
        Q_OBJECT
        ILanguageModel *LanguageModel;
        MultiLanguageTextBox * TextBox;
    public:
        explicit OutputWidgetConfigurator(QWidget *parent = 0);
        ~OutputWidgetConfigurator();
        void SetTitle(const MultiLanguageString& Title);
        MultiLanguageString GetTitle();
        QString GetTitleText();
        bool GetVisibility();
        void SetVisibility(bool Visibility);
        void SetLanguageModel(ILanguageModel *LanguageModel);
    signals:

        void TitleChanged(const QString& Title);
    private:
        Ui::OutputWidgetConfigurator *ui;
        void changeEvent(QEvent *e);
    };
}

#endif // OUTPUTWIDGETCONFIGURATOR_H
