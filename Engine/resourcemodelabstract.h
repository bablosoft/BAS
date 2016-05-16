#ifndef RESOURCEMODELABSTRACT_H
#define RESOURCEMODELABSTRACT_H
#include "engine_global.h"


#include "iresourcemodel.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceModelAbstract : public IResourceModel
    {
        Q_OBJECT
        QString Name;
        MultiLanguageString Description;
        QString Types;
        bool Visible;
        bool Enabled;
        MultiLanguageString SectionName;
        QString VisibilityConditionVariable;
        QString VisibilityConditionValue;
        QList<IResourceModel*> Defaults;
        bool IsAdvanced;
    public:
        explicit ResourceModelAbstract(QObject *parent = 0);
        virtual QString GetTypeId() = 0;
        virtual QString GetName();
        virtual void SetName(const QString& Name);
        virtual MultiLanguageString GetDescription();
        virtual void SetDescription(const MultiLanguageString& Description);
        virtual bool GetVisibleByUser();
        virtual void SetVisibleByUser(bool visible);
        virtual bool GetEnabledByUser();
        virtual void SetEnabledByUser(bool enabled);
        virtual MultiLanguageString GetSectionName();
        virtual void SetSectionName(const MultiLanguageString& SectionName);
        virtual QString GetVisibilityConditionVariable();
        virtual void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable);
        virtual QString GetVisibilityConditionValue();
        virtual void SetVisibilityConditionValue(const QString& VisibilityConditionValue);
        virtual QList<IResourceModel*> GetDefaults();
        virtual void SetDefaults(QList<IResourceModel*>& Defaults);

        virtual QString GetAllowedTypes();
        virtual void SetAllowedTypes(const QString& Types);
        virtual bool GetIsAdvanced();
        virtual void SetIsAdvanced(bool IsAdvanced);

    signals:

    public slots:

    };
}

#endif // RESOURCEMODELABSTRACT_H
