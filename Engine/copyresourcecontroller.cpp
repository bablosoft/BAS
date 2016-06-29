#include "copyresourcecontroller.h"
#include "resourcemodelfixedinteger.h"
#include "resourcemodelfixedstring.h"
#include "resourcemodelurl.h"
#include "resourcemodeldirectory.h"
#include "resourcemodelfile.h"
#include "resourcemodelrandominteger.h"
#include "resourcemodelrandomstring.h"
#include "resourcemodelselect.h"
#include "resourcemodeldatabase.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    CopyResourceController::CopyResourceController(QObject *parent) :
        IResourceController(parent)
    {
        DefaultsExternal = 0;
    }

    void CopyResourceController::SetResources(IResources * ResourcesExternal)
    {
        this->ResourcesExternal = ResourcesExternal;
    }

    void CopyResourceController::SetDefaults(IResources * DefaultsExternal)
    {
        this->DefaultsExternal = DefaultsExternal;
    }

    bool CopyResourceController::IsDefaultChanged(const QString& Type,IResourceModel* ModelFrom, IResourceModel* ModelDefault)
    {
        bool res = false;
        if(Type == "FixedString")
        {
            ResourceModelFixedString *ModelDefaultActual = qobject_cast<ResourceModelFixedString*>(ModelDefault);
            ResourceModelFixedString *ModelFromActual = qobject_cast<ResourceModelFixedString*>(ModelFrom);


            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                res = true;
            }


        }else if(Type == "FixedInteger")
        {
            ResourceModelFixedInteger *ModelDefaultActual = qobject_cast<ResourceModelFixedInteger*>(ModelDefault);
            ResourceModelFixedInteger *ModelFromActual = qobject_cast<ResourceModelFixedInteger*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                res = true;
            }

        }else if(Type == "RandomString")
        {
            ResourceModelRandomString *ModelDefaultActual = qobject_cast<ResourceModelRandomString*>(ModelDefault);
            ResourceModelRandomString *ModelFromActual = qobject_cast<ResourceModelRandomString*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                res = true;
            }

        }else if(Type == "RandomInteger")
        {
            ResourceModelRandomInteger *ModelDefaultActual = qobject_cast<ResourceModelRandomInteger*>(ModelDefault);
            ResourceModelRandomInteger *ModelFromActual = qobject_cast<ResourceModelRandomInteger*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetMinUserValue() != ModelFromActual->GetMinUserValue()) || (ModelDefaultActual->GetMaxUserValue() != ModelFromActual->GetMaxUserValue()))
            {
                res = true;
            }

        }else if(Type == "LinesFromFile")
        {
            ResourceModelFile *ModelDefaultActual = qobject_cast<ResourceModelFile*>(ModelDefault);
            ResourceModelFile *ModelFromActual = qobject_cast<ResourceModelFile*>(ModelFrom);


            if(!ModelDefaultActual ||
                    (ModelDefaultActual->GetFilename() != ModelFromActual->GetFilename()) ||
                    (ModelDefaultActual->GetWrite() != ModelFromActual->GetWrite()) ||
                    (ModelDefaultActual->GetRead() != ModelFromActual->GetRead()) ||
                    (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()) ||
                    (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()) ||
                    (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()) ||
                    (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()) ||
                    (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()) ||
                    (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()) ||
                    (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()) ||
                    (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                res = true;
            }

        }else if(Type == "Database")
        {
            ResourceModelDatabase *ModelDefaultActual = qobject_cast<ResourceModelDatabase*>(ModelDefault);
            ResourceModelDatabase *ModelFromActual = qobject_cast<ResourceModelDatabase*>(ModelFrom);

            bool Equal = false;
            if(ModelDefaultActual)
            {
                QStringList Compare1 = ModelDefaultActual->GetGroupList();
                QStringList Compare2 = ModelFromActual->GetGroupList();
                Compare1.sort();
                Compare2.sort();
                Equal = Compare1 == Compare2;

            }

            if(!ModelDefaultActual ||
                    !Equal ||
                    (ModelDefaultActual->GetClean() != ModelFromActual->GetClean()) ||
                    (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()) ||
                    (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()) ||
                    (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()) ||
                    (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()) ||
                    (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()) ||
                    (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()) ||
                    (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()) ||
                    (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                res = true;
            }

        }else if(Type == "FilesFromDirectory")
        {
            ResourceModelDirectory *ModelDefaultActual = qobject_cast<ResourceModelDirectory*>(ModelDefault);
            ResourceModelDirectory *ModelFromActual = qobject_cast<ResourceModelDirectory*>(ModelFrom);

            if(!ModelDefaultActual ||
                    (ModelDefaultActual->GetDirectory() != ModelFromActual->GetDirectory()) ||
                    (ModelDefaultActual->GetWildcard() != ModelFromActual->GetWildcard()) ||
                    (ModelDefaultActual->GetClean() != ModelFromActual->GetClean()) ||
                    (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()) ||
                    (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()) ||
                    (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()) ||
                    (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()) ||
                    (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()) ||
                    (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()) ||
                    (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()) ||
                    (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                res = true;
            }


        }else if(Type == "LinesFromUrl")
        {
            ResourceModelUrl *ModelDefaultActual = qobject_cast<ResourceModelUrl*>(ModelDefault);
            ResourceModelUrl *ModelFromActual = qobject_cast<ResourceModelUrl*>(ModelFrom);

            if(!ModelDefaultActual ||
                    (ModelDefaultActual->GetUrl() != ModelFromActual->GetUrl()) ||
                    (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()) ||
                    (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()) ||
                    (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()) ||
                    (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()) ||
                    (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()) ||
                    (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()) ||
                    (ModelDefaultActual->GetCaptureArgument() != ModelFromActual->GetCaptureArgument()) ||
                    (ModelDefaultActual->GetCaptureMethod() != ModelFromActual->GetCaptureMethod()) ||
                    (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()) ||
                    (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                res = true;
            }

        }else if(Type == "Select")
        {
            ResourceModelSelect *ModelDefaultActual = qobject_cast<ResourceModelSelect*>(ModelDefault);
            ResourceModelSelect *ModelFromActual = qobject_cast<ResourceModelSelect*>(ModelFrom);

            if(!ModelDefaultActual)
            {
                res = true;
            }else
            {
                QStringList list_compare1 = ModelDefaultActual->GetValues();
                list_compare1.sort();
                QStringList list_compare2 = ModelFromActual->GetValues();
                list_compare2.sort();
                if(list_compare1.join(",") != list_compare2.join(","))
                {
                    res = true;
                }else
                {
                    QStringList compare1;
                    QStringList values1 = ModelDefaultActual->GetValues();
                    foreach(int index, ModelDefaultActual->GetSelected())
                    {
                        compare1.append(values1[index]);
                    }

                    QStringList compare2;
                    QStringList values2 = ModelFromActual->GetValues();
                    foreach(int index, ModelFromActual->GetSelected())
                    {
                        compare2.append(values2[index]);
                    }
                    compare1.sort();
                    compare2.sort();
                    if(compare1.join(",") != compare2.join(","))
                    {
                        res = true;
                    }
                }

            }



        }
        return res;
    }

    IResourceModel* CopyResourceController::CopyModelToActual(const QString& Type, IResourceModel* ModelTo, IResourceModel* ModelFrom, IResourceModel* ModelDefault, QObject* parent)
    {
        IResourceModel* res = 0;
        if(Type == "FixedString")
        {
            ResourceModelFixedString *ModelToActual = qobject_cast<ResourceModelFixedString*>(ModelTo);
            ResourceModelFixedString *ModelDefaultActual = qobject_cast<ResourceModelFixedString*>(ModelDefault);
            ResourceModelFixedString *ModelFromActual = qobject_cast<ResourceModelFixedString*>(ModelFrom);



            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                ModelToActual->SetValue(ModelFromActual->GetValue());
            }


        }else if(Type == "FixedInteger")
        {
            ResourceModelFixedInteger *ModelToActual = qobject_cast<ResourceModelFixedInteger*>(ModelTo);
            ResourceModelFixedInteger *ModelDefaultActual = qobject_cast<ResourceModelFixedInteger*>(ModelDefault);
            ResourceModelFixedInteger *ModelFromActual = qobject_cast<ResourceModelFixedInteger*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                ModelToActual->SetValue(ModelFromActual->GetValue());
            }

        }else if(Type == "RandomString")
        {
            ResourceModelRandomString *ModelToActual = qobject_cast<ResourceModelRandomString*>(ModelTo);
            ResourceModelRandomString *ModelDefaultActual = qobject_cast<ResourceModelRandomString*>(ModelDefault);
            ResourceModelRandomString *ModelFromActual = qobject_cast<ResourceModelRandomString*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetValue() != ModelFromActual->GetValue()))
            {
                ModelToActual->SetValue(ModelFromActual->GetValue());
            }

        }else if(Type == "RandomInteger")
        {
            ResourceModelRandomInteger *ModelToActual = qobject_cast<ResourceModelRandomInteger*>(ModelTo);
            ResourceModelRandomInteger *ModelDefaultActual = qobject_cast<ResourceModelRandomInteger*>(ModelDefault);
            ResourceModelRandomInteger *ModelFromActual = qobject_cast<ResourceModelRandomInteger*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetMinUserValue() != ModelFromActual->GetMinUserValue()))
            {
                ModelToActual->SetMinUserValue(ModelFromActual->GetMinUserValue());
            }

            if(!ModelDefaultActual || (ModelDefaultActual->GetMaxUserValue() != ModelFromActual->GetMaxUserValue()))
            {
                ModelToActual->SetMaxUserValue(ModelFromActual->GetMaxUserValue());
            }

        }else if(Type == "LinesFromFile")
        {
            ResourceModelFile *ModelToActual = qobject_cast<ResourceModelFile*>(ModelTo);
            ResourceModelFile *ModelDefaultActual = qobject_cast<ResourceModelFile*>(ModelDefault);
            ResourceModelFile *ModelFromActual = qobject_cast<ResourceModelFile*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetFilename() != ModelFromActual->GetFilename()))
            {
                ModelToActual->SetFilename(ModelFromActual->GetFilename());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetRead() != ModelFromActual->GetRead()))
            {
                ModelToActual->SetRead(ModelFromActual->GetRead());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetWrite() != ModelFromActual->GetWrite()))
            {
                ModelToActual->SetWrite(ModelFromActual->GetWrite());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()))
            {
                ModelToActual->SetMix(ModelFromActual->GetMix());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()))
            {
                ModelToActual->SetSuccessAttempts(ModelFromActual->GetSuccessAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()))
            {
                ModelToActual->SetFailAttempts(ModelFromActual->GetFailAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()))
            {
                ModelToActual->SetNumberSimultaneousUse(ModelFromActual->GetNumberSimultaneousUse());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()))
            {
                ModelToActual->SetIntervalBetweenUsage(ModelFromActual->GetIntervalBetweenUsage());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()))
            {
                ModelToActual->SetLoadInterval(ModelFromActual->GetLoadInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()))
            {
                ModelToActual->SetRenewInterval(ModelFromActual->GetRenewInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                ModelToActual->SetGreedy(ModelFromActual->GetGreedy());
            }


        }else if(Type == "Database")
        {

            ResourceModelDatabase *ModelToActual = qobject_cast<ResourceModelDatabase*>(ModelTo);
            ResourceModelDatabase *ModelDefaultActual = qobject_cast<ResourceModelDatabase*>(ModelDefault);
            ResourceModelDatabase *ModelFromActual = qobject_cast<ResourceModelDatabase*>(ModelFrom);

            bool Equal = false;
            if(ModelDefaultActual)
            {
                QStringList Compare1 = ModelDefaultActual->GetGroupList();
                QStringList Compare2 = ModelFromActual->GetGroupList();
                Compare1.sort();
                Compare2.sort();
                Equal = Compare1 == Compare2;

            }

            if(!ModelDefaultActual || !Equal)
            {
                ModelToActual->SetGroupList(ModelFromActual->GetGroupList());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetClean() != ModelFromActual->GetClean()))
            {
                ModelToActual->SetClean(ModelFromActual->GetClean());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()))
            {
                ModelToActual->SetMix(ModelFromActual->GetMix());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()))
            {
                ModelToActual->SetSuccessAttempts(ModelFromActual->GetSuccessAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()))
            {
                ModelToActual->SetFailAttempts(ModelFromActual->GetFailAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()))
            {
                ModelToActual->SetNumberSimultaneousUse(ModelFromActual->GetNumberSimultaneousUse());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()))
            {
                ModelToActual->SetIntervalBetweenUsage(ModelFromActual->GetIntervalBetweenUsage());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()))
            {
                ModelToActual->SetLoadInterval(ModelFromActual->GetLoadInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()))
            {
                ModelToActual->SetRenewInterval(ModelFromActual->GetRenewInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                ModelToActual->SetGreedy(ModelFromActual->GetGreedy());
            }

        }else if(Type == "FilesFromDirectory")
        {
            ResourceModelDirectory *ModelToActual = qobject_cast<ResourceModelDirectory*>(ModelTo);
            ResourceModelDirectory *ModelDefaultActual = qobject_cast<ResourceModelDirectory*>(ModelDefault);
            ResourceModelDirectory *ModelFromActual = qobject_cast<ResourceModelDirectory*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetDirectory() != ModelFromActual->GetDirectory()))
            {
                ModelToActual->SetDirectory(ModelFromActual->GetDirectory());
            }

            if(!ModelDefaultActual || (ModelDefaultActual->GetWildcard() != ModelFromActual->GetWildcard()))
            {
                ModelToActual->SetWildcard(ModelFromActual->GetWildcard());
            }

            if(!ModelDefaultActual || (ModelDefaultActual->GetClean() != ModelFromActual->GetClean()))
            {
                ModelToActual->SetClean(ModelFromActual->GetClean());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()))
            {
                ModelToActual->SetMix(ModelFromActual->GetMix());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()))
            {
                ModelToActual->SetSuccessAttempts(ModelFromActual->GetSuccessAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()))
            {
                ModelToActual->SetFailAttempts(ModelFromActual->GetFailAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()))
            {
                ModelToActual->SetNumberSimultaneousUse(ModelFromActual->GetNumberSimultaneousUse());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()))
            {
                ModelToActual->SetIntervalBetweenUsage(ModelFromActual->GetIntervalBetweenUsage());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()))
            {
                ModelToActual->SetLoadInterval(ModelFromActual->GetLoadInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()))
            {
                ModelToActual->SetRenewInterval(ModelFromActual->GetRenewInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                ModelToActual->SetGreedy(ModelFromActual->GetGreedy());
            }



        }else if(Type == "LinesFromUrl")
        {
            ResourceModelUrl *ModelToActual = qobject_cast<ResourceModelUrl*>(ModelTo);
            ResourceModelUrl *ModelDefaultActual = qobject_cast<ResourceModelUrl*>(ModelDefault);
            ResourceModelUrl *ModelFromActual = qobject_cast<ResourceModelUrl*>(ModelFrom);

            if(!ModelDefaultActual || (ModelDefaultActual->GetUrl() != ModelFromActual->GetUrl()))
            {
                ModelToActual->SetUrl(ModelFromActual->GetUrl());
            }

            if(!ModelDefaultActual || (ModelDefaultActual->GetMix() != ModelFromActual->GetMix()))
            {
                ModelToActual->SetMix(ModelFromActual->GetMix());
            }

            if(!ModelDefaultActual || (ModelDefaultActual->GetSuccessAttempts() != ModelFromActual->GetSuccessAttempts()))
            {
                ModelToActual->SetSuccessAttempts(ModelFromActual->GetSuccessAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetFailAttempts() != ModelFromActual->GetFailAttempts()))
            {
                ModelToActual->SetFailAttempts(ModelFromActual->GetFailAttempts());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetNumberSimultaneousUse() != ModelFromActual->GetNumberSimultaneousUse()))
            {
                ModelToActual->SetNumberSimultaneousUse(ModelFromActual->GetNumberSimultaneousUse());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetIntervalBetweenUsage() != ModelFromActual->GetIntervalBetweenUsage()))
            {
                ModelToActual->SetIntervalBetweenUsage(ModelFromActual->GetIntervalBetweenUsage());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetLoadInterval() != ModelFromActual->GetLoadInterval()))
            {
                ModelToActual->SetLoadInterval(ModelFromActual->GetLoadInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetRenewInterval() != ModelFromActual->GetRenewInterval()))
            {
                ModelToActual->SetRenewInterval(ModelFromActual->GetRenewInterval());
            }
            if(!ModelDefaultActual || (ModelDefaultActual->GetGreedy() != ModelFromActual->GetGreedy()))
            {
                ModelToActual->SetGreedy(ModelFromActual->GetGreedy());
            }



        }else if(Type == "Select")
        {
            ResourceModelSelect *ModelToActual = qobject_cast<ResourceModelSelect*>(ModelTo);
            ResourceModelSelect *ModelDefaultActual = qobject_cast<ResourceModelSelect*>(ModelDefault);
            ResourceModelSelect *ModelFromActual = qobject_cast<ResourceModelSelect*>(ModelFrom);

            bool SetToUserSelected = false;
            if(ModelDefaultActual)
            {

                QStringList list_compare1 = ModelDefaultActual->GetValues();
                QStringList list_compare2 = ModelFromActual->GetValues();

                QStringList compare1;
                foreach(int index, ModelDefaultActual->GetSelected())
                {
                    compare1.append(list_compare1[index]);
                }

                QStringList compare2;
                foreach(int index, ModelFromActual->GetSelected())
                {
                    compare2.append(list_compare2[index]);
                }

                compare1.sort();
                compare2.sort();
                if(compare1.join(",") != compare2.join(","))
                {
                    SetToUserSelected = true;
                }

            }else
            {
                SetToUserSelected = true;
            }

            if(SetToUserSelected)
            {
                QList<int> SelectedResult;
                QList<int> SelectedCandidates = ModelFromActual->GetSelected();
                foreach(int index, SelectedCandidates)
                {
                    QString IndexString = ModelFromActual->GetValues().at(index);
                    if(ModelToActual->GetValues().contains(IndexString))
                    {
                        SelectedResult.append(ModelToActual->GetValues().indexOf(IndexString));
                    }
                }
                ModelToActual->SetSelected(SelectedResult);

            }



        }
        return res;
    }

    void CopyResourceController::FromViewToModel(IResources * resources, bool Clear)
    {
        QList<IResourceModel *> *ModelsTo = resources->GetModelList();
        QList<IResourceModel *> *ModelsFrom = ResourcesExternal->GetModelList();
        QList<IResourceModel *> *ModelsDefault = 0;
        if(DefaultsExternal)
        {
            ModelsDefault = DefaultsExternal->GetModelList();
        }

        foreach(IResourceModel * ModelFrom,*ModelsFrom)
        {

            IResourceModel * ModelTo = 0;
            IResourceModel * ModelDefault = 0;


            //Find ModelTo and ModelDefault
            foreach(IResourceModel * ModelToTest,*ModelsTo)
            {
                if(ModelFrom->GetName() == ModelToTest->GetName())
                {
                    ModelTo = ModelToTest;
                    break;
                }
            }
            if(!ModelTo)
            {
                continue;
            }




            if(ModelsDefault)
            {
                foreach(IResourceModel * ModelDefaultTest,*ModelsDefault)
                {
                    if(ModelFrom->GetName() == ModelDefaultTest->GetName())
                    {
                        ModelDefault = ModelDefaultTest;
                        break;
                    }
                }
            }

            //Find all subclasses of 3 current models
            QList<IResourceModel *> AllModelsFrom;
            AllModelsFrom.append(ModelFrom);
            AllModelsFrom.append(ModelFrom->GetDefaults());

            QList<IResourceModel *> AllModelsTo;
            AllModelsTo.append(ModelTo);
            AllModelsTo.append(ModelTo->GetDefaults());

            QList<IResourceModel *> AllModelsDefault;
            if(ModelDefault)
            {
                AllModelsDefault.append(ModelDefault);
                AllModelsDefault.append(ModelDefault->GetDefaults());
            }


            //Determine target type and change ModelTo if needed
            QString TargetType = ModelFrom->GetTypeId();

            if(ModelDefault && ModelDefault->GetTypeId() == ModelFrom->GetTypeId() && !IsDefaultChanged(ModelDefault->GetTypeId(),ModelFrom,ModelDefault))
            {

                TargetType = ModelTo->GetTypeId();
            }
            //else
            {
                IResourceModel * ModelToNew = 0;
                foreach(IResourceModel * ModelToTest,AllModelsTo)
                {
                    if(TargetType == ModelToTest->GetTypeId())
                    {
                        ModelToNew = ModelToTest;
                        QList<IResourceModel *>def;
                        ModelTo->SetDefaults(def);

                        break;
                    }
                }
                if(!ModelToNew)
                {
                    TargetType = ModelTo->GetTypeId();
                }
                else
                {
                    QList<IResourceModel *> ModelsToNewDefault;
                    foreach(IResourceModel * ModelToTest,AllModelsTo)
                    {
                        if(ModelToTest != ModelToNew)
                        {
                            ModelsToNewDefault.append(ModelToTest);
                        }
                    }
                    ModelToNew->SetDefaults(ModelsToNewDefault);

                    int index = 0;
                    foreach(IResourceModel * ModelToTest,*ModelsTo)
                    {
                        if(ModelTo == ModelToTest)
                        {
                            break;
                        }
                        index++;
                    }
                    ModelTo = ModelToNew;
                    ModelsTo->replace(index,ModelTo);
                }
            }
            //Copy user selected settings to developer defined
            foreach(IResourceModel * CurrentModelFrom,AllModelsFrom)
            {

                IResourceModel * CurrentModelTo = 0;
                IResourceModel * CurrentModelDefault = 0;

                foreach(IResourceModel * ModelToTest,AllModelsTo)
                {
                    if(CurrentModelFrom->GetTypeId() == ModelToTest->GetTypeId())
                    {
                        CurrentModelTo = ModelToTest;
                        break;
                    }
                }
                if(!CurrentModelTo)
                {
                    continue;
                }
                foreach(IResourceModel * ModelDefaultTest,AllModelsDefault)
                {
                    if(CurrentModelFrom->GetTypeId() == ModelDefaultTest->GetTypeId())
                    {
                        CurrentModelDefault = ModelDefaultTest;
                    }
                }
                CopyModelToActual(CurrentModelFrom->GetTypeId(), CurrentModelTo, CurrentModelFrom, CurrentModelDefault, resources);
            }
        }
    }
    void CopyResourceController::FromModelToView(IResources * resources, bool Clear)
    {

    }
}

