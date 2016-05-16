#ifndef LANGUAGECHOOSERDEVELOPMENTWIDGET_H
#define LANGUAGECHOOSERDEVELOPMENTWIDGET_H
#include "engine_global.h"

#include <QDialog>
#include <QList>
#include <QCheckBox>

#include "ilanguagemodel.h"

namespace Ui {
class LanguageChooserDevelopmentWidget;
}

using namespace BrowserAutomationStudioFramework;

class ENGINESHARED_EXPORT LanguageChooserDevelopmentWidget : public QDialog
{
    Q_OBJECT
    ILanguageModel *LanguageModel;
    bool correcting;
    QList<QCheckBox *> CheckBoxes;
public:
    explicit LanguageChooserDevelopmentWidget(QWidget *parent = 0);
    ~LanguageChooserDevelopmentWidget();
    void SetLanguageModel(ILanguageModel *LanguageModel);
private:
    Ui::LanguageChooserDevelopmentWidget *ui;
    void changeEvent(QEvent *e);
private slots:
    void CheckBoxClicked();
    void ButtonClicked();
    void AcceptedSlot();
};

#endif // LANGUAGECHOOSERDEVELOPMENTWIDGET_H
