#include "qtresourcecontroller.h"
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>

#include <QCheckBox>
#include <QPlainTextEdit>
#include <QComboBox>
#include "qxtcheckcombobox.h"
#include "dragsection.h"
#include "designchooserresourcewidget.h"

#include "resourcemodelfixedstring.h"
#include "resourcemodelfixedinteger.h"
#include "resourcemodelrandominteger.h"
#include "resourcemodelrandomstring.h"
#include "resourcemodelfile.h"
#include "resourcemodeldirectory.h"
#include "resourcemodelurl.h"
#include "resourcemodelselect.h"
#include "resourcemodeldatabase.h"
#include "userresourcewidget.h"
#include "multilanguagestring.h"
#include "qAccordion/qaccordion.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    QtResourceController::QtResourceController(QObject *parent) :
        IResourceController(parent), TabWidget(0), Layout(0), UseAccordion(false), UseUIConstructor(false)
    {
        AllValidator = new GeneralValidator(this);
        WidgetUIConstructor = 0;
        ConstructResource = 0;
    }

    void QtResourceController::SetConstructResource(IConstructResource *ConstructResource)
    {
        this->ConstructResource = ConstructResource;
    }

    void QtResourceController::SetUseAccordion()
    {
        UseAccordion = true;
    }

    void QtResourceController::SetUseUIConstructor()
    {
        UseUIConstructor = true;
    }

    void QtResourceController::SetLanguage(const QString& Language)
    {
        this->Language = Language;
    }

    void QtResourceController::SetLanguageModel(ILanguageModel* LanguageModel)
    {
        this->LanguageModel = LanguageModel;
    }

    QWidget * QtResourceController::GetWidget()
    {
        return Widget;

    }

    void QtResourceController::SetWidget(QWidget * Widget)
    {
        this->Widget = Widget;
    }

    void QtResourceController::SetResourceWidgetFactory(IResourceWidgetFactory *WidgetFactory)
    {
        this->WidgetFactory = WidgetFactory;
    }


    bool QtResourceController::GetIncludeSections()
    {
        return IncludeSections;
    }

    void QtResourceController::SetIncludeSections(bool IncludeSections)
    {
        this->IncludeSections = IncludeSections;
    }

    IResourceModel* QtResourceController::GetModelByType(const QString& Type, IResourceWidget*r)
    {
        QWidget *w = r->GetTemplateWidgetByType(true,Type);
        if(Type == "FixedString")
        {
            ResourceModelFixedString *m = new ResourceModelFixedString();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());
            m->SetValue(w->findChild<QLineEdit *>("FixedStringValue")->text());
            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());

            QCheckBox * e = r->GetTemplateWidgetByType(false,Type)->findChild<QCheckBox *>("NotEmptyCheckBox");
            if(e)
                m->SetNotEmpty(e->isChecked());
            else
            {
                m->SetNotEmpty(w->findChild<QLineEdit *>("FixedStringValue")->property("NotEmpty").toBool());
            }


            return m;
        }else if(Type == "FixedInteger")
        {
            ResourceModelFixedInteger *m = new ResourceModelFixedInteger();
            m->SetName(r->GetVariableName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetSectionName(r->GetSectionName());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());

            m->SetDescription(r->GetDescription());
            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            m->SetValue(w->findChild<QSpinBox *>("FixedIntegerValue")->value());

            QSpinBox * e = r->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMinimum");
            if(e)
                m->SetMinValue(e->value());

            e = r->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMaximum");
            if(e)
                m->SetMaxValue(e->value());

            return m;
        }else if(Type == "RandomString")
        {
            ResourceModelRandomString *m = new ResourceModelRandomString();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());
            m->SetValue(w->findChild<QLineEdit *>("RandomStringValue")->text());
            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            return m;
        }else if(Type == "RandomInteger")
        {
            ResourceModelRandomInteger *m = new ResourceModelRandomInteger();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());
            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            m->SetMinUserValue(w->findChild<QSpinBox *>("RIMinimumValue")->value());
            m->SetMaxUserValue(w->findChild<QSpinBox *>("RIMaximumValue")->value());


            QSpinBox * e = r->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMinimum_2");
            if(e)
                m->SetMinDesignValue(e->value());

            e = r->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMaximum_2");
            if(e)
                m->SetMaxDesignValue(e->value());

            return m;
        }else if(Type == "LinesFromFile")
        {
            ResourceModelFile *m = new ResourceModelFile();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());
            m->SetFilename(w->findChild<QLineEdit *>("FileFilename")->text());
            m->SetRead(w->findChild<QCheckBox *>("FileRead")->isChecked());
            m->SetWrite(w->findChild<QCheckBox *>("FileWrite")->isChecked());
            m->SetMix(w->findChild<QCheckBox *>("FileMix")->isChecked());
            m->SetSuccessAttempts(w->findChild<QSpinBox *>("FileMaxSuccess")->value());
            m->SetFailAttempts(w->findChild<QSpinBox *>("FileMaxFail")->value());
            m->SetNumberSimultaneousUse(w->findChild<QSpinBox *>("FileMaxSimultaneous")->value());
            m->SetIntervalBetweenUsage(w->findChild<QSpinBox *>("FileInterval")->value());
            if(w->findChild<QCheckBox *>("FileReload")->isChecked())
                m->SetLoadInterval(w->findChild<QSpinBox *>("FileReloadInterval")->value());
            else
                m->SetLoadInterval(0);

            if(w->findChild<QCheckBox *>("FileRenew")->isChecked())
                m->SetRenewInterval(w->findChild<QSpinBox *>("FileRenewInterval")->value());
            else
                m->SetRenewInterval(-1);

            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            m->SetGreedy(w->findChild<QCheckBox *>("FileGreedy")->isChecked());

            return m;
        }else if(Type == "Database")
        {
            ResourceModelDatabase *m = new ResourceModelDatabase();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());

            m->SetGroupList(w->findChild<QxtCheckComboBox *>("DatabaseGroups")->checkedData());

            if(r->GetTemplateWidgetByType(false,Type))
            {
                m->SetTableId(r->GetTemplateWidgetByType(false,Type)->findChild<QComboBox*>("TableCombobox")->currentData().toInt());
                m->SetColumnIds(qobject_cast<DesignChooserResourceWidget*>(r->GetTemplateWidgetByType(false,Type)->parentWidget()->parentWidget())->GetDatabaseColumnsIds());
            }else
            {
                m->SetTableId(r->GetTableId());
                m->SetColumnIds(qobject_cast<UserResourceWidget*>(r->GetMainWidget())->GetColumnIds());
            }



            m->SetClean(w->findChild<QCheckBox *>("DatabaseClear")->isChecked());
            m->SetMix(w->findChild<QCheckBox *>("DatabaseMix")->isChecked());
            m->SetSuccessAttempts(w->findChild<QSpinBox *>("DatabaseMaxSuccess")->value());
            m->SetFailAttempts(w->findChild<QSpinBox *>("DatabaseMaxFail")->value());
            m->SetNumberSimultaneousUse(w->findChild<QSpinBox *>("DatabaseMaxSimultaneous")->value());
            m->SetIntervalBetweenUsage(w->findChild<QSpinBox *>("DatabaseInterval")->value());
            if(w->findChild<QCheckBox *>("DatabaseReload")->isChecked())
                m->SetLoadInterval(w->findChild<QSpinBox *>("DatabaseReloadInterval")->value());
            else
                m->SetLoadInterval(0);
            if(w->findChild<QCheckBox *>("DatabaseRenew")->isChecked())
                m->SetRenewInterval(w->findChild<QSpinBox *>("DatabaseRenewInterval")->value());
            else
                m->SetRenewInterval(-1);

            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            m->SetGreedy(w->findChild<QCheckBox *>("DatabaseGreedy")->isChecked());


            return m;
        }

        else if(Type == "FilesFromDirectory")
        {
            ResourceModelDirectory *m = new ResourceModelDirectory();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());

            m->SetDirectory(w->findChild<QLineEdit *>("DirectoryDirectory")->text());
            m->SetWildcard(w->findChild<QLineEdit *>("DirectoryWildcard")->text());
            m->SetClean(w->findChild<QCheckBox *>("DirectoryClean")->isChecked());
            m->SetMix(w->findChild<QCheckBox *>("DirectoryMix")->isChecked());
            m->SetSuccessAttempts(w->findChild<QSpinBox *>("DirectoryMaxSuccess")->value());
            m->SetFailAttempts(w->findChild<QSpinBox *>("DirectoryMaxFail")->value());
            m->SetNumberSimultaneousUse(w->findChild<QSpinBox *>("DirectoryMaxSimultaneous")->value());
            m->SetIntervalBetweenUsage(w->findChild<QSpinBox *>("DirectoryInterval")->value());
            if(w->findChild<QCheckBox *>("DirectoryReload")->isChecked())
                m->SetLoadInterval(w->findChild<QSpinBox *>("DirectoryReloadInterval")->value());
            else
                m->SetLoadInterval(0);

            if(w->findChild<QCheckBox *>("DirectoryRenew")->isChecked())
                m->SetRenewInterval(w->findChild<QSpinBox *>("DirectoryRenewInterval")->value());
            else
                m->SetRenewInterval(-1);

            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());


            m->SetGreedy(w->findChild<QCheckBox *>("DirectoryGreedy")->isChecked());



            return m;
        }else if(Type == "LinesFromUrl")
        {
            ResourceModelUrl *m = new ResourceModelUrl();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());

            m->SetUrl(w->findChild<QLineEdit *>("UrlUrl")->text());
            m->SetMix(w->findChild<QCheckBox *>("UrlMix")->isChecked());
            m->SetSuccessAttempts(w->findChild<QSpinBox *>("UrlMaxSuccess")->value());
            m->SetFailAttempts(w->findChild<QSpinBox *>("UrlMaxFail")->value());
            m->SetNumberSimultaneousUse(w->findChild<QSpinBox *>("UrlMaxSimultaneous")->value());
            m->SetIntervalBetweenUsage(w->findChild<QSpinBox *>("UrlInterval")->value());

            QComboBox * combo = r->GetTemplateWidgetByType(false,Type)->findChild<QComboBox *>("CaptureMethod");
            if(combo)
                m->SetCaptureMethod(combo->currentIndex());
            else
                m->SetCaptureMethod(w->findChild<QLineEdit *>("UrlUrl")->property("CaptureMethod").toInt());


            QLineEdit *edit = r->GetTemplateWidgetByType(false,Type)->findChild<QLineEdit *>("CaptureArgument");
            if(edit)
                m->SetCaptureArgument(edit->text());
            else
            {
                m->SetCaptureArgument(w->findChild<QLineEdit *>("UrlUrl")->property("CaptureArgument").toString());
            }


            if(w->findChild<QCheckBox *>("UrlRenew")->isChecked())
                m->SetRenewInterval(w->findChild<QSpinBox *>("UrlRenewInterval")->value());
            else
                m->SetRenewInterval(-1);


            if(w->findChild<QCheckBox *>("UrlReload")->isChecked())
                m->SetLoadInterval(w->findChild<QSpinBox *>("UrlReloadInterval")->value());
            else
                m->SetLoadInterval(-w->findChild<QSpinBox *>("UrlReloadInterval")->value());

            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());

            m->SetGreedy(w->findChild<QCheckBox *>("UrlGreedy")->isChecked());

            return m;
        }else if(Type == "Select")
        {
            ResourceModelSelect *m = new ResourceModelSelect();
            m->SetSectionName(r->GetSectionName());
            m->SetIsAdvanced(r->GetIsAdvanced());
            m->SetVisibilityConditionValue(r->GetVisibilityConditionValue());
            m->SetVisibilityConditionVariable(r->GetVisibilityConditionVariable());
            m->SetName(r->GetVariableName());
            m->SetDescription(r->GetDescription());



            QWidget *child = r->GetTemplateWidgetByType(true,Type);
            MultiSelect *multi = child->findChild<MultiSelect *>();

            m->SetValues(multi->GetValues());
            m->SetSelected(multi->GetSelectedIndex());

            if(multi->GetType() == "Radio")
                m->SetSelectType(ResourceModelSelect::Radio);
            if(multi->GetType() == "Check")
                m->SetSelectType(ResourceModelSelect::Check);
            if(multi->GetType() == "Combo")
                m->SetSelectType(ResourceModelSelect::Combo);
            if(multi->GetType() == "DragAndDrop")
                m->SetSelectType(ResourceModelSelect::DragAndDrop);


            if(r->GetAvailableNames().isEmpty())
                m->SetAllowedTypes(r->GetTypeId());
            else
                m->SetAllowedTypes(r->GetAvailableNames());
            m->SetVisibleByUser(r->GetVisibleToUser());
            m->SetEnabledByUser(r->GetEnabledToUser());
            return m;

        }
        return 0;

    }

    void QtResourceController::CreateUIConstructorWidgetIfNeeded()
    {
        if(!WidgetUIConstructor)
        {
            UIConstructor *a = new UIConstructor(Widget);
            QLabel *lab = new QLabel(Widget);
            lab->setText(tr("This is how user interface will look like:"));
            QWidget *b = new QWidget(Widget);
            QVBoxLayout *l = new QVBoxLayout(Widget);
            lab->setWordWrap(true);
            lab->setAlignment(Qt::AlignHCenter);
            lab->setMargin(5);
            l->setAlignment(Qt::AlignTop);
            l->addWidget(lab);
            l->addWidget(a);
            l->addWidget(b);
            Widget->setLayout(l);
            WidgetUIConstructor = a;
            Widget = b;
            Widget->setVisible(false);

        }else
        {
            //Clear old widgets
            UIConstructor *w = new UIConstructor(WidgetUIConstructor->parentWidget());
            ((QVBoxLayout *)WidgetUIConstructor->parentWidget()->layout())->insertWidget(1,w);
            WidgetUIConstructor->deleteLater();
            WidgetUIConstructor = w;
        }
        WidgetUIConstructor->SetLanguage(Language);

        connect(WidgetUIConstructor,SIGNAL(RemoveWidget(QWidget*)),this,SLOT(DeleteUnit(QWidget*)));
        connect(WidgetUIConstructor,SIGNAL(MoveUnitInsideTab(QWidget*,QWidget*,bool)),this,SLOT(MoveUnit(QWidget*,QWidget*,bool)));
        connect(WidgetUIConstructor,SIGNAL(UpdateClearState()),this,SLOT(UpdateClearState()));
        connect(WidgetUIConstructor,SIGNAL(ChangeTab(QWidget*,MultiLanguageString&)),this,SLOT(ChangeUnitTab(QWidget*,MultiLanguageString&)));
    }

    void QtResourceController::UpdateClearState()
    {
        if(WidgetUIConstructor && WidgetUIConstructor->IsClear())
            emit WidgetsEmpty();
    }

    void QtResourceController::DeleteUnit(QWidget* From)
    {
        From->deleteLater();
        UpdateClearState();
    }

    void QtResourceController::MoveUnit(QWidget* From, QWidget* To,bool After)
    {
        QVBoxLayout *layout =  dynamic_cast<QVBoxLayout *>(From->parentWidget()->layout());
        int index = -1;
        if(From == To)
        {
            index = layout->indexOf(To);
        }
        layout->removeWidget(From);

        if(!To)
        {
            index = 0;
        }else
        {
            if(index<0)
                index = layout->indexOf(To);

            if(After)
            {
                index++;
            }
            else
            {
                //index--;
            }
        }

        layout->insertWidget(index,From);

    }

    void QtResourceController::ChangeUnitTab(QWidget* From,MultiLanguageString& TabName)
    {
        foreach(QObject * i,From->children())
        {
            IResourceWidget* w = qobject_cast<IResourceWidget*>(i);

            if(w)
            {
                w->SetSectionName(TabName);
            }
        }
    }

    void QtResourceController::FromViewToModel(IResources * resources, bool Clear)
    {
        if(Clear)
            DeleteAllModel(resources);

        QList<QWidget *> list;
        int size = Widget->layout()->count();
        for(int i = 0;i<size;i++)
        {
            QLayoutItem * item = Widget->layout()->itemAt(i);
            if(!item)
                continue;
            QWidget *widget = item->widget();
            if(!widget)
                continue;
            list.append(widget->findChildren<QWidget *>());
            list.append(widget);
        }

        //QList<QWidget *> list = Widget->findChildren<QWidget *>();
        list.append(Widget);


        //list.append(Widget);
        //QList<QWidget *> listsearch;


        //bool AccordionFound = false;
        /*foreach(QWidget * widget,list)
        {
            QAccordion* accordion = qobject_cast<QAccordion*>(widget);
            if(accordion)
            {
                int size = accordion->numberOfContentPanes();
                for(int i = 0;i<size;i++)
                {
                    listsearch += accordion->getContentPane(i)->getContentFrame()->findChildren<QWidget *>();
                }
                AccordionFound = true;
                break;
            }
        }*/

        /*if(!AccordionFound)
        {
            listsearch = list;
        }*/

        foreach(QWidget * widget,list)
        {
            foreach(QObject * i,widget->children())
            {
                IResourceWidget* r = qobject_cast<IResourceWidget*>(i);

                if(r)
                {
                    IResourceModel *m = GetModelByType(r->GetTypeId(),r);
                    m->setParent(resources);
                    resources->GetModelList()->append(m);
                    QStringList types = r->GetAvailableNames().split(",");
                    QList<IResourceModel*> Defaults;
                    foreach(QString type, types)
                    {
                        if(type != r->GetTypeId())
                        {
                            IResourceModel *md = GetModelByType(type,r);
                            if(md)
                            {
                                md->setParent(resources);
                                Defaults.append(md);
                            }
                        }
                    }
                    m->SetDefaults(Defaults);

                }
            }
        }

    }

    void QtResourceController::GetTabWiget()
    {
        if(GetIncludeSections())
        {
            if(!TabWidget)
            {
                QLayout *LayoutSection;
                if(UseAccordion)
                {
                    LayoutSection = new FlowLayout(Widget);
                }else
                {
                    LayoutSection = new QVBoxLayout(Widget);
                }
                LayoutSection->setContentsMargins(0,0,0,0);
                LayoutSection->setSpacing(0);
                LayoutSection->setAlignment(Qt::AlignTop);
                Widget->setLayout(LayoutSection);
                TabWidget = new ExtendedTabWidget();
                Validator = new ExtendedTabWidgetValidator(TabWidget);


                LayoutSection->addWidget(TabWidget);
            }
        }else
        {
            if(!Layout)
            {
                if(UseAccordion)
                {
                    Layout = new FlowLayout(Widget);
                }else
                {
                    Layout = new QVBoxLayout(Widget);
                }
                Layout->setContentsMargins(0,0,0,0);
                Layout->setSpacing(0);
                Layout->setAlignment(Qt::AlignTop);
                Widget->setLayout(Layout);
            }
        }

    }

    QLayout * QtResourceController::GetLayoutForSection(const QString& SectionName)
    {
        GetTabWiget();
        if(GetIncludeSections())
        {
            QStringList list = TabWidget->pageTitleList();
            int index = list.indexOf(SectionName);
            if(index<0)
            {
                QWidget *widget = new QWidget(TabWidget);
                QLayout * layout;
                if(UseAccordion)
                {
                    layout = new FlowLayout(widget);
                }else
                {
                    layout = new QVBoxLayout(widget);
                }
                layout->setContentsMargins(0,0,0,0);
                layout->setSpacing(0);
                layout->setAlignment(Qt::AlignTop);


                widget->setLayout(layout);
                TabWidget->addTab(widget,SectionName);
                return layout;
            }else
            {
                QWidget *widget = TabWidget->widget(index);
                return dynamic_cast<QLayout *>(widget->layout());
            }

        }else
        {
            return Layout;
        }

    }

    void QtResourceController::DeleteAllView()
    {
        QList<QWidget *> list = Widget->findChildren<QWidget *>();
        foreach(QWidget * w,list)
        {
            if(w->parentWidget() == Widget)
            {
                w->deleteLater();
            }
        }
        emit WidgetsEmpty();
        if(UseUIConstructor)
        {
            CreateUIConstructorWidgetIfNeeded();
            //Widget->setVisible(false);
        }

    }

    void QtResourceController::DeleteAllModel(IResources * resources)
    {
        int len = resources->GetModelList()->size();
        for(int i = 0;i<len;i++)
        {
            IResourceModel* w = resources->GetModelList()->at(i);
            delete w;
        }

        resources->GetModelList()->clear();
    }

    void QtResourceController::AddWidgetToView()
    {
        IResourceWidget *w = WidgetFactory->CreateObject();
        w->SetLanguage(Language);
        w->SetLanguageModel(LanguageModel);

        w->SetTypeId("FixedStringValue");

        if(ConstructResource)
        {
            QStringList groups;
            QHash<QString,QString> VariablesAndValues;

            QList<QGroupBox*> Widgets = Widget->findChildren<QGroupBox*>("DesignResourceWidget");

            for(QGroupBox* group:Widgets)
            {
                foreach(QObject * i,group->children())
                {
                    IResourceWidget* w = qobject_cast<IResourceWidget*>(i);

                    if(w)
                    {
                        groups.append(w->GetSectionName().GetTranslation("en") + QString("|") + w->GetSectionName().GetTranslation("ru"));
                        if(w->GetTypeId() == "Select")
                        {
                            QPlainTextEdit * SelectValuesEdit = w->GetTemplateWidgetByType(false,w->GetTypeId())->findChild<QPlainTextEdit *>("SelectValuesEdit");
                            if(SelectValuesEdit)
                            {
                                VariablesAndValues.insert(w->GetVariableName(), SelectValuesEdit->toPlainText());
                            }
                        }
                    }
                }
            }
            groups.removeDuplicates();

            ConstructResource->SetGroups(groups);
            ConstructResource->SetSelectsVariablesAndValues(VariablesAndValues);
            if(!ConstructResource->ConstructResource(w))
            {
                w->deleteLater();
                return;
            }
        }
        if(w->GetVariableName().isEmpty())
        {
            w->SetVariableName("place_variable_name");
            MultiLanguageString str;
            str.SetTranslation("en","PLEASE FILL DESCRIPTION");
            str.SetTranslation("ru",QString::fromStdWString(std::wstring(L"\x0412\x0412\x0415\x0414\x0418\x0422\x0415\x0020\x041E\x041F\x0418\x0421\x0410\x041D\x0418\x0415")));
            w->SetDescription(str);
        }


        if(UseAccordion)
        {
            QLayout * Layout = GetLayoutForSection("");
            QAccordion *accordion = 0;

            /* Find accordion */
            int size = Layout->count();
            for(int i = 0;i<size;i++)
            {
                QLayoutItem *item = Layout->itemAt(i);
                QWidget *w = item->widget();
                if(w)
                {

                    accordion = qobject_cast<QAccordion *>(w);
                    if(accordion)
                    {
                        break;
                    }
                }
            }
            if(accordion == 0)
            {
                accordion = new QAccordion(Widget);
                Layout->addWidget(accordion);
            }

            if (accordion->insertContentPane(0,QString::number(qrand() % 100000) + QString(":") + w->GetVariableName()))
            {
                QFrame *contentFrame = accordion->getContentPane(0)->getContentFrame();
                accordion->getContentPane(0)->setMaximumHeight(3000);

                contentFrame->setLayout(new QVBoxLayout());
                contentFrame->layout()->addWidget(w->GetMainWidget());
                w->GetMainWidget()->setParent(contentFrame);
                accordion->getContentPane(0)->headerClicked(QPoint());

                connect(w,SIGNAL(VariableNameChanged(QString)),accordion->getContentPane(0),SLOT(setHeader(QString)));
                connect(w,SIGNAL(ResourceDestroyed()),accordion->getContentPane(0),SLOT(selfRemove()));
                connect(w,SIGNAL(ResourceDestroyed()),accordion->getContentPane(0),SLOT(deleteLater()));
                if(UseAccordion || UseUIConstructor)
                    connect(w,SIGNAL(ResourceDestroyed()),this,SLOT(ResourceDestroyed()));

                connect(w,SIGNAL(Up(int)),accordion->getContentPane(0),SLOT(selfUp()));
                connect(w,SIGNAL(Down(int)),accordion->getContentPane(0),SLOT(selfDown()));
            }


        }
        else
        {
            GetLayoutForSection("")->addWidget(w->GetMainWidget());
            //connect(w,SIGNAL(Up(int)),GetLayoutForSection(""),SLOT(moveItemUp(int)));
            //connect(w,SIGNAL(Down(int)),GetLayoutForSection(""),SLOT(moveItemDown(int)));
        }
        if(WidgetUIConstructor)
        {
            WidgetUIConstructor->AddUnitToCurrentTab(w->GetVariableName(),w->GetMainWidget());
        }
        emit WidgetsNotEmpty();
    }

    void QtResourceController::ResourceDestroyed()
    {
        if(!Widget)
        {
            emit WidgetsEmpty();
            return;
        }
        QAccordion* accordion = Widget->findChild<QAccordion *>();
        if(accordion)
        {
            int size = accordion->numberOfContentPanes();
            if(size>0)
            {
                emit WidgetsNotEmpty();
            }else
            {
                emit WidgetsEmpty();
            }
        }else
        {
            emit WidgetsEmpty();
        }
    }

    void QtResourceController::CheckIfAllSectionsAreEmpty(IResources * resources)
    {
        int size = resources->GetModelList()->size();
        for(int i = 0;i<size;i++)
        {
            IResourceModel * res = resources->GetModelList()->at(i);
            if(!res->GetSectionName().GetTranslation(Language).isEmpty())
            {
                return;
            }
        }
        SetIncludeSections(false);

    }

    void QtResourceController::ShowModel(const QString &Type, IResourceModel* res, IResourceWidget *w, QHash<QString, QPair<MultiSelect*, IResourceWidget *> >& Triggers)
    {
        if(Type == "FixedString")
        {
            QLineEdit * edit = w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("FixedStringValue");
            ResourceModelFixedString * r = qobject_cast<ResourceModelFixedString *>(res);
            if(w->GetTemplateWidgetByType(false,Type))
            {
                QCheckBox * NotEmptyCheckBox = w->GetTemplateWidgetByType(false,Type)->findChild<QCheckBox *>("NotEmptyCheckBox");
                NotEmptyCheckBox->setChecked(r->GetNotEmpty());
            }else
            {
                w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("FixedStringValue")->setProperty("NotEmpty", QVariant((bool)r->GetNotEmpty()));
            }
            if(r->GetValue() == "1")
                edit->setText("2");
            else
                edit->setText("1");

            edit->setText(r->GetValue());
        }else if(Type == "FixedInteger")
        {
            QSpinBox * edit = w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FixedIntegerValue");
            ResourceModelFixedInteger * r = qobject_cast<ResourceModelFixedInteger *>(res);
            /*QWidget * RandomInteger = w->GetTemplateWidgetByType(true,"RandomInteger");
            if(RandomInteger)
            {
                QSpinBox * RIMaximumValue = RandomInteger->findChild<QSpinBox *>("RIMaximumValue");
                QSpinBox * RIMinimumValue = RandomInteger->findChild<QSpinBox *>("RIMinimumValue");
                RIMaximumValue->setMinimum(r->GetMinValue());
                RIMaximumValue->setMaximum(r->GetMaxValue());
                RIMinimumValue->setMinimum(r->GetMinValue());
                RIMinimumValue->setMaximum(r->GetMaxValue());
            }*/


            edit->setMinimum(r->GetMinValue());
            edit->setMaximum(r->GetMaxValue());

            edit->setValue(r->GetValue());

            if(w->GetTemplateWidgetByType(false,Type))
            {
                edit = w->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMinimum");
                edit->setValue(r->GetMinValue());
                edit = w->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMaximum");
                edit->setValue(r->GetMaxValue());
            }

        }else if(Type == "RandomString")
        {
            QLineEdit * edit = w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("RandomStringValue");
            ResourceModelRandomString * r = qobject_cast<ResourceModelRandomString *>(res);
            edit->setText(r->GetValue());
        }else if(Type == "RandomInteger")
        {
            ResourceModelRandomInteger * r = qobject_cast<ResourceModelRandomInteger *>(res);
            /*QWidget * FixedInteger = w->GetTemplateWidgetByType(true,"FixedInteger");
            if(FixedInteger)
            {
                QSpinBox * edit = FixedInteger->findChild<QSpinBox *>("FixedIntegerValue");
                edit->setMinimum(r->GetMinDesignValue());
                edit->setMaximum(r->GetMaxDesignValue());
            }*/
            QSpinBox * RIMaximumValue = w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("RIMaximumValue");
            QSpinBox * RIMinimumValue = w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("RIMinimumValue");


            RIMaximumValue->setMinimum(r->GetMinDesignValue());
            RIMaximumValue->setMaximum(r->GetMaxDesignValue());
            RIMinimumValue->setMinimum(r->GetMinDesignValue());
            RIMinimumValue->setMaximum(r->GetMaxDesignValue());


            RIMinimumValue->setValue(r->GetMinUserValue());
            RIMaximumValue->setValue(r->GetMaxUserValue());

            if(w->GetTemplateWidgetByType(false,Type))
            {
                QSpinBox * edit = w->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMinimum_2");
                edit->setValue(r->GetMinDesignValue());
                edit = w->GetTemplateWidgetByType(false,Type)->findChild<QSpinBox *>("EditMaximum_2");
                edit->setValue(r->GetMaxDesignValue());
            }

        }else if(Type == "LinesFromFile")
        {
            ResourceModelFile * r = qobject_cast<ResourceModelFile *>(res);
            w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("FileFilename")->setText(r->GetFilename());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileWrite")->setChecked(r->GetWrite());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileRead")->setChecked(r->GetRead());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileMix")->setChecked(r->GetMix());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileMaxSuccess")->setValue(r->GetSuccessAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileMaxFail")->setValue(r->GetFailAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileMaxSimultaneous")->setValue(r->GetNumberSimultaneousUse());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileInterval")->setValue(r->GetIntervalBetweenUsage());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileReload")->setChecked(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileReloadInterval")->setValue(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileRenew")->setChecked(r->GetRenewInterval() > 0);
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("FileRenewInterval")->setValue(r->GetRenewInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("FileGreedy")->setChecked(r->GetGreedy());


        }else if(Type == "Database")
        {
            ResourceModelDatabase * r = qobject_cast<ResourceModelDatabase *>(res);
            w->SetTableId(r->GetTableId());
            w->GetTemplateWidgetByType(true,Type)->findChild<QxtCheckComboBox *>("DatabaseGroups")->setCheckedData(r->GetGroupList());
            QComboBox * TableCombobox = w->GetTemplateWidgetByType(false,Type)->findChild<QComboBox*>("TableCombobox");
            if(TableCombobox)
            {
                int index = -1;

                for(int i = 0;i < TableCombobox->count();i++)
                {
                    if(TableCombobox->itemData(i).toInt() == r->GetTableId())
                    {
                        index = i;
                        break;
                    }
                }
                if(index>=0)
                    TableCombobox->setCurrentIndex(index);
            }else
            {
                qobject_cast<UserResourceWidget*>(w->GetMainWidget())->SetColumnIds(r->GetColumnIds());
            }

            QWidget * Widget = w->GetTemplateWidgetByType(false,Type);
            if(Widget)
                qobject_cast<DesignChooserResourceWidget*>(Widget->parentWidget()->parentWidget())->SetDatabaseColumnsIds(r->GetColumnIds());


            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DatabaseClear")->setChecked(r->GetClean());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DatabaseMix")->setChecked(r->GetMix());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseMaxSuccess")->setValue(r->GetSuccessAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseMaxFail")->setValue(r->GetFailAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseMaxSimultaneous")->setValue(r->GetNumberSimultaneousUse());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseInterval")->setValue(r->GetIntervalBetweenUsage());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DatabaseReload")->setChecked(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseReloadInterval")->setValue(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DatabaseRenew")->setChecked(r->GetRenewInterval() > 0);
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DatabaseRenewInterval")->setValue(r->GetRenewInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DatabaseGreedy")->setChecked(r->GetGreedy());

        }else if(Type == "FilesFromDirectory")
        {
            ResourceModelDirectory * r = qobject_cast<ResourceModelDirectory *>(res);
            w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("DirectoryDirectory")->setText(r->GetDirectory());
            w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("DirectoryWildcard")->setText(r->GetWildcard());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DirectoryClean")->setChecked(r->GetClean());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DirectoryMix")->setChecked(r->GetMix());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryMaxSuccess")->setValue(r->GetSuccessAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryMaxFail")->setValue(r->GetFailAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryMaxSimultaneous")->setValue(r->GetNumberSimultaneousUse());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryInterval")->setValue(r->GetIntervalBetweenUsage());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DirectoryReload")->setChecked(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryReloadInterval")->setValue(r->GetLoadInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DirectoryRenew")->setChecked(r->GetRenewInterval() > 0);
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("DirectoryRenewInterval")->setValue(r->GetRenewInterval());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("DirectoryGreedy")->setChecked(r->GetGreedy());



        }else if(Type == "LinesFromUrl")
        {
            ResourceModelUrl * r = qobject_cast<ResourceModelUrl *>(res);
            w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("UrlUrl")->setText(r->GetUrl());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("UrlMix")->setChecked(r->GetMix());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlMaxSuccess")->setValue(r->GetSuccessAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlMaxFail")->setValue(r->GetFailAttempts());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlMaxSimultaneous")->setValue(r->GetNumberSimultaneousUse());
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlInterval")->setValue(r->GetIntervalBetweenUsage());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("UrlReload")->setChecked(r->GetLoadInterval() > 0);
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("UrlGreedy")->setChecked(r->GetGreedy());
            w->GetTemplateWidgetByType(true,Type)->findChild<QCheckBox *>("UrlRenew")->setChecked(r->GetRenewInterval() > 0);
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlRenewInterval")->setValue(r->GetRenewInterval());


            QWidget *design = w->GetTemplateWidgetByType(false,Type);

            if(design)
            {
                design->findChild<QComboBox *>("CaptureMethod")->setCurrentIndex(r->GetCaptureMethod());
                design->findChild<QLineEdit *>("CaptureArgument")->setText(r->GetCaptureArgument());
            }else
            {
                w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("UrlUrl")->setProperty("CaptureMethod", QVariant((int)r->GetCaptureMethod()));
                w->GetTemplateWidgetByType(true,Type)->findChild<QLineEdit *>("UrlUrl")->setProperty("CaptureArgument", QVariant(r->GetCaptureArgument()));
            }




            int interval = r->GetLoadInterval();
            if(interval < 0)
                interval = - interval;
            w->GetTemplateWidgetByType(true,Type)->findChild<QSpinBox *>("UrlReloadInterval")->setValue(interval);

        }else if(Type == "Select")
        {
            ResourceModelSelect * r = qobject_cast<ResourceModelSelect *>(res);
            QWidget *child = w->GetTemplateWidgetByType(true,Type)->findChild<QWidget *>("SelectWidget");
            QWidget *design = w->GetTemplateWidgetByType(false,Type);

            if(design)
            {
                QComboBox * SelectTypeCombo = design->findChild<QComboBox *>("SelectTypeCombo");
                SelectTypeCombo->setCurrentIndex(r->GetSelectType());

                QPlainTextEdit * SelectValuesEdit = design->findChild<QPlainTextEdit *>("SelectValuesEdit");
                SelectValuesEdit->setPlainText(r->GetValues().join("\r\n"));
            }

            QLayout * layout = child->layout();
            MultiSelect * OldSelect = child->findChild<MultiSelect *>();
            if(OldSelect)
                OldSelect->deleteLater();

            MultiSelect * Select = new MultiSelect(child);



            QStringList list = r->GetValues();
            QString SelectType;
            if(r->GetSelectType() == ResourceModelSelect::Radio)
                SelectType = "Radio";
            else if(r->GetSelectType() == ResourceModelSelect::Check)
                SelectType = "Check";
            else if(r->GetSelectType() == ResourceModelSelect::Combo)
                SelectType = "Combo";
            else if(r->GetSelectType() == ResourceModelSelect::DragAndDrop)
                SelectType = "DragAndDrop";

            Select->Update(SelectType, list, r->GetSelected());
            layout->addWidget(Select);
            QPair<MultiSelect*, IResourceWidget *> pair;
            pair.first = Select;
            pair.second = w;
            Triggers.insert(res->GetName(),pair);

        }
    }

    void QtResourceController::FromModelToView(IResources * resources, bool Clear)
    {
        if(Clear)
            DeleteAllView();
        int size = resources->GetModelList()->size();
        if(size > 0)
        {
            emit WidgetsNotEmpty();
        }else
        {
            emit WidgetsEmpty();
        }
        CheckIfAllSectionsAreEmpty(resources);
        GetTabWiget();

        QAccordion *accordion = 0;

        QHash<QString, QPair<MultiSelect*, IResourceWidget *> > Triggers;
        QHash<QString, QList<IResourceWidget *> > Listeners;

        for(int i = 0;i<size;i++)
        {
            IResourceModel * res = resources->GetModelList()->at(i);


            IResourceWidget *w = WidgetFactory->CreateObject();

            w->SetLanguage(Language);
            w->SetLanguageModel(LanguageModel);

            w->GetMainWidget()->setParent(Widget);


            w->SetSectionName(res->GetSectionName());
            w->SetVisibilityConditionValue(res->GetVisibilityConditionValue());

            w->SetVisibilityConditionVariable(res->GetVisibilityConditionVariable());
            w->SetVariableName(res->GetName());
            w->SetDescription(res->GetDescription());
            w->SetAvailableNames(res->GetAllowedTypes());
            //qDebug()<<1<<res->GetTypeId();
            w->SetTypeId(res->GetTypeId());
            //qDebug()<<2;
            w->SetIsAdvanced(res->GetIsAdvanced());

            if(!res->GetVisibilityConditionVariable().isEmpty())
                Listeners[res->GetVisibilityConditionVariable()].append(w);

            if(!w->GetTemplateWidgetByType(true,res->GetTypeId()))
                continue;

            QString Type = res->GetTypeId();
            ShowModel(Type,res,w,Triggers);

            QList<IResourceModel*> Defaults = res->GetDefaults();
            foreach(IResourceModel* Default,Defaults)
            {
                if(w->GetAvailableNames().contains(Default->GetTypeId()))
                    ShowModel(Default->GetTypeId(),Default,w,Triggers);
            }

            w->SetVisibleToUser(res->GetVisibleByUser());
            w->SetEnabledToUser(res->GetEnabledByUser());
            QString SectionName = res->GetSectionName().GetTranslation(Language);
            QLayout *FLayout = GetLayoutForSection(SectionName);
            if(UseAccordion)
            {
                if(!accordion)
                {
                    accordion = new QAccordion(Widget);
                    FLayout->addWidget(accordion);
                }
                int Pane = accordion->addContentPane(QString::number(qrand() % 100000) + ":" + res->GetName());
                if (Pane != -1)
                {
                    QFrame *contentFrame = accordion->getContentPane(Pane)->getContentFrame();
                    accordion->getContentPane(Pane)->setMaximumHeight(3000);

                    contentFrame->setLayout(new QVBoxLayout());
                    contentFrame->layout()->addWidget(w->GetMainWidget());
                    w->GetMainWidget()->setParent(contentFrame);

                    connect(w,SIGNAL(VariableNameChanged(QString)),accordion->getContentPane(Pane),SLOT(setHeader(QString)));
                    connect(w,SIGNAL(ResourceDestroyed()),accordion->getContentPane(Pane),SLOT(selfRemove()));
                    connect(w,SIGNAL(ResourceDestroyed()),accordion->getContentPane(Pane),SLOT(deleteLater()));
                    if(UseAccordion || UseUIConstructor)
                        connect(w,SIGNAL(ResourceDestroyed()),this,SLOT(ResourceDestroyed()));

                    connect(w,SIGNAL(Up(int)),accordion->getContentPane(Pane),SLOT(selfUp()));
                    connect(w,SIGNAL(Down(int)),accordion->getContentPane(Pane),SLOT(selfDown()));
                }

            }else
            {
                FLayout->addWidget(w->GetMainWidget());
                //connect(w,SIGNAL(Up(int)),FLayout,SLOT(moveItemUp(int)));
                //connect(w,SIGNAL(Down(int)),FLayout,SLOT(moveItemDown(int)));
            }

            if(UseUIConstructor)
            {
                WidgetUIConstructor->AddUnit(res->GetName(),w->GetSectionName(),w->GetMainWidget());
            }



            if(TabWidget)
            {
                Validator->InsertResourceWidget(TabWidget->pageTitleList().indexOf(SectionName),w);
                QObject::connect(w,SIGNAL(VisibilityChanged(bool)),TabWidget, SLOT(HideEmptyTabsAndShowVisibleTabs()));
            }
            AllValidator->InsertResourceWidget(w);
            emit NewResourceWidget(w);
        }

        QHashIterator<QString, QPair<MultiSelect*, IResourceWidget *> > i(Triggers);

        //Connect triggers
        while (i.hasNext())
        {
            i.next();
            if(Listeners.contains(i.key()))
            {
                int size = Listeners[i.key()].size();
                for(int j = 0;j<size;j++)
                {
                    IResourceWidget * w = Listeners[i.key()][j];
                    QObject::connect(i.value().first,SIGNAL(ValueChanged(QString)),w, SLOT(VisibilityTriggerChanged(QString)));
                    QObject::connect(i.value().second,SIGNAL(VisibilityChanged(bool)),w, SLOT(VisibilityParentChanged(bool)));
                }

            }
        }

        //Fire triggers
        i.toFront();
        while (i.hasNext())
        {
            i.next();
            if(Listeners.contains(i.key()))
            {
                int size = Listeners[i.key()].size();
                for(int j = 0;j<size;j++)
                {
                    IResourceWidget * w = Listeners[i.key()][j];
                    w->VisibilityTriggerChanged(i.value().first->GetSelectedValue());
                }

            }
        }

        //Connect tab visibility update listeners
        i.toFront();
        while (i.hasNext())
        {
            i.next();
            if(Listeners.contains(i.key()))
            {
                if(TabWidget)
                {
                    QObject::connect(i.value().first,SIGNAL(ValueChanged(QString)),TabWidget, SLOT(HideEmptyTabsAndShowVisibleTabs()));
                }
            }
        }

        if(TabWidget)
        {
            TabWidget->HideEmptyTabsAndShowVisibleTabs();
            Validator->SetTabWidget(TabWidget);
        }


        emit WidgetGenerationDone();

    }

    IValidator* QtResourceController::GetValidator()
    {
        return AllValidator;
    }

}



