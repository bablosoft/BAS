#ifndef IRESOURCEMODEL_H
#define IRESOURCEMODEL_H
#include "engine_global.h"
#include "multilanguagestring.h"
#include <QObject>
#include <QList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceModel : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceModel(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetTypeId() = 0;
        virtual QString GetName() = 0;
        virtual void SetName(const QString& Name) = 0;
        virtual MultiLanguageString GetDescription() = 0;
        virtual void SetDescription(const MultiLanguageString& Description) = 0;
        virtual bool GetVisibleByUser() = 0;
        virtual void SetVisibleByUser(bool visible) = 0;
        virtual bool GetEnabledByUser() = 0;
        virtual void SetEnabledByUser(bool enabled) = 0;
        virtual MultiLanguageString GetSectionName() = 0;
        virtual void SetSectionName(const MultiLanguageString& SectionName) = 0;
        virtual QString GetVisibilityConditionVariable() = 0;
        virtual void SetVisibilityConditionVariable(const QString& VisibilityConditionVariable) = 0;
        virtual QString GetVisibilityConditionValue() = 0;
        virtual void SetVisibilityConditionValue(const QString& VisibilityConditionValue) = 0;
        virtual QString GetAllowedTypes() = 0;
        virtual void SetAllowedTypes(const QString& Types) = 0;
        virtual QList<IResourceModel*> GetDefaults() = 0;
        virtual void SetDefaults(QList<IResourceModel*>& Defaults) = 0;
        virtual bool GetIsAdvanced() = 0;
        virtual void SetIsAdvanced(bool IsAdvanced) = 0;

    };
}

#endif // IRESOURCEMODEL_H

