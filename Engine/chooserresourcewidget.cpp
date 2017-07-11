#include "chooserresourcewidget.h"
#include "ui_chooserresourcewidget.h"
#include <QFileDialog>
#include <QToolBar>
#include "every_cpp.h"

#include "toprightpositioner.h"

ChooserResourceWidget::ChooserResourceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooserResourceWidget), StringBuilder(0), LastTableId(-1)
{
    ui->setupUi(this);
    DatabaseIndexesChangedInAction = false;
    MultiWidget = new QxtCheckComboBox();
    MultiWidget->setObjectName("DatabaseGroups");
    MultiWidget->setParent(ui->page_9);
    MultiWidget->setDefaultText(tr("---"));
    MultiWidget->setMaximumWidth(250);
    MultiWidget->setMinimumWidth(250);

    ui->ComboLayout->addWidget(MultiWidget);
    int size = ui->stackedWidget->count();
    for(int i = 0;i<size;i++)
    {
        QWidget * Widget =  ui->stackedWidget->widget(i);
        Widgets.append(Widget);
    }

    for(int i = 0;i<size;i++)
    {
        QWidget * Widget =  ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(Widget);
    }


    on_DirectoryReload_toggled(ui->DirectoryReload->isChecked());
    on_FileReload_toggled(ui->FileReload->isChecked());
    on_UrlReload_toggled(ui->UrlReload->isChecked());
    on_DirectoryRenew_toggled(ui->DirectoryRenew->isChecked());
    on_FileRenew_toggled(ui->FileRenew->isChecked());
    on_UrlRenew_toggled(ui->UrlRenew->isChecked());
    on_DatabaseReload_toggled(ui->DatabaseReload->isChecked());
    on_DatabaseRenew_toggled(ui->DatabaseRenew->isChecked());
    ShowValidation = false;

    connect(ui->stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(Validate()));
    connect(ui->FixedStringValue,SIGNAL(textChanged(QString)),this,SLOT(Validate()));
    connect(ui->FileFilename,SIGNAL(textChanged(QString)),this,SLOT(Validate()));
    connect(ui->UrlUrl,SIGNAL(textChanged(QString)),this,SLOT(Validate()));
    connect(ui->DirectoryDirectory,SIGNAL(textChanged(QString)),this,SLOT(Validate()));
    connect(ui->FileRead,SIGNAL(toggled(bool)),this,SLOT(Validate()));
    connect(ui->FileWrite,SIGNAL(toggled(bool)),this,SLOT(Validate()));
    connect(MultiWidget,SIGNAL(checkedIndexesChanged(QList<int>,QList<int>)),this,SLOT(DatabaseIndexesChanged(QList<int>,QList<int>)));

    int MarginTop = 1;
    int MarginRight = 1;

    TopRightPositioner *Pos;

    int ValidationPixmapHeight = ui->FixedStringValue->sizeHint().height()-2;
    int ValidationPixmapWidth = ui->LabelValidation1->pixmap()->width();

    ui->LayoutValidation1->removeWidget(ui->LabelValidation1);
    ui->horizontalLayout_6->removeWidget(ui->LabelValidation2);
    ui->horizontalLayout_9->removeWidget(ui->LabelValidation3);
    ui->horizontalLayout_10->removeWidget(ui->LabelValidation4);

    ui->LabelValidation1->setPixmap(ui->LabelValidation1->pixmap()->scaled(ValidationPixmapWidth,ValidationPixmapHeight));
    ui->LabelValidation1->setMaximumHeight(ValidationPixmapHeight);
    ui->LabelValidation1->setMinimumHeight(ValidationPixmapHeight);
    ui->LabelValidation1->setMaximumWidth(ValidationPixmapWidth);
    ui->LabelValidation1->setMinimumWidth(ValidationPixmapWidth);

    ui->LabelValidation2->setPixmap(ui->LabelValidation2->pixmap()->scaled(ValidationPixmapWidth,ValidationPixmapHeight));
    ui->LabelValidation2->setMaximumHeight(ValidationPixmapHeight);
    ui->LabelValidation2->setMinimumHeight(ValidationPixmapHeight);
    ui->LabelValidation2->setMaximumWidth(ValidationPixmapWidth);
    ui->LabelValidation2->setMinimumWidth(ValidationPixmapWidth);

    ui->LabelValidation3->setPixmap(ui->LabelValidation3->pixmap()->scaled(ValidationPixmapWidth,ValidationPixmapHeight));
    ui->LabelValidation3->setMaximumHeight(ValidationPixmapHeight);
    ui->LabelValidation3->setMinimumHeight(ValidationPixmapHeight);
    ui->LabelValidation3->setMaximumWidth(ValidationPixmapWidth);
    ui->LabelValidation3->setMinimumWidth(ValidationPixmapWidth);

    ui->LabelValidation4->setPixmap(ui->LabelValidation4->pixmap()->scaled(ValidationPixmapWidth,ValidationPixmapHeight));
    ui->LabelValidation4->setMaximumHeight(ValidationPixmapHeight);
    ui->LabelValidation4->setMinimumHeight(ValidationPixmapHeight);
    ui->LabelValidation4->setMaximumWidth(ValidationPixmapWidth);
    ui->LabelValidation4->setMinimumWidth(ValidationPixmapWidth);

    ui->LabelValidation5->setPixmap(ui->LabelValidation5->pixmap()->scaled(ValidationPixmapWidth,ValidationPixmapHeight));
    ui->LabelValidation5->setMaximumHeight(ValidationPixmapHeight);
    ui->LabelValidation5->setMinimumHeight(ValidationPixmapHeight);
    ui->LabelValidation5->setMaximumWidth(ValidationPixmapWidth);
    ui->LabelValidation5->setMinimumWidth(ValidationPixmapWidth);



    Pos = new TopRightPositioner(this);
    ui->LabelValidation1->setVisible(false);



    Pos->SetChild(ui->LabelValidation1);
    Pos->SetParent(ui->FixedStringValue);
    Pos->SetMarginRight(MarginRight);
    Pos->SetMarginTop(MarginTop);
    Pos->Start();

    Pos = new TopRightPositioner(this);
    ui->LabelValidation2->setVisible(false);
    Pos->SetChild(ui->LabelValidation2);
    Pos->SetParent(ui->FileFilename);
    Pos->SetMarginRight(MarginRight);
    Pos->SetMarginTop(MarginTop);
    Pos->Start();

    Pos = new TopRightPositioner(this);
    ui->LabelValidation4->setVisible(false);
    Pos->SetChild(ui->LabelValidation4);
    Pos->SetParent(ui->DirectoryDirectory);
    Pos->SetMarginRight(MarginRight);
    Pos->SetMarginTop(MarginTop);
    Pos->Start();

    Pos = new TopRightPositioner(this);
    ui->LabelValidation3->setVisible(false);
    Pos->SetChild(ui->LabelValidation3);
    Pos->SetParent(ui->UrlUrl);
    Pos->SetMarginRight(MarginRight);
    Pos->SetMarginTop(MarginTop);
    Pos->Start();

    LastVisibleAdvanced = true;

}

void ChooserResourceWidget::SetDatabaseState(IDatabaseState * DatabaseState)
{
    this->DatabaseState = DatabaseState;
    connect(DatabaseState,SIGNAL(GroupsChanged()),this,SLOT(GroupsChanged()));
}

void ChooserResourceWidget::GroupsChanged()
{
    SetTableId(LastTableId);
}

void ChooserResourceWidget::SetTableId(int TableId)
{
    this->LastTableId = TableId;
    if(TableId == -1)
        return;
    QStringList Checked = MultiWidget->checkedData();
    MultiWidget->clear();

    foreach(DatabaseGroup Group, DatabaseState->GetGroups(TableId))
    {
        MultiWidget->addItem(Group.Name, Group.Id);
    }

    MultiWidget->setCheckedData(Checked);

}

int ChooserResourceWidget::GetTableId()
{
    return this->LastTableId;
}

void ChooserResourceWidget::DatabaseIndexesChanged(QList<int> Previous,QList<int> Now)
{
    if(DatabaseIndexesChangedInAction)
        return;


    DatabaseIndexesChangedInAction = true;
    if(!Previous.contains(0) && Now.contains(0))
        MultiWidget->setCheckedIndexes(QList<int>()<<0);
    else if(Previous.length() == 1 && Previous[0] == 0 && Now.length() == 2 && Now.contains(0))
    {
        QList<int> Next = Now;
        Next.removeAll(0);

        MultiWidget->setCheckedIndexes(Next);
    }

    Validate();
    DatabaseIndexesChangedInAction = false;
}


void ChooserResourceWidget::SetVisibleAdvanced(bool Visible)
{

    LastVisibleAdvanced = Visible;
    if(ui->stackedWidget->findChild<QWidget*>("page"))
    {
        if(!Visible)
        {
            ui->FixedStringValue->setMaximumWidth(100000);
            ui->FixedStringValue->setMinimumWidth(0);
        }else
        {
            ui->FixedStringValue->setMaximumWidth(175);
            ui->FixedStringValue->setMinimumWidth(175);
        }
        ui->label_4->setVisible(Visible);
    }

    if(ui->stackedWidget->findChild<QWidget*>("page_2"))
    {
        if(!Visible)
        {
            ui->FixedIntegerValue->setMaximumWidth(100000);
            ui->FixedIntegerValue->setMinimumWidth(0);
        }else
        {
            ui->FixedIntegerValue->setMaximumWidth(175);
            ui->FixedIntegerValue->setMinimumWidth(175);
        }
        ui->label_5->setVisible(Visible);
    }

    if(ui->stackedWidget->findChild<QWidget*>("page_4"))
    {
        if(!Visible)
        {
            ui->RandomStringValue->setMaximumWidth(100000);
            ui->RandomStringValue->setMinimumWidth(0);
        }else
        {
            ui->RandomStringValue->setMaximumWidth(150);
            ui->RandomStringValue->setMinimumWidth(150);
        }
        ui->label_8->setVisible(Visible);
    }

    if(ui->stackedWidget->findChild<QWidget*>("page_5"))
    {
        if(!Visible)
        {
            ui->RIMaximumValue->setMaximumWidth(100000);
            ui->RIMaximumValue->setMinimumWidth(0);
            ui->RIMinimumValue->setMaximumWidth(100000);
            ui->RIMinimumValue->setMinimumWidth(0);
        }else
        {
            ui->RIMaximumValue->setMaximumWidth(150);
            ui->RIMaximumValue->setMinimumWidth(150);
            ui->RIMinimumValue->setMaximumWidth(150);
            ui->RIMinimumValue->setMinimumWidth(150);
        }

    }

    if(ui->stackedWidget->findChild<QWidget*>("page_3"))
    {
        if(!Visible)
        {
            ui->formLayout_8->removeWidget(ui->label);
            ui->formLayout_8->removeWidget(ui->FileWrite);
            ui->formLayout_8->removeWidget(ui->label_50);
            ui->formLayout_8->removeWidget(ui->FileRead);
            ui->formLayout_8->removeWidget(ui->label_3);
            ui->formLayout_8->removeWidget(ui->FileMix);
            ui->formLayout_8->removeWidget(ui->label_26);
            ui->formLayout_8->removeWidget(ui->FileReload);
            ui->formLayout_8->removeWidget(ui->label_27);
            ui->formLayout_8->removeWidget(ui->FileReloadInterval);

            ui->formLayout_8->removeWidget(ui->FileMaxFail);
            ui->formLayout_8->removeWidget(ui->FileMaxSuccess);
            ui->formLayout_8->removeWidget(ui->FileMaxSimultaneous);
            ui->formLayout_8->removeWidget(ui->FileInterval);
            ui->formLayout_8->removeWidget(ui->FileGreedy);
            ui->formLayout_8->removeWidget(ui->FileRenew);
            ui->formLayout_8->removeWidget(ui->FileRenewInterval);

            ui->formLayout_8->removeWidget(ui->label_18);
            ui->formLayout_8->removeWidget(ui->label_111);
            ui->formLayout_8->removeWidget(ui->label_17);
            ui->formLayout_8->removeWidget(ui->label_19);
            ui->formLayout_8->removeWidget(ui->label_7);
            ui->formLayout_8->removeWidget(ui->label_37);
            ui->formLayout_8->removeWidget(ui->label_38);
            ui->FileFilename->setMaximumWidth(100000);
            ui->FileFilename->setMinimumWidth(0);


        }else
        {
            ui->formLayout_8->insertRow(1,ui->label_50,ui->FileRead);
            ui->formLayout_8->insertRow(2,ui->label,ui->FileWrite);
            ui->formLayout_8->insertRow(3,ui->label_3,ui->FileMix);
            ui->formLayout_8->insertRow(4,ui->label_111,ui->FileMaxSuccess);
            ui->formLayout_8->insertRow(5,ui->label_17,ui->FileMaxFail);
            ui->formLayout_8->insertRow(6,ui->label_18,ui->FileMaxSimultaneous);
            ui->formLayout_8->insertRow(7,ui->label_19,ui->FileInterval);
            ui->formLayout_8->insertRow(8,ui->label_7,ui->FileGreedy);
            ui->formLayout_8->addRow(ui->label_26,ui->FileReload);
            ui->formLayout_8->addRow(ui->label_27,ui->FileReloadInterval);
            ui->formLayout_8->addRow(ui->label_37,ui->FileRenew);
            ui->formLayout_8->addRow(ui->label_38,ui->FileRenewInterval);

            ui->FileFilename->setMaximumWidth(100);
            ui->FileFilename->setMinimumWidth(100);



        }
        ui->label_10->setVisible(Visible);
        ui->label->setVisible(Visible);
        ui->label_3->setVisible(Visible);
        ui->FileMix->setVisible(Visible);
        ui->FileReload->setVisible(Visible);
        ui->FileReloadInterval->setVisible(Visible);
        ui->FileWrite->setVisible(Visible);
        ui->FileRead->setVisible(Visible);
        ui->label_50->setVisible(Visible);
        ui->label_18->setVisible(Visible);
        ui->label_111->setVisible(Visible);
        ui->label_17->setVisible(Visible);
        ui->label_19->setVisible(Visible);
        ui->label_7->setVisible(Visible);
        ui->label_37->setVisible(Visible);
        ui->label_26->setVisible(Visible);
        ui->label_27->setVisible(Visible);
        ui->label_38->setVisible(Visible);
        ui->FileMaxSimultaneous->setVisible(Visible);
        ui->FileMaxSuccess->setVisible(Visible);
        ui->FileMaxFail->setVisible(Visible);
        ui->FileInterval->setVisible(Visible);
        ui->FileGreedy->setVisible(Visible);
        ui->FileRenew->setVisible(Visible);
        ui->FileRenewInterval->setVisible(Visible);

        if(Visible)
        {
            on_FileRenew_toggled(ui->FileRenew->isChecked());
            on_FileReload_toggled(ui->FileReload->isChecked());
        }
    }


    if(ui->stackedWidget->findChild<QWidget*>("page_9"))
    {
        if(!Visible)
        {
            ui->formLayout->removeWidget(ui->label_39);
            ui->formLayout->removeWidget(ui->DatabaseClear);
            ui->formLayout->removeWidget(ui->label_40);
            ui->formLayout->removeWidget(ui->DatabaseMix);
            ui->formLayout->removeWidget(ui->label_46);
            ui->formLayout->removeWidget(ui->DatabaseReload);
            ui->formLayout->removeWidget(ui->label_47);
            ui->formLayout->removeWidget(ui->DatabaseReloadInterval);


            ui->formLayout->removeWidget(ui->DatabaseMaxFail);
            ui->formLayout->removeWidget(ui->DatabaseMaxSuccess);
            ui->formLayout->removeWidget(ui->DatabaseMaxSimultaneous);
            ui->formLayout->removeWidget(ui->DatabaseInterval);
            ui->formLayout->removeWidget(ui->DatabaseGreedy);
            ui->formLayout->removeWidget(ui->DatabaseRenew);
            ui->formLayout->removeWidget(ui->DatabaseRenewInterval);

            ui->formLayout->removeWidget(ui->label_41);
            ui->formLayout->removeWidget(ui->label_42);
            ui->formLayout->removeWidget(ui->label_43);
            ui->formLayout->removeWidget(ui->label_44);
            ui->formLayout->removeWidget(ui->label_45);
            ui->formLayout->removeWidget(ui->label_48);
            ui->formLayout->removeWidget(ui->label_49);

            ui->horizontalSpacer->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);

            MultiWidget->setMaximumWidth(100000);
            MultiWidget->setMinimumWidth(0);

        }else
        {
            ui->formLayout->insertRow(1,ui->label_39,ui->DatabaseClear);
            ui->formLayout->insertRow(2,ui->label_40,ui->DatabaseMix);
            ui->formLayout->insertRow(3,ui->label_41,ui->DatabaseMaxSuccess);
            ui->formLayout->insertRow(4,ui->label_42,ui->DatabaseMaxFail);
            ui->formLayout->insertRow(5,ui->label_43,ui->DatabaseMaxSimultaneous);
            ui->formLayout->insertRow(6,ui->label_44,ui->DatabaseInterval);
            ui->formLayout->insertRow(7,ui->label_45,ui->DatabaseGreedy);
            ui->formLayout->addRow(ui->label_46,ui->DatabaseReload);
            ui->formLayout->addRow(ui->label_47,ui->DatabaseReloadInterval);
            ui->formLayout->addRow(ui->label_48,ui->DatabaseRenew);
            ui->formLayout->addRow(ui->label_49,ui->DatabaseRenewInterval);

            ui->horizontalSpacer->changeSize(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

            MultiWidget->setMaximumWidth(250);
            MultiWidget->setMinimumWidth(250);


        }
        ui->widget_2->setVisible(Visible);

        ui->label_39->setVisible(Visible);
        ui->label_40->setVisible(Visible);
        ui->label_46->setVisible(Visible);
        ui->label_47->setVisible(Visible);
        ui->label_41->setVisible(Visible);
        ui->label_42->setVisible(Visible);
        ui->label_43->setVisible(Visible);
        ui->label_44->setVisible(Visible);
        ui->label_45->setVisible(Visible);
        ui->label_48->setVisible(Visible);
        ui->label_49->setVisible(Visible);
        ui->DatabaseMaxSimultaneous->setVisible(Visible);
        ui->DatabaseMaxSuccess->setVisible(Visible);
        ui->DatabaseMaxFail->setVisible(Visible);
        ui->DatabaseInterval->setVisible(Visible);
        ui->DatabaseGreedy->setVisible(Visible);
        ui->DatabaseRenew->setVisible(Visible);
        ui->DatabaseRenewInterval->setVisible(Visible);
        ui->DatabaseClear->setVisible(Visible);
        ui->DatabaseMix->setVisible(Visible);
        ui->DatabaseReload->setVisible(Visible);
        ui->DatabaseReloadInterval->setVisible(Visible);

        if(Visible)
        {
            on_DatabaseRenew_toggled(ui->DatabaseRenew->isChecked());
            on_DatabaseReload_toggled(ui->DatabaseReload->isChecked());
        }
    }

    if(ui->stackedWidget->findChild<QWidget*>("page_7"))
    {
        if(!Visible)
        {
            ui->formLayout_9->removeWidget(ui->label_13);
            ui->formLayout_9->removeWidget(ui->UrlMix);
            ui->formLayout_9->removeWidget(ui->label_29);
            ui->formLayout_9->removeWidget(ui->UrlReload);
            ui->formLayout_9->removeWidget(ui->label_28);
            ui->formLayout_9->removeWidget(ui->UrlReloadInterval);


            ui->formLayout_9->removeWidget(ui->UrlMaxSuccess);
            ui->formLayout_9->removeWidget(ui->UrlMaxFail);
            ui->formLayout_9->removeWidget(ui->UrlMaxSimultaneous);
            ui->formLayout_9->removeWidget(ui->UrlInterval);
            ui->formLayout_9->removeWidget(ui->UrlGreedy);
            ui->formLayout_9->removeWidget(ui->UrlRenew);
            ui->formLayout_9->removeWidget(ui->UrlRenewInterval);


            ui->formLayout_9->removeWidget(ui->label_112);
            ui->formLayout_9->removeWidget(ui->label_20);
            ui->formLayout_9->removeWidget(ui->label_21);
            ui->formLayout_9->removeWidget(ui->label_22);
            ui->formLayout_9->removeWidget(ui->label_31);
            ui->formLayout_9->removeWidget(ui->label_35);
            ui->formLayout_9->removeWidget(ui->label_36);
            ui->UrlUrl->setMaximumWidth(100000);
            ui->UrlUrl->setMinimumWidth(0);
        }else
        {
            ui->formLayout_9->insertRow(2,ui->label_13,ui->UrlMix);
            ui->formLayout_9->insertRow(3,ui->label_112,ui->UrlMaxSuccess);
            ui->formLayout_9->insertRow(4,ui->label_20,ui->UrlMaxFail);
            ui->formLayout_9->insertRow(5,ui->label_21,ui->UrlMaxSimultaneous);
            ui->formLayout_9->insertRow(6,ui->label_22,ui->UrlInterval);
            ui->formLayout_9->insertRow(7,ui->label_31,ui->UrlGreedy);
            ui->formLayout_9->addRow(ui->label_29,ui->UrlReload);
            ui->formLayout_9->addRow(ui->label_28,ui->UrlReloadInterval);
            ui->formLayout_9->addRow(ui->label_35,ui->UrlRenew);
            ui->formLayout_9->addRow(ui->label_36,ui->UrlRenewInterval);

            ui->UrlUrl->setMaximumWidth(120);
            ui->UrlUrl->setMinimumWidth(120);

        }
        ui->label_11->setVisible(Visible);

        ui->label_13->setVisible(Visible);
        ui->UrlMix->setVisible(Visible);
        ui->label_28->setVisible(Visible);
        ui->label_29->setVisible(Visible);
        ui->UrlReloadInterval->setVisible(Visible);
        ui->UrlReload->setVisible(Visible);
        ui->label_112->setVisible(Visible);
        ui->label_20->setVisible(Visible);
        ui->label_21->setVisible(Visible);
        ui->label_22->setVisible(Visible);
        ui->UrlMaxFail->setVisible(Visible);
        ui->UrlMaxSuccess->setVisible(Visible);
        ui->UrlMaxSimultaneous->setVisible(Visible);
        ui->UrlInterval->setVisible(Visible);
        ui->UrlGreedy->setVisible(Visible);
        ui->label_31->setVisible(Visible);
        ui->UrlRenew->setVisible(Visible);
        ui->UrlRenewInterval->setVisible(Visible);
        ui->label_35->setVisible(Visible);
        ui->label_36->setVisible(Visible);

        if(Visible)
        {
            on_UrlReload_toggled(ui->UrlReload->isChecked());
            on_UrlRenew_toggled(ui->UrlRenew->isChecked());
        }
    }

    if(ui->stackedWidget->findChild<QWidget*>("page_8"))
    {
        if(!Visible)
        {
            ui->formLayout_10->removeWidget(ui->label_16);
            ui->formLayout_10->removeWidget(ui->DirectoryWildcard);
            ui->formLayout_10->removeWidget(ui->label_14);
            ui->formLayout_10->removeWidget(ui->DirectoryClean);
            ui->formLayout_10->removeWidget(ui->label_15);
            ui->formLayout_10->removeWidget(ui->DirectoryMix);
            ui->formLayout_10->removeWidget(ui->label_6);
            ui->formLayout_10->removeWidget(ui->DirectoryReload);
            ui->formLayout_10->removeWidget(ui->label_30);
            ui->formLayout_10->removeWidget(ui->DirectoryReloadInterval);


            ui->formLayout_10->removeWidget(ui->DirectoryMaxFail);
            ui->formLayout_10->removeWidget(ui->DirectoryMaxSimultaneous);
            ui->formLayout_10->removeWidget(ui->DirectoryMaxSuccess);
            ui->formLayout_10->removeWidget(ui->DirectoryInterval);
            ui->formLayout_10->removeWidget(ui->DirectoryGreedy);
            ui->formLayout_10->removeWidget(ui->DirectoryRenew);
            ui->formLayout_10->removeWidget(ui->DirectoryRenewInterval);

            ui->formLayout_10->removeWidget(ui->label_113);
            ui->formLayout_10->removeWidget(ui->label_23);
            ui->formLayout_10->removeWidget(ui->label_24);
            ui->formLayout_10->removeWidget(ui->label_25);
            ui->formLayout_10->removeWidget(ui->label_32);
            ui->formLayout_10->removeWidget(ui->label_33);
            ui->formLayout_10->removeWidget(ui->label_34);
            ui->DirectoryDirectory->setMaximumWidth(100000);
            ui->DirectoryDirectory->setMinimumWidth(0);
        }else
        {
            ui->formLayout_10->insertRow(1,ui->label_16,ui->DirectoryWildcard);
            ui->formLayout_10->insertRow(2,ui->label_14,ui->DirectoryClean);
            ui->formLayout_10->insertRow(3,ui->label_15,ui->DirectoryMix);
            ui->formLayout_10->insertRow(4,ui->label_113,ui->DirectoryMaxSuccess);
            ui->formLayout_10->insertRow(5,ui->label_23,ui->DirectoryMaxFail);
            ui->formLayout_10->insertRow(6,ui->label_24,ui->DirectoryMaxSimultaneous);
            ui->formLayout_10->insertRow(7,ui->label_25,ui->DirectoryInterval);
            ui->formLayout_10->insertRow(8,ui->label_32,ui->DirectoryGreedy);
            ui->formLayout_10->insertRow(9,ui->label_6,ui->DirectoryReload);
            ui->formLayout_10->insertRow(10,ui->label_30,ui->DirectoryReloadInterval);
            ui->formLayout_10->addRow(ui->label_33,ui->DirectoryRenew);
            ui->formLayout_10->addRow(ui->label_34,ui->DirectoryRenewInterval);
            ui->DirectoryDirectory->setMaximumWidth(100);
            ui->DirectoryDirectory->setMinimumWidth(100);
        }

        ui->label_12->setVisible(Visible);
        ui->label_16->setVisible(Visible);
        ui->DirectoryWildcard->setVisible(Visible);
        ui->label_14->setVisible(Visible);
        ui->DirectoryClean->setVisible(Visible);
        ui->label_15->setVisible(Visible);
        ui->DirectoryMix->setVisible(Visible);
        ui->label_6->setVisible(Visible);
        ui->DirectoryReload->setVisible(Visible);
        ui->label_30->setVisible(Visible);
        ui->DirectoryReloadInterval->setVisible(Visible);


        ui->label_113->setVisible(Visible);
        ui->label_23->setVisible(Visible);
        ui->label_24->setVisible(Visible);
        ui->label_25->setVisible(Visible);
        ui->DirectoryMaxFail->setVisible(Visible);
        ui->DirectoryMaxSimultaneous->setVisible(Visible);
        ui->DirectoryMaxSuccess->setVisible(Visible);
        ui->DirectoryInterval->setVisible(Visible);
        ui->label_32->setVisible(Visible);
        ui->DirectoryGreedy->setVisible(Visible);
        ui->DirectoryRenew->setVisible(Visible);
        ui->DirectoryRenewInterval->setVisible(Visible);
        ui->label_33->setVisible(Visible);
        ui->label_34->setVisible(Visible);

        if(Visible)
        {
            on_DirectoryRenew_toggled(ui->DirectoryRenew->isChecked());
            on_DirectoryReload_toggled(ui->DirectoryReload->isChecked());
        }
    }


}

void ChooserResourceWidget::Validate()
{
    bool PreviousValidationRes = LastValidateResult;
    LastValidateResult = true;


    QString name;
    if(ui->stackedWidget->currentWidget())
    {
        name = ui->stackedWidget->currentWidget()->objectName();
    }


        if(name == "page_9")
        {
            if(MultiWidget->currentIndexes().isEmpty() && ShowValidation)
            {
                ui->LabelValidation5->setVisible(true);
                MultiWidget->setToolTip(tr("No groups selected"));

                LastValidateResult = false;
            }else
            {
                ui->LabelValidation5->setVisible(false);

                MultiWidget->setToolTip("");
            }

        }else if(name == "page")
        {
            bool NeedValidate = false;
            QVariant p = ui->FixedStringValue->property("NotEmpty");
            if(!p.isNull())
            {
                NeedValidate = p.toBool();
            }
            if(ui->FixedStringValue->text().isEmpty() && ShowValidation && NeedValidate)
            {
                ui->LabelValidation1->setVisible(true);
                ui->FixedStringValue->setToolTip(tr("Field is empty"));

                LastValidateResult = false;
            }else
            {
                ui->LabelValidation1->setVisible(false);

                ui->FixedStringValue->setToolTip("");
            }

        }else if(name == "page_3")
        {

            if(ShowValidation)
            {
                bool IsValid = false;
                QString filename = ui->FileFilename->text();
                if(filename.isEmpty())
                {
                    IsValid = !ui->FileWrite->isChecked() && !ui->FileRead->isChecked();
                }else
                {

                    foreach(QString f,filename.split("|"))
                    {
                        QFileInfo info(f);
                        IsValid = !ui->FileRead->isChecked() || info.exists();
                        if(!IsValid)
                        {
                            break;
                        }

                    }

                }

                if(!IsValid)
                {
                    ui->LabelValidation2->setVisible(true);
                    ui->FileFilename->setToolTip(tr("File not exists"));

                    LastValidateResult = false;
                }else
                {
                    ui->LabelValidation2->setVisible(false);
                    ui->FileFilename->setToolTip("");
                }
            }

        }else if(name == "page_7")
        {

            if(ShowValidation)
            {
                bool IsValid = false;
                QString urlstring = ui->UrlUrl->text();
                if(urlstring.isEmpty())
                {
                    IsValid = false;
                }else
                {

                    foreach(QString s,urlstring.split("|"))
                    {
                        QUrl url(s);
                        IsValid = url.isValid() && (url.scheme() == "http" || url.scheme() == "https") && !url.host().isEmpty();
                        if(!IsValid)
                        {
                           break;
                        }
                    }
                }

                if(!IsValid)
                {
                    ui->LabelValidation3->setVisible(true);
                    ui->UrlUrl->setToolTip(tr("Url not valid"));

                    LastValidateResult = false;
                }else
                {
                    ui->LabelValidation3->setVisible(false);
                    ui->UrlUrl->setToolTip("");
                }
            }

        }else if(name == "page_8")
        {

            if(ShowValidation)
            {
                bool IsValid = false;
                QString dir = ui->DirectoryDirectory->text();
                if(dir.isEmpty())
                {
                    IsValid = false;
                }else
                {
                    QFileInfo info(dir);
                    IsValid = info.exists() && info.isDir();
                }

                if(!IsValid)
                {
                    ui->LabelValidation4->setVisible(true);
                    ui->DirectoryDirectory->setToolTip(tr("Directory not exists"));

                    LastValidateResult = false;
                }else
                {
                    ui->LabelValidation4->setVisible(false);
                    ui->DirectoryDirectory->setToolTip("");
                }
            }

        }



    if(PreviousValidationRes != LastValidateResult)
        emit ValidationStateChanged();

}

void ChooserResourceWidget::SetShowValidation(bool ShowValidation)
{
    this->ShowValidation = ShowValidation;
    Validate();
}

bool ChooserResourceWidget::IsValid()
{
    Validate();
    return LastValidateResult;
}

IStringBuilder * ChooserResourceWidget::GetStringBuilder()
{
    return StringBuilder;
}

void ChooserResourceWidget::SetStringBuilder(IStringBuilder * val)
{

    StringBuilder = val;

}

void ChooserResourceWidget::SetRandomStringEdit(const QString& val)
{
    ui->RandomStringValue->setText(val);
}

void ChooserResourceWidget::setCurrentIndex(int index)
{

    int size = ui->stackedWidget->count();
    for(int i = 0;i<size;i++)
    {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(i));
    }

    QWidget* Widget = Widgets.at(index);
    ui->stackedWidget->addWidget(Widget);
    ui->stackedWidget->setCurrentIndex(0);

    //Widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    //Widget->adjustSize();
    //ui->stackedWidget->adjustSize();
    SetVisibleAdvanced(LastVisibleAdvanced);
}

ChooserResourceWidget::~ChooserResourceWidget()
{
    delete ui;
}

QWidget* ChooserResourceWidget::GetTemplateWidgetByIndex(int index)
{
    return Widgets.at(index);
}

void ChooserResourceWidget::RemoveWidgetAtIndex(int index)
{

    QWidget *widget = GetTemplateWidgetByIndex(index);
    Widgets.removeAt(index);
    delete widget;
}

void ChooserResourceWidget::on_ButtonFileSelect_clicked()
{
    if(ui->FileRead->isChecked())
    {
        QString fileName = QFileDialog::getOpenFileNames(this, tr("Open File"), "", tr("All Files (*.*)")).join("|");
        if(fileName.length()>0)
        {
            ui->FileFilename->setText(fileName);
        }
    }else
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("All Files (*.*)"));
        if(fileName.length()>0)
        {
            ui->FileFilename->setText(fileName);
        }
    }

}

void ChooserResourceWidget::on_ButtonDirectorySelect_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",0);
    if(directory.length()>0)
    {
        ui->DirectoryDirectory->setText(directory);
    }
}


void ChooserResourceWidget::on_RandomStringEdit_clicked()
{
    disconnect(StringBuilder,SIGNAL(Changed(QString)),this,SLOT(SetRandomStringEdit(QString)));
    connect(StringBuilder,SIGNAL(Changed(QString)),this,SLOT(SetRandomStringEdit(QString)));

    StringBuilder->Show(ui->RandomStringValue->text());
    disconnect(StringBuilder,SIGNAL(Changed(QString)),this,SLOT(SetRandomStringEdit(QString)));

}

void ChooserResourceWidget::on_DirectoryReload_toggled(bool checked)
{
    ui->DirectoryReloadInterval->setVisible(checked);
    ui->label_30->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_10->removeWidget(ui->DirectoryReloadInterval);
        ui->formLayout_10->removeWidget(ui->label_30);
    }else
    {
        int position;
        ui->formLayout_10->getWidgetPosition(ui->DirectoryReload,&position,0);

        ui->formLayout_10->insertRow(position + 1,ui->label_30,ui->DirectoryReloadInterval);
    }
}


void ChooserResourceWidget::on_FileReload_toggled(bool checked)
{
    ui->FileReloadInterval->setVisible(checked);
    ui->label_27->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_8->removeWidget(ui->FileReloadInterval);
        ui->formLayout_8->removeWidget(ui->label_27);
    }else
    {
        int position;
        ui->formLayout_8->getWidgetPosition(ui->FileReload,&position,0);

        ui->formLayout_8->insertRow(position + 1,ui->label_27,ui->FileReloadInterval);
    }
}


void ChooserResourceWidget::changeEvent(QEvent *e)
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





void ChooserResourceWidget::on_UrlReload_toggled(bool checked)
{
    ui->UrlReloadInterval->setVisible(checked);
    ui->label_28->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_9->removeWidget(ui->UrlReloadInterval);
        ui->formLayout_9->removeWidget(ui->label_28);
    }else
    {
        int position;
        ui->formLayout_9->getWidgetPosition(ui->UrlReload,&position,0);
        ui->formLayout_9->insertRow(position + 1,ui->label_28,ui->UrlReloadInterval);
    }
}


void ChooserResourceWidget::on_FileRenew_toggled(bool checked)
{
    ui->FileRenewInterval->setVisible(checked);
    ui->label_38->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_8->removeWidget(ui->FileRenewInterval);
        ui->formLayout_8->removeWidget(ui->label_38);
    }else
    {
        ui->formLayout_8->addRow(ui->label_38,ui->FileRenewInterval);
    }
}

void ChooserResourceWidget::on_UrlRenew_toggled(bool checked)
{
    ui->UrlRenewInterval->setVisible(checked);
    ui->label_36->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_9->removeWidget(ui->UrlRenewInterval);
        ui->formLayout_9->removeWidget(ui->label_36);
    }else
    {
        ui->formLayout_9->addRow(ui->label_36,ui->UrlRenewInterval);
    }
}

void ChooserResourceWidget::on_DirectoryRenew_toggled(bool checked)
{
    ui->DirectoryRenewInterval->setVisible(checked);
    ui->label_34->setVisible(checked);
    if(!checked)
    {
        ui->formLayout_10->removeWidget(ui->DirectoryRenewInterval);
        ui->formLayout_10->removeWidget(ui->label_34);
    }else
    {
        ui->formLayout_10->addRow(ui->label_34,ui->DirectoryRenewInterval);
    }
}

void ChooserResourceWidget::on_DatabaseReload_toggled(bool checked)
{
    ui->DatabaseReloadInterval->setVisible(checked);
    ui->label_47->setVisible(checked);
    if(!checked)
    {
        ui->formLayout->removeWidget(ui->DatabaseReloadInterval);
        ui->formLayout->removeWidget(ui->label_47);
    }else
    {
        int position;
        ui->formLayout->getWidgetPosition(ui->DatabaseReload,&position,0);

        ui->formLayout->insertRow(position + 1,ui->label_47,ui->DatabaseReloadInterval);
    }
}

void ChooserResourceWidget::on_DatabaseRenew_toggled(bool checked)
{
    ui->DatabaseRenewInterval->setVisible(checked);
    ui->label_49->setVisible(checked);
    if(!checked)
    {
        ui->formLayout->removeWidget(ui->DatabaseRenewInterval);
        ui->formLayout->removeWidget(ui->label_49);
    }else
    {
        ui->formLayout->addRow(ui->label_49,ui->DatabaseRenewInterval);
    }
}
