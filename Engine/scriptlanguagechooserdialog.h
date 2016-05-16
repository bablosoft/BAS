#ifndef SCRIPTLANGUAGECHOOSERDIALOG_H
#define SCRIPTLANGUAGECHOOSERDIALOG_H
#include "engine_global.h"

#include <QDialog>
#include "ilanguagemodel.h"


namespace Ui {
class ScriptLanguageChooserDialog;
}

using namespace BrowserAutomationStudioFramework;
class ENGINESHARED_EXPORT ScriptLanguageChooserDialog : public QDialog
{
    Q_OBJECT
    ILanguageModel *LanguageModel;
    QString CurrentLang;
public:
    explicit ScriptLanguageChooserDialog(QWidget *parent = 0);
    ~ScriptLanguageChooserDialog();
    void SetLanguageModel(ILanguageModel *LanguageModel);
    void SetLang(const QString &CurrentLang);
    QString GetLang();
    void ChangesWillTakeEffectAfterRestart();
private:
    Ui::ScriptLanguageChooserDialog *ui;
    void changeEvent(QEvent *e);
private slots:
    void RadioBoxToggled(bool state);
};

#endif // SCRIPTLANGUAGECHOOSERDIALOG_H
