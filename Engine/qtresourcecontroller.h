#ifndef QTRESOURCECONTROLLER_H
#define QTRESOURCECONTROLLER_H
#include "engine_global.h"

#include "iresourcecontroller.h"
#include "flowlayout.h"
#include "iresourcewidgetfactory.h"
#include "ExtendedTabWidget.h"
#include "ilanguagemodel.h"
#include "multiselect.h"
#include "extendedtabwidgetvalidator.h"
#include "generalvalidator.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT QtResourceController : public IResourceController
    {
        Q_OBJECT
        QWidget * Widget;
        ExtendedTabWidget *TabWidget;
        ExtendedTabWidgetValidator *Validator;
        GeneralValidator *AllValidator;
        FlowLayout *Layout;
        void GetTabWiget();
        FlowLayout * GetLayoutForSection(const QString& SectionName);
        IResourceWidgetFactory *WidgetFactory;
        bool IncludeSections;
        QString Language;
        void DeleteAllModel(IResources * resources);
        void CheckIfAllSectionsAreEmpty(IResources * resources);
        ILanguageModel* LanguageModel;
        IResourceModel* GetModelByType(const QString& Type, IResourceWidget*r);
        void ShowModel(const QString &Type, IResourceModel* res, IResourceWidget *w, QHash<QString, QPair<MultiSelect*, IResourceWidget *> >& Triggers);
        bool UseAccordion;
    public:
        explicit QtResourceController(QObject *parent = 0);

    signals:
        void NewResourceWidget(IResourceWidget *Widget);
        void WidgetGenerationDone();
    public slots:
        IValidator* GetValidator();
        void DeleteAllView();
        QWidget * GetWidget();
        void SetWidget(QWidget *Widget);
        void SetLanguage(const QString& Language);
        void SetLanguageModel(ILanguageModel* LanguageModel);
        void SetUseAccordion();
        void AddWidgetToView();
        void SetResourceWidgetFactory(IResourceWidgetFactory *WidgetFactory);
        virtual void FromViewToModel(IResources * resources, bool Clear = true);
        virtual void FromModelToView(IResources * resources, bool Clear = true);
        bool GetIncludeSections();
        void SetIncludeSections(bool IncludeSections);


    };
}

#endif // QTRESOURCECONTROLLER_H
