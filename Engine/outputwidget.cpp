#include "outputwidget.h"
#include "ui_outputwidget.h"
#include <QDesktopServices>
#include <QFileInfo>
#include "toprightpositioner.h"
#include "openlinksfromfilesystem.h"
#include "every_cpp.h"


OutputWidget::OutputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWidget)
{
    ui->setupUi(this);
    LabelAllResults1 = new QPushButton(tr("All Results"),ui->tab);
    LabelAllResults2 = new QPushButton(tr("All Results"),ui->tab_2);
    LabelAllResults3 = new QPushButton(tr("All Results"),ui->tab_3);
    LabelAllResults4 = new QPushButton(tr("All Results"),ui->tab_4);
    LabelAllResults5 = new QPushButton(tr("All Results"),ui->tab_5);
    LabelAllResults6 = new QPushButton(tr("All Results"),ui->tab_6);
    LabelAllResults7 = new QPushButton(tr("All Results"),ui->tab_7);
    LabelAllResults8 = new QPushButton(tr("All Results"),ui->tab_8);
    LabelAllResults9 = new QPushButton(tr("All Results"),ui->tab_9);

    TopRightPositioner * LabelAllResults1Positioner = new TopRightPositioner(this);
    LabelAllResults1Positioner->SetChild(LabelAllResults1);
    LabelAllResults1Positioner->SetParent(ui->tab);
    LabelAllResults1Positioner->Start();
    TopRightPositioner * LabelAllResults2Positioner = new TopRightPositioner(this);
    LabelAllResults2Positioner->SetChild(LabelAllResults2);
    LabelAllResults2Positioner->SetParent(ui->tab_2);
    LabelAllResults2Positioner->Start();
    TopRightPositioner * LabelAllResults3Positioner = new TopRightPositioner(this);
    LabelAllResults3Positioner->SetChild(LabelAllResults3);
    LabelAllResults3Positioner->SetParent(ui->tab_3);
    LabelAllResults3Positioner->Start();

    TopRightPositioner * LabelAllResults4Positioner = new TopRightPositioner(this);
    LabelAllResults4Positioner->SetChild(LabelAllResults4);
    LabelAllResults4Positioner->SetParent(ui->tab_4);
    LabelAllResults4Positioner->Start();
    TopRightPositioner * LabelAllResults5Positioner = new TopRightPositioner(this);
    LabelAllResults5Positioner->SetChild(LabelAllResults5);
    LabelAllResults5Positioner->SetParent(ui->tab_5);
    LabelAllResults5Positioner->Start();
    TopRightPositioner * LabelAllResults6Positioner = new TopRightPositioner(this);
    LabelAllResults6Positioner->SetChild(LabelAllResults6);
    LabelAllResults6Positioner->SetParent(ui->tab_6);
    LabelAllResults6Positioner->Start();
    TopRightPositioner * LabelAllResults7Positioner = new TopRightPositioner(this);
    LabelAllResults7Positioner->SetChild(LabelAllResults7);
    LabelAllResults7Positioner->SetParent(ui->tab_7);
    LabelAllResults7Positioner->Start();
    TopRightPositioner * LabelAllResults8Positioner = new TopRightPositioner(this);
    LabelAllResults8Positioner->SetChild(LabelAllResults8);
    LabelAllResults8Positioner->SetParent(ui->tab_8);
    LabelAllResults8Positioner->Start();
    TopRightPositioner * LabelAllResults9Positioner = new TopRightPositioner(this);
    LabelAllResults9Positioner->SetChild(LabelAllResults9);
    LabelAllResults9Positioner->SetParent(ui->tab_9);
    LabelAllResults9Positioner->Start();
    connect(LabelAllResults1,SIGNAL(clicked()),this,SLOT(LabelAllResults1_linkActivated()));
    connect(LabelAllResults2,SIGNAL(clicked()),this,SLOT(LabelAllResults2_linkActivated()));
    connect(LabelAllResults3,SIGNAL(clicked()),this,SLOT(LabelAllResults3_linkActivated()));
    connect(LabelAllResults4,SIGNAL(clicked()),this,SLOT(LabelAllResults4_linkActivated()));
    connect(LabelAllResults5,SIGNAL(clicked()),this,SLOT(LabelAllResults5_linkActivated()));
    connect(LabelAllResults6,SIGNAL(clicked()),this,SLOT(LabelAllResults6_linkActivated()));
    connect(LabelAllResults7,SIGNAL(clicked()),this,SLOT(LabelAllResults7_linkActivated()));
    connect(LabelAllResults8,SIGNAL(clicked()),this,SLOT(LabelAllResults8_linkActivated()));
    connect(LabelAllResults9,SIGNAL(clicked()),this,SLOT(LabelAllResults9_linkActivated()));


    MultiLanguageString ms1;
    ms1.SetTranslation("en","First Results");

    MultiLanguageString ms2;
    ms2.SetTranslation("en","Second Results");

    MultiLanguageString ms3;
    ms3.SetTranslation("en","Third Results");

    MultiLanguageString ms4;
    ms4.SetTranslation("en","Fourth Results");

    MultiLanguageString ms5;
    ms5.SetTranslation("en","Fifth Results");

    MultiLanguageString ms6;
    ms6.SetTranslation("en","Sixth Results");

    MultiLanguageString ms7;
    ms7.SetTranslation("en","Seventh Results");

    MultiLanguageString ms8;
    ms8.SetTranslation("en","Eighth Results");

    MultiLanguageString ms9;
    ms9.SetTranslation("en","Ninth Results");



    Configurator1 = new OutputWidgetConfigurator(this);
    connect(Configurator1,SIGNAL(TitleChanged(QString)),this,SLOT(Tab1TextChanged(QString)));
    Configurator1->SetTitle(ms1);
    ui->configuratorLayout_1->addWidget(Configurator1);

    Configurator2 = new OutputWidgetConfigurator(this);
    connect(Configurator2,SIGNAL(TitleChanged(QString)),this,SLOT(Tab2TextChanged(QString)));
    Configurator2->SetTitle(ms2);
    ui->configuratorLayout_2->addWidget(Configurator2);

    Configurator3 = new OutputWidgetConfigurator(this);
    connect(Configurator3,SIGNAL(TitleChanged(QString)),this,SLOT(Tab3TextChanged(QString)));
    Configurator3->SetTitle(ms3);
    ui->configuratorLayout_3->addWidget(Configurator3);

    Configurator4 = new OutputWidgetConfigurator(this);
    connect(Configurator4,SIGNAL(TitleChanged(QString)),this,SLOT(Tab4TextChanged(QString)));
    Configurator4->SetTitle(ms4);
    ui->configuratorLayout_4->addWidget(Configurator4);

    Configurator5 = new OutputWidgetConfigurator(this);
    connect(Configurator5,SIGNAL(TitleChanged(QString)),this,SLOT(Tab5TextChanged(QString)));
    Configurator5->SetTitle(ms5);
    ui->configuratorLayout_5->addWidget(Configurator5);

    Configurator6 = new OutputWidgetConfigurator(this);
    connect(Configurator6,SIGNAL(TitleChanged(QString)),this,SLOT(Tab6TextChanged(QString)));
    Configurator6->SetTitle(ms6);
    ui->configuratorLayout_6->addWidget(Configurator6);

    Configurator7 = new OutputWidgetConfigurator(this);
    connect(Configurator7,SIGNAL(TitleChanged(QString)),this,SLOT(Tab7TextChanged(QString)));
    Configurator7->SetTitle(ms7);
    ui->configuratorLayout_7->addWidget(Configurator7);

    Configurator8 = new OutputWidgetConfigurator(this);
    connect(Configurator8,SIGNAL(TitleChanged(QString)),this,SLOT(Tab8TextChanged(QString)));
    Configurator8->SetTitle(ms8);
    ui->configuratorLayout_8->addWidget(Configurator8);

    Configurator9 = new OutputWidgetConfigurator(this);
    connect(Configurator9,SIGNAL(TitleChanged(QString)),this,SLOT(Tab9TextChanged(QString)));
    Configurator9->SetTitle(ms9);
    ui->configuratorLayout_9->addWidget(Configurator9);


    LabelAllResults1->setVisible(false);
    LabelAllResults2->setVisible(false);
    LabelAllResults3->setVisible(false);
    LabelAllResults4->setVisible(false);
    LabelAllResults5->setVisible(false);
    LabelAllResults6->setVisible(false);
    LabelAllResults7->setVisible(false);
    LabelAllResults8->setVisible(false);
    LabelAllResults9->setVisible(false);
    tab1 = ui->tab;
    tab2 = ui->tab_2;
    tab3 = ui->tab_3;
    tab4 = ui->tab_4;
    tab5 = ui->tab_5;
    tab6 = ui->tab_6;
    tab7 = ui->tab_7;
    tab8 = ui->tab_8;
    tab9 = ui->tab_9;
    Clear();

    new OpenLinksFromFileSystem(ui->Output1);
    new OpenLinksFromFileSystem(ui->Output2);
    new OpenLinksFromFileSystem(ui->Output3);
    new OpenLinksFromFileSystem(ui->Output4);
    new OpenLinksFromFileSystem(ui->Output5);
    new OpenLinksFromFileSystem(ui->Output6);
    new OpenLinksFromFileSystem(ui->Output7);
    new OpenLinksFromFileSystem(ui->Output8);
    new OpenLinksFromFileSystem(ui->Output9);


}

void OutputWidget::SetLanguageModel(ILanguageModel* LanguageModel)
{
    Configurator1->SetLanguageModel(LanguageModel);
    Configurator2->SetLanguageModel(LanguageModel);
    Configurator3->SetLanguageModel(LanguageModel);
    Configurator4->SetLanguageModel(LanguageModel);
    Configurator5->SetLanguageModel(LanguageModel);
    Configurator6->SetLanguageModel(LanguageModel);
    Configurator7->SetLanguageModel(LanguageModel);
    Configurator8->SetLanguageModel(LanguageModel);
    Configurator9->SetLanguageModel(LanguageModel);
}

MultiLanguageString OutputWidget::GetOutputTitle1()
{
    return Configurator1->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle2()
{
    return Configurator2->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle3()
{
    return Configurator3->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle4()
{
    return Configurator4->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle5()
{
    return Configurator5->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle6()
{
    return Configurator6->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle7()
{
    return Configurator7->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle8()
{
    return Configurator8->GetTitle();
}

MultiLanguageString OutputWidget::GetOutputTitle9()
{
    return Configurator9->GetTitle();
}

bool OutputWidget::GetOutputVisible1()
{
    return Configurator1->GetVisibility();
}

bool OutputWidget::GetOutputVisible2()
{
    return Configurator2->GetVisibility();
}

bool OutputWidget::GetOutputVisible3()
{
    return Configurator3->GetVisibility();
}

bool OutputWidget::GetOutputVisible4()
{
    return Configurator4->GetVisibility();
}

bool OutputWidget::GetOutputVisible5()
{
    return Configurator5->GetVisibility();
}

bool OutputWidget::GetOutputVisible6()
{
    return Configurator6->GetVisibility();
}

bool OutputWidget::GetOutputVisible7()
{
    return Configurator7->GetVisibility();
}

bool OutputWidget::GetOutputVisible8()
{
    return Configurator8->GetVisibility();
}

bool OutputWidget::GetOutputVisible9()
{
    return Configurator9->GetVisibility();
}

void OutputWidget::SetOutputTitle1(const MultiLanguageString& OutputTitle1)
{
    Configurator1->SetTitle(OutputTitle1);
}

void OutputWidget::SetOutputTitle2(const MultiLanguageString& OutputTitle2)
{
    Configurator2->SetTitle(OutputTitle2);
}

void OutputWidget::SetOutputTitle3(const MultiLanguageString& OutputTitle3)
{
    Configurator3->SetTitle(OutputTitle3);
}

void OutputWidget::SetOutputTitle4(const MultiLanguageString& OutputTitle4)
{
    Configurator4->SetTitle(OutputTitle4);
}

void OutputWidget::SetOutputTitle5(const MultiLanguageString& OutputTitle5)
{
    Configurator5->SetTitle(OutputTitle5);
}

void OutputWidget::SetOutputTitle6(const MultiLanguageString& OutputTitle6)
{
    Configurator6->SetTitle(OutputTitle6);
}

void OutputWidget::SetOutputTitle7(const MultiLanguageString& OutputTitle7)
{
    Configurator7->SetTitle(OutputTitle7);
}

void OutputWidget::SetOutputTitle8(const MultiLanguageString& OutputTitle8)
{
    Configurator8->SetTitle(OutputTitle8);
}

void OutputWidget::SetOutputTitle9(const MultiLanguageString& OutputTitle9)
{
    Configurator9->SetTitle(OutputTitle9);
}

void OutputWidget::SetOutputVisible1(bool OutputVisible1)
{
    Configurator1->SetVisibility(OutputVisible1);
}

void OutputWidget::SetOutputVisible2(bool OutputVisible2)
{
    Configurator2->SetVisibility(OutputVisible2);
}

void OutputWidget::SetOutputVisible3(bool OutputVisible3)
{
    Configurator3->SetVisibility(OutputVisible3);
}

void OutputWidget::SetOutputVisible4(bool OutputVisible4)
{
    Configurator4->SetVisibility(OutputVisible4);
}

void OutputWidget::SetOutputVisible5(bool OutputVisible5)
{
    Configurator5->SetVisibility(OutputVisible5);
}

void OutputWidget::SetOutputVisible6(bool OutputVisible6)
{
    Configurator6->SetVisibility(OutputVisible6);
}

void OutputWidget::SetOutputVisible7(bool OutputVisible7)
{
    Configurator7->SetVisibility(OutputVisible7);
}

void OutputWidget::SetOutputVisible8(bool OutputVisible8)
{
    Configurator8->SetVisibility(OutputVisible8);
}

void OutputWidget::SetOutputVisible9(bool OutputVisible9)
{
    Configurator9->SetVisibility(OutputVisible9);
}

void OutputWidget::Tab1TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(0,text);
}

void OutputWidget::Tab2TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(1,text);
}

void OutputWidget::Tab3TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(2,text);
}

void OutputWidget::Tab4TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(3,text);
}


void OutputWidget::Tab5TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(4,text);
}


void OutputWidget::Tab6TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(5,text);
}


void OutputWidget::Tab7TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(6,text);
}


void OutputWidget::Tab8TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(7,text);
}


void OutputWidget::Tab9TextChanged(const QString & text)
{
    ui->tabWidget->setTabText(8,text);
}


void OutputWidget::Clear()
{
    LabelAllResults1->setVisible(true);
    LabelAllResults2->setVisible(true);
    LabelAllResults3->setVisible(true);
    LabelAllResults4->setVisible(true);
    LabelAllResults5->setVisible(true);
    LabelAllResults6->setVisible(true);
    LabelAllResults7->setVisible(true);
    LabelAllResults8->setVisible(true);
    LabelAllResults9->setVisible(true);

    SuccessCount = 0;
    FailedCount = 0;
    ui->LabelSuccess->setText("0");
    ui->LabelFailed->setText("0");

    CountOutput.clear();
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);
    CountOutput.append(0);


    QHash<QString, SolverStats>::iterator i;
    for (i = Stats.begin(); i != Stats.end(); ++i)
    {
        i.value().label1->deleteLater();
        i.value().label2->deleteLater();

    }
    Stats.clear();

    ui->Output1->clear();
    ui->Output2->clear();
    ui->Output3->clear();
    ui->Output4->clear();
    ui->Output5->clear();
    ui->Output6->clear();
    ui->Output7->clear();
    ui->Output8->clear();
    ui->Output9->clear();

    ProgressValue(0);
    ProgressMaximum(100);
    ui->progressBar->setEnabled(true);
    ui->progressBar->setVisible(false);
}

void OutputWidget::SetFileName1(const QString& FileName1)
{
    this->FileName1 = FileName1;
}
void OutputWidget::SetFileName2(const QString& FileName2)
{
    this->FileName2 = FileName2;
}
void OutputWidget::SetFileName3(const QString& FileName3)
{
    this->FileName3 = FileName3;
}
void OutputWidget::SetFileName4(const QString& FileName4)
{
    this->FileName4 = FileName4;
}
void OutputWidget::SetFileName5(const QString& FileName5)
{
    this->FileName5 = FileName5;
}
void OutputWidget::SetFileName6(const QString& FileName6)
{
    this->FileName6 = FileName6;
}
void OutputWidget::SetFileName7(const QString& FileName7)
{
    this->FileName7 = FileName7;
}
void OutputWidget::SetFileName8(const QString& FileName8)
{
    this->FileName8 = FileName8;
}
void OutputWidget::SetFileName9(const QString& FileName9)
{
    this->FileName9 = FileName9;
}

OutputWidget::~OutputWidget()
{
    delete ui;
}

void OutputWidget::AddSolver(const QString& Solver, SolverStats& stats)
{
    QLabel *l1 = new QLabel(this);
    l1->setText(QString(tr("%1 solver %2")).arg(Solver).arg("used"));
    QLabel *l2 = new QLabel(this);
    l2->setText(QString("%1").arg(QString::number(stats.Used)));
    l2->setStyleSheet("font: bold;");
    ui->formLayout->addRow(l1,l2);
    stats.label2 = l2;
    stats.label1 = l1;

}



QTextBrowser *OutputWidget::GetOutput(int number)
{
    switch(number)
    {
        case 0: return ui->Output1;
        case 1: return ui->Output2;
        case 2: return ui->Output3;
        case 3: return ui->Output4;
        case 4: return ui->Output5;
        case 5: return ui->Output6;
        case 6: return ui->Output7;
        case 7: return ui->Output8;
        case 8: return ui->Output9;
    }
    return 0;
}

void OutputWidget::Success()
{
    ui->LabelSuccess->setText(QString::number(++SuccessCount));

}

void OutputWidget::Failed()
{
    ui->LabelFailed->setText(QString::number(++FailedCount));
}

void OutputWidget::UsedSolver(const QString &Solver)
{

    if(Stats.contains(Solver))
    {
        SolverStats stats = Stats[Solver];
        stats.Used ++;
        stats.label2->setText(QString::number(stats.Used));
        Stats[Solver] = stats;
    }else
    {
        SolverStats stats;
        stats.Used = 1;
        AddSolver(Solver,stats);
        Stats[Solver] = stats;
    }
}


void OutputWidget::ProgressValue(int value)
{
    ui->progressBar->setVisible(true);
    if(value<0)
        ui->progressBar->setValue(ui->progressBar->value() - value);
    else
        ui->progressBar->setValue(value);
}

void OutputWidget::ProgressMaximum(int maximum)
{
    ui->progressBar->setVisible(true);
    ui->progressBar->setMaximum(maximum);
}

void OutputWidget::Finished()
{
    ui->progressBar->setEnabled(false);
}

void OutputWidget::AddedOutput(int number)
{
    if(number<0 || number>8)
        return;

    QString TabName;
    if(number == 0)
    {
        TabName = Configurator1->GetTitleText();
    }else if(number == 1)
    {
        TabName = Configurator2->GetTitleText();
    }else if(number == 2)
    {
        TabName = Configurator3->GetTitleText();
    }else if(number == 3)
    {
        TabName = Configurator4->GetTitleText();
    }else if(number == 4)
    {
        TabName = Configurator5->GetTitleText();
    }else if(number == 5)
    {
        TabName = Configurator6->GetTitleText();
    }else if(number == 6)
    {
        TabName = Configurator7->GetTitleText();
    }else if(number == 7)
    {
        TabName = Configurator8->GetTitleText();
    }else if(number == 8)
    {
        TabName = Configurator9->GetTitleText();
    }
    ui->tabWidget->setTabText(number,QString("%1 (%2)").arg(TabName).arg(QString::number(++CountOutput[number])));
}


void OutputWidget::LabelAllResults1_linkActivated()
{
    QFileInfo info(FileName1);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults2_linkActivated()
{
    QFileInfo info(FileName2);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults3_linkActivated()
{
    QFileInfo info(FileName3);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults4_linkActivated()
{
    QFileInfo info(FileName4);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults5_linkActivated()
{
    QFileInfo info(FileName5);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults6_linkActivated()
{
    QFileInfo info(FileName6);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults7_linkActivated()
{
    QFileInfo info(FileName7);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults8_linkActivated()
{
    QFileInfo info(FileName8);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::LabelAllResults9_linkActivated()
{
    QFileInfo info(FileName9);
    QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
}

void OutputWidget::SetConfiguratorVisible(bool Visible)
{
    Configurator1->setVisible(Visible);
    Configurator2->setVisible(Visible);
    Configurator3->setVisible(Visible);
    Configurator4->setVisible(Visible);
    Configurator5->setVisible(Visible);
    Configurator6->setVisible(Visible);
    Configurator7->setVisible(Visible);
    Configurator8->setVisible(Visible);
    Configurator9->setVisible(Visible);
    if(Visible)
    {
        while(ui->tabWidget->count() > 0)
            ui->tabWidget->removeTab(0);

        ui->tabWidget->addTab(tab1, Configurator1->GetTitleText());
        ui->tabWidget->addTab(tab2, Configurator2->GetTitleText());
        ui->tabWidget->addTab(tab3, Configurator3->GetTitleText());
        ui->tabWidget->addTab(tab4, Configurator4->GetTitleText());
        ui->tabWidget->addTab(tab5, Configurator5->GetTitleText());
        ui->tabWidget->addTab(tab6, Configurator6->GetTitleText());
        ui->tabWidget->addTab(tab7, Configurator7->GetTitleText());
        ui->tabWidget->addTab(tab8, Configurator8->GetTitleText());
        ui->tabWidget->addTab(tab9, Configurator9->GetTitleText());

    }else
    {
        while(ui->tabWidget->count() > 0)
            ui->tabWidget->removeTab(0);

        if(Configurator1->GetVisibility())
            ui->tabWidget->addTab(tab1, Configurator1->GetTitleText());

        if(Configurator2->GetVisibility())
            ui->tabWidget->addTab(tab2, Configurator2->GetTitleText());

        if(Configurator3->GetVisibility())
            ui->tabWidget->addTab(tab3, Configurator3->GetTitleText());

        if(Configurator4->GetVisibility())
            ui->tabWidget->addTab(tab4, Configurator4->GetTitleText());

        if(Configurator5->GetVisibility())
            ui->tabWidget->addTab(tab5, Configurator5->GetTitleText());

        if(Configurator6->GetVisibility())
            ui->tabWidget->addTab(tab6, Configurator6->GetTitleText());

        if(Configurator7->GetVisibility())
            ui->tabWidget->addTab(tab7, Configurator7->GetTitleText());

        if(Configurator8->GetVisibility())
            ui->tabWidget->addTab(tab8, Configurator8->GetTitleText());

        if(Configurator9->GetVisibility())
            ui->tabWidget->addTab(tab9, Configurator9->GetTitleText());
    }
}

void OutputWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
