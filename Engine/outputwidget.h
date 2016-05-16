#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QHash>

#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include "outputwidgetconfigurator.h"
#include "multilanguagestring.h"

namespace Ui {
class OutputWidget;
}
using namespace BrowserAutomationStudioFramework;
class OutputWidget : public QWidget
{
    Q_OBJECT
    int SuccessCount;
    int FailedCount;
    QString FileName1;
    QString FileName2;
    QString FileName3;
    QString FileName4;
    QString FileName5;
    QString FileName6;
    QString FileName7;
    QString FileName8;
    QString FileName9;
    QList<int> CountOutput;
    struct SolverStats
    {
        int Used;
        QLabel *label2;
        QLabel *label1;
    };
    QWidget *tab1;
    QWidget *tab2;
    QWidget *tab3;
    QWidget *tab4;
    QWidget *tab5;
    QWidget *tab6;
    QWidget *tab7;
    QWidget *tab8;
    QWidget *tab9;

    QHash<QString,SolverStats> Stats;
    void AddSolver(const QString& Solver, SolverStats& stats);
    QPushButton *LabelAllResults1;
    QPushButton *LabelAllResults2;
    QPushButton *LabelAllResults3;
    QPushButton *LabelAllResults4;
    QPushButton *LabelAllResults5;
    QPushButton *LabelAllResults6;
    QPushButton *LabelAllResults7;
    QPushButton *LabelAllResults8;
    QPushButton *LabelAllResults9;

    OutputWidgetConfigurator *Configurator1;
    OutputWidgetConfigurator *Configurator2;
    OutputWidgetConfigurator *Configurator3;
    OutputWidgetConfigurator *Configurator4;
    OutputWidgetConfigurator *Configurator5;
    OutputWidgetConfigurator *Configurator6;
    OutputWidgetConfigurator *Configurator7;
    OutputWidgetConfigurator *Configurator8;
    OutputWidgetConfigurator *Configurator9;

public:
    explicit OutputWidget(QWidget *parent = 0);
    ~OutputWidget();
    QTextBrowser *GetOutput(int number);
    void SetFileName1(const QString& FileName1);
    void SetFileName2(const QString& FileName2);
    void SetFileName3(const QString& FileName3);
    void SetFileName4(const QString& FileName4);
    void SetFileName5(const QString& FileName5);
    void SetFileName6(const QString& FileName6);
    void SetFileName7(const QString& FileName7);
    void SetFileName8(const QString& FileName8);
    void SetFileName9(const QString& FileName9);
    void Success();
    void Failed();
    void UsedSolver(const QString &Solver);
    void Finished();
    void AddedOutput(int number);
    void Clear();
    void ProgressValue(int value);
    void ProgressMaximum(int maximum);
    MultiLanguageString GetOutputTitle1();
    MultiLanguageString GetOutputTitle2();
    MultiLanguageString GetOutputTitle3();
    MultiLanguageString GetOutputTitle4();
    MultiLanguageString GetOutputTitle5();
    MultiLanguageString GetOutputTitle6();
    MultiLanguageString GetOutputTitle7();
    MultiLanguageString GetOutputTitle8();
    MultiLanguageString GetOutputTitle9();
    bool GetOutputVisible1();
    bool GetOutputVisible2();
    bool GetOutputVisible3();
    bool GetOutputVisible4();
    bool GetOutputVisible5();
    bool GetOutputVisible6();
    bool GetOutputVisible7();
    bool GetOutputVisible8();
    bool GetOutputVisible9();
    void SetOutputTitle1(const MultiLanguageString& OutputTitle1);
    void SetOutputTitle2(const MultiLanguageString& OutputTitle2);
    void SetOutputTitle3(const MultiLanguageString& OutputTitle3);
    void SetOutputTitle4(const MultiLanguageString& OutputTitle4);
    void SetOutputTitle5(const MultiLanguageString& OutputTitle5);
    void SetOutputTitle6(const MultiLanguageString& OutputTitle6);
    void SetOutputTitle7(const MultiLanguageString& OutputTitle7);
    void SetOutputTitle8(const MultiLanguageString& OutputTitle8);
    void SetOutputTitle9(const MultiLanguageString& OutputTitle9);

    void SetOutputVisible1(bool OutputVisible1);
    void SetOutputVisible2(bool OutputVisible2);
    void SetOutputVisible3(bool OutputVisible3);
    void SetOutputVisible4(bool OutputVisible4);
    void SetOutputVisible5(bool OutputVisible5);
    void SetOutputVisible6(bool OutputVisible6);
    void SetOutputVisible7(bool OutputVisible7);
    void SetOutputVisible8(bool OutputVisible8);
    void SetOutputVisible9(bool OutputVisible9);
    void SetConfiguratorVisible(bool Visible);

public slots:
    void SetLanguageModel(ILanguageModel* LanguageModel);

private slots:
    void LabelAllResults1_linkActivated();
    void LabelAllResults2_linkActivated();
    void LabelAllResults3_linkActivated();
    void LabelAllResults4_linkActivated();
    void LabelAllResults5_linkActivated();
    void LabelAllResults6_linkActivated();
    void LabelAllResults7_linkActivated();
    void LabelAllResults8_linkActivated();
    void LabelAllResults9_linkActivated();
    void Tab1TextChanged(const QString & text);
    void Tab2TextChanged(const QString & text);
    void Tab3TextChanged(const QString & text);
    void Tab4TextChanged(const QString & text);
    void Tab5TextChanged(const QString & text);
    void Tab6TextChanged(const QString & text);
    void Tab7TextChanged(const QString & text);
    void Tab8TextChanged(const QString & text);
    void Tab9TextChanged(const QString & text);

private:
    Ui::OutputWidget *ui;
    void changeEvent(QEvent *e);
protected:

};

#endif // OUTPUTWIDGET_H
