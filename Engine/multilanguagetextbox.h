#ifndef MULTILANGUAGETEXTBOX_H
#define MULTILANGUAGETEXTBOX_H
#include "engine_global.h"

#include <QObject>
#include "ilanguagemodel.h"
#include "multilanguagestring.h"

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class MultiLanguageTextBox;
}


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT MultiLanguageTextBox : public QWidget
    {
        Q_OBJECT
        ILanguageModel *LanguageModel;
        MultiLanguageString MultilanguageText;
    public:
        explicit MultiLanguageTextBox(QWidget *parent = 0);
        ~MultiLanguageTextBox();
        void SetLanguageModel(ILanguageModel * LanguageModel);
        MultiLanguageString GetText();
        QString GetCurrentText();
        void SetText(const MultiLanguageString& text);
        QLineEdit * GetEdit();
    private:
        Ui::MultiLanguageTextBox *ui;
        void changeEvent(QEvent *e);
    signals:
        void textChanged(const QString&);
        void textChangedMultilanguage(const MultiLanguageString&);
    private slots:
        void DefaultLanguageChanged(const QString& lang);
        void textChangedMultilanguageSlot();
        void UpdateLanguageModel();
        void ComboTextChanged(const QString& lang);
        void SetTranslation(const QString& text);

    };
}
#endif // MULTILANGUAGETEXTBOX_H

