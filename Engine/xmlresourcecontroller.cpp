#include "xmlresourcecontroller.h"
#include <QFile>
#include <QHash>

#include "resourcemodelfixedstring.h"
#include "resourcemodelfixedinteger.h"
#include "resourcemodelrandominteger.h"
#include "resourcemodelrandomstring.h"
#include "resourcemodelfile.h"
#include "resourcemodeldirectory.h"
#include "resourcemodelurl.h"
#include "resourcemodeldatabase.h"
#include "resourcemodelselect.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    XmlResourceController::XmlResourceController(QObject *parent) :
        IResourceController(parent)
    {
        ConnectionIsRemote = false;
        HideBrowsers = false;
    }

    void XmlResourceController::SetAvailableLanguages(const QString & AvailableLanguages)
    {
        this->AvailableLanguages = AvailableLanguages;
    }

    QString XmlResourceController::GetAvailableLanguages()
    {
        return AvailableLanguages;
    }

    void XmlResourceController::SetOutputTitle1(const MultiLanguageString& OutputTitle1)
    {
        this->OutputTitle1 = OutputTitle1;
    }
    void XmlResourceController::SetOutputTitle2(const MultiLanguageString& OutputTitle2)
    {
        this->OutputTitle2 = OutputTitle2;
    }
    void XmlResourceController::SetOutputTitle3(const MultiLanguageString& OutputTitle3)
    {
        this->OutputTitle3 = OutputTitle3;
    }
    void XmlResourceController::SetOutputTitle4(const MultiLanguageString& OutputTitle4)
    {
        this->OutputTitle4 = OutputTitle4;
    }
    void XmlResourceController::SetOutputTitle5(const MultiLanguageString& OutputTitle5)
    {
        this->OutputTitle5 = OutputTitle5;
    }
    void XmlResourceController::SetOutputTitle6(const MultiLanguageString& OutputTitle6)
    {
        this->OutputTitle6 = OutputTitle6;
    }
    void XmlResourceController::SetOutputTitle7(const MultiLanguageString& OutputTitle7)
    {
        this->OutputTitle7 = OutputTitle7;
    }
    void XmlResourceController::SetOutputTitle8(const MultiLanguageString& OutputTitle8)
    {
        this->OutputTitle8 = OutputTitle8;
    }
    void XmlResourceController::SetOutputTitle9(const MultiLanguageString& OutputTitle9)
    {
        this->OutputTitle9 = OutputTitle9;
    }
    void XmlResourceController::SetOutputVisible1(bool OutputVisible1)
    {
        this->OutputVisible1 = OutputVisible1;
    }
    void XmlResourceController::SetOutputVisible2(bool OutputVisible2)
    {
        this->OutputVisible2 = OutputVisible2;
    }
    void XmlResourceController::SetOutputVisible3(bool OutputVisible3)
    {
        this->OutputVisible3 = OutputVisible3;
    }
    void XmlResourceController::SetOutputVisible4(bool OutputVisible4)
    {
        this->OutputVisible4 = OutputVisible4;
    }
    void XmlResourceController::SetOutputVisible5(bool OutputVisible5)
    {
        this->OutputVisible5 = OutputVisible5;
    }
    void XmlResourceController::SetOutputVisible6(bool OutputVisible6)
    {
        this->OutputVisible6 = OutputVisible6;
    }
    void XmlResourceController::SetOutputVisible7(bool OutputVisible7)
    {
        this->OutputVisible7 = OutputVisible7;
    }
    void XmlResourceController::SetOutputVisible8(bool OutputVisible8)
    {
        this->OutputVisible8 = OutputVisible8;
    }
    void XmlResourceController::SetOutputVisible9(bool OutputVisible9)
    {
        this->OutputVisible9 = OutputVisible9;
    }

    void XmlResourceController::SetScriptName(const QString & Name)
    {
        this->ScriptName = Name;
    }

    void XmlResourceController::SetHideBrowsers(bool HideBrowsers)
    {
        this->HideBrowsers = HideBrowsers;
    }

    bool XmlResourceController::GetHideBrowsers()
    {
        return HideBrowsers;
    }

    MultiLanguageString XmlResourceController::GetOutputTitle1()
    {
        return OutputTitle1;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle2()
    {
        return OutputTitle2;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle3()
    {
        return OutputTitle3;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle4()
    {
        return OutputTitle4;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle5()
    {
        return OutputTitle5;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle6()
    {
        return OutputTitle6;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle7()
    {
        return OutputTitle7;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle8()
    {
        return OutputTitle8;
    }
    MultiLanguageString XmlResourceController::GetOutputTitle9()
    {
        return OutputTitle9;
    }
    bool XmlResourceController::GetOutputVisible1()
    {
        return OutputVisible1;
    }
    bool XmlResourceController::GetOutputVisible2()
    {
        return OutputVisible2;
    }
    bool XmlResourceController::GetOutputVisible3()
    {
        return OutputVisible3;
    }
    bool XmlResourceController::GetOutputVisible4()
    {
        return OutputVisible4;
    }
    bool XmlResourceController::GetOutputVisible5()
    {
        return OutputVisible5;
    }
    bool XmlResourceController::GetOutputVisible6()
    {
        return OutputVisible6;
    }
    bool XmlResourceController::GetOutputVisible7()
    {
        return OutputVisible7;
    }
    bool XmlResourceController::GetOutputVisible8()
    {
        return OutputVisible8;
    }
    bool XmlResourceController::GetOutputVisible9()
    {
        return OutputVisible9;
    }


    void XmlResourceController::SetScriptVersion(const QString & Version)
    {
        this->ScriptVersion = Version;
    }
    QString XmlResourceController::GetScriptName()
    {
        return ScriptName;
    }
    QString XmlResourceController::GetScriptVersion()
    {
        return ScriptVersion;
    }

    void XmlResourceController::SetScript(const QString & Script)
    {
        this->Script = Script;

    }

    void XmlResourceController::SetDatabaseId(const QString & DatabaseId)
    {
        this->DatabaseId = DatabaseId;

    }

    void XmlResourceController::SetSchema(const QString & Schema)
    {
        this->Schema = Schema;

    }

    void XmlResourceController::SetConnectionIsRemote(bool ConnectionIsRemote)
    {
        this->ConnectionIsRemote = ConnectionIsRemote;
    }
    void XmlResourceController::SetConnectionServer(const QString & ConnectionServer)
    {
        this->ConnectionServer = ConnectionServer;
    }
    void XmlResourceController::SetConnectionPort(const QString & ConnectionPort)
    {
        this->ConnectionPort = ConnectionPort;
    }
    void XmlResourceController::SetConnectionLogin(const QString & ConnectionLogin)
    {
        this->ConnectionLogin = ConnectionLogin;
    }
    void XmlResourceController::SetConnectionPassword(const QString & ConnectionPassword)
    {
        this->ConnectionPassword = ConnectionPassword;

    }

    void XmlResourceController::SetFileName(const QString & FileName)
    {
        this->FileName = FileName;
    }

    void XmlResourceController::SetFileContent(const QString & FileContent)
    {
        this->FileContent = FileContent;
    }

    void XmlResourceController::SetEngineVersion(const QString & EngineVersion)
    {
        this->EngineVersion = EngineVersion;
    }
    void XmlResourceController::SetChromeCommandLine(const QString & ChromeCommandLine)
    {
        this->ChromeCommandLine = ChromeCommandLine;
    }
    void XmlResourceController::SetSettingsWorker(const QString & SettingsWorker)
    {
        this->SettingsWorker = SettingsWorker;
    }
    void XmlResourceController::SetModulesMetaJson(const QString & ModulesMetaJson)
    {
        this->ModulesMetaJson = ModulesMetaJson;
    }


    QString XmlResourceController::GetFileContent()
    {
        return FileContent;
    }

    QString XmlResourceController::GetEngineVersion()
    {
        return EngineVersion;
    }
    QString XmlResourceController::GetChromeCommandLine()
    {
        return ChromeCommandLine;
    }
    QString XmlResourceController::GetSettingsWorker()
    {
        return SettingsWorker;
    }
    QString XmlResourceController::GetModulesMetaJson()
    {
        return ModulesMetaJson;
    }

    QString XmlResourceController::GetScript()
    {
        return Script;
    }

    QString XmlResourceController::GetDatabaseId()
    {
        return DatabaseId;
    }

    QString XmlResourceController::GetSchema()
    {
        return Schema;
    }
    bool XmlResourceController::GetConnectionIsRemote()
    {
        return ConnectionIsRemote;
    }
    QString XmlResourceController::GetConnectionServer()
    {
        return ConnectionServer;
    }

    QString XmlResourceController::GetConnectionPort()
    {
        return ConnectionPort;
    }
    QString XmlResourceController::GetConnectionLogin()
    {
        return ConnectionLogin;
    }
    QString XmlResourceController::GetConnectionPassword()
    {
        return ConnectionPassword;
    }

    QString XmlResourceController::GetFileName()
    {
        return FileName;
    }

    bool XmlResourceController::GetResult()
    {
        return Result;
    }

    QString XmlResourceController::GetErrorString()
    {
        return ErrorString;
    }


    IResourceModel* XmlResourceController::ReadModel(QHash<QString,QString>& attr)
    {
        if(attr["Type"] == "FixedString")
        {
            ResourceModelFixedString *m = new ResourceModelFixedString();
            m->SetName(attr["Name"]);

            m->SetValue(attr["Value"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());
            m->SetNotEmpty(attr["NotEmpty"].toInt());
            return m;
        }else if(attr["Type"] == "FixedInteger")
        {
            ResourceModelFixedInteger *m = new ResourceModelFixedInteger();
            m->SetName(attr["Name"]);
            m->SetValue(attr["Value"].toInt());
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());
            m->SetMinValue(attr["MinValue"].toInt());
            m->SetMaxValue(attr["MaxValue"].toInt());
            return m;
        } else if(attr["Type"] == "RandomString")
        {
            ResourceModelRandomString * m = new ResourceModelRandomString();
            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());
            m->SetValue(attr["Value"]);

            return m;
        }else if(attr["Type"] == "RandomInteger")
        {
            ResourceModelRandomInteger * m = new ResourceModelRandomInteger();
            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());
            m->SetMinDesignValue(attr["MinDesignValue"].toInt());
            m->SetMaxDesignValue(attr["MaxDesignValue"].toInt());
            m->SetMinUserValue(attr["MinUserValue"].toInt());
            m->SetMaxUserValue(attr["MaxUserValue"].toInt());
            return m;
        }else if(attr["Type"] == "LinesFromFile")
        {
            ResourceModelFile * m = new ResourceModelFile();

            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());

            m->SetFilename(attr["Filename"]);
            m->SetWrite(attr["Clean"].toInt());
            if(!attr.contains("Read"))
                m->SetRead(1);
            else
                m->SetRead(attr["Read"].toInt());

            m->SetMix(attr["Mix"].toInt());
            m->SetSuccessAttempts(attr["MaxSuccess"].toInt());
            m->SetFailAttempts(attr["MaxFail"].toInt());
            m->SetNumberSimultaneousUse(attr["MaxSimultaneous"].toInt());
            m->SetIntervalBetweenUsage(attr["Interval"].toInt());
            m->SetLoadInterval(attr["ReloadInterval"].toInt());
            m->SetRenewInterval(attr["RenewInterval"].toInt());
            m->SetGreedy(attr["Greedy"].toInt());
            return m;
        }else if(attr["Type"] == "Database")
        {
            ResourceModelDatabase * m = new ResourceModelDatabase();

            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());

            m->SetGroupList(attr["GroupList"].split(","));
            m->SetTableId(attr["TableId"].toInt());
            QList<int> ColumnIds;
            foreach(QString ColumnString, attr["ColumnIds"].split(","))
            {
                ColumnIds.append(ColumnString.toInt());
            }
            m->SetColumnIds(ColumnIds);

            m->SetClean(attr["Clean"].toInt());
            m->SetMix(attr["Mix"].toInt());
            m->SetSuccessAttempts(attr["MaxSuccess"].toInt());
            m->SetFailAttempts(attr["MaxFail"].toInt());
            m->SetNumberSimultaneousUse(attr["MaxSimultaneous"].toInt());
            m->SetIntervalBetweenUsage(attr["Interval"].toInt());
            m->SetLoadInterval(attr["ReloadInterval"].toInt());
            m->SetRenewInterval(attr["RenewInterval"].toInt());
            m->SetGreedy(attr["Greedy"].toInt());
            return m;
        }else if(attr["Type"] == "FilesFromDirectory")
        {
            ResourceModelDirectory * m = new ResourceModelDirectory();

            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());

            m->SetDirectory(attr["FilesFromDirectory"]);
            m->SetWildcard(attr["Wildcard"]);
            m->SetClean(attr["Clean"].toInt());
            m->SetMix(attr["Mix"].toInt());
            m->SetSuccessAttempts(attr["MaxSuccess"].toInt());
            m->SetFailAttempts(attr["MaxFail"].toInt());
            m->SetNumberSimultaneousUse(attr["MaxSimultaneous"].toInt());
            m->SetIntervalBetweenUsage(attr["Interval"].toInt());
            m->SetLoadInterval(attr["ReloadInterval"].toInt());
            m->SetRenewInterval(attr["RenewInterval"].toInt());
            m->SetGreedy(attr["Greedy"].toInt());
            return m;

        }else if(attr["Type"] == "LinesFromUrl")
        {
            ResourceModelUrl * m = new ResourceModelUrl();

            m->SetName(attr["Name"]);
            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());

            m->SetUrl(attr["LinesFromUrl"]);
            m->SetMix(attr["Mix"].toInt());
            m->SetSuccessAttempts(attr["MaxSuccess"].toInt());
            m->SetFailAttempts(attr["MaxFail"].toInt());
            m->SetNumberSimultaneousUse(attr["MaxSimultaneous"].toInt());
            m->SetIntervalBetweenUsage(attr["Interval"].toInt());
            m->SetLoadInterval(attr["ReloadInterval"].toInt());
            m->SetRenewInterval(attr["RenewInterval"].toInt());
            m->SetCaptureMethod(attr["CaptureMethod"].toInt());
            m->SetCaptureArgument(attr["CaptureArgument"]);
            m->SetGreedy(attr["Greedy"].toInt());
            return m;

        }else if(attr["Type"] == "Select")
        {
            ResourceModelSelect * m = new ResourceModelSelect();

            m->SetName(attr["Name"]);

            m->SetVisibilityConditionValue(attr["VisibilityConditionValue"]);
            m->SetVisibilityConditionVariable(attr["VisibilityConditionVariable"]);
            m->SetIsAdvanced(attr["IsAdvanced"].toInt());

            m->SetVisibleByUser(attr["Visible"].toInt());
            m->SetAllowedTypes(attr["AllowedTypes"]);
            m->SetEnabledByUser(attr["Enabled"].toInt());

            m->SetValues(attr["Values"].split(QRegExp("[\r\n]"),QString::SkipEmptyParts));


            QList<int> selected;
            foreach(QString s,attr["Selected"].split(","))
            {
                if(!s.isEmpty())
                selected.append(s.toInt());
            }


            m->SetSelected(selected);
            m->SetSelectType((ResourceModelSelect::SelectType)attr["SelectType"].toInt());
            return m;
        }
        return 0;
    }

    void XmlResourceController::FromViewToModel(IResources * resources, bool Clear)
    {
        int len = resources->GetModelList()->size();
        for(int i = 0;i<len;i++)
        {
            IResourceModel* w = resources->GetModelList()->at(i);
            delete w;
        }
        if(Clear)
            resources->GetModelList()->clear();

        Result = false;
        QXmlStreamReader xmlReader;
        QObject FileParent;
        if(!FileName.isEmpty())
        {
            QFile *file = new QFile(FileName);
            file->setParent(&FileParent);
            if (!file->open(QIODevice::ReadOnly| QIODevice::Text))
            {
                ErrorString = QString("Can't read file %1").arg(FileName);
                return;
            }

            xmlReader.setDevice(file);

        }else if(!FileContent.isEmpty())
        {
            xmlReader.addData(FileContent);
        }

        QHash<QString,QString> attr, attrDefault;

        MultiLanguageString Description,SectionName,DescriptionDefault,SectionNameDefault;
        bool is_inside_model = false;
        bool is_inside_default = false;
        QList<IResourceModel*> Defaults;
        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();


            if(xmlReader.name() == "DatabaseId" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                DatabaseId = xmlReader.text().toString();
            }else if(xmlReader.name() == "Script" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Script = xmlReader.text().toString();
            }else if(xmlReader.name() == "Schema" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                Schema = xmlReader.text().toString();
            }else if(xmlReader.name() == "ConnectionIsRemote" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ConnectionIsRemote = xmlReader.text().toString() == "true";
            }else if(xmlReader.name() == "ConnectionServer" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ConnectionServer = xmlReader.text().toString();
            }else if(xmlReader.name() == "ConnectionPort" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ConnectionPort = xmlReader.text().toString();
            }else if(xmlReader.name() == "ConnectionLogin" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ConnectionLogin = xmlReader.text().toString();
            }else if(xmlReader.name() == "ConnectionPassword" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ConnectionPassword = xmlReader.text().toString();
            }else if(xmlReader.name() == "ScriptName" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ScriptName = xmlReader.text().toString();
            }else if(xmlReader.name() == "HideBrowsers" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                HideBrowsers = xmlReader.text().toString() == "true";
            }else if(xmlReader.name() == "ScriptVersion" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ScriptVersion = xmlReader.text().toString();
            }else if(xmlReader.name() == "EngineVersion" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                EngineVersion = xmlReader.text().toString();
            }else if(xmlReader.name() == "ChromeCommandLine" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ChromeCommandLine = xmlReader.text().toString();
            }else if(xmlReader.name() == "SettingsWorker" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                SettingsWorker = xmlReader.text().toString();
            }else if(xmlReader.name() == "ModulesMetaJson" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                ModulesMetaJson = xmlReader.text().toString();
            }else if(xmlReader.name() == "AvailableLanguages" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                AvailableLanguages = xmlReader.text().toString();
            }else if(xmlReader.name() == "OutputTitle1" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle1.Clear();
                OutputTitle1.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle2" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle2.Clear();
                OutputTitle2.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle3" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle3.Clear();
                OutputTitle3.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle4" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle4.Clear();
                OutputTitle4.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle5" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle5.Clear();
                OutputTitle5.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle6" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle6.Clear();
                OutputTitle6.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle7" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle7.Clear();
                OutputTitle7.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle8" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle8.Clear();
                OutputTitle8.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputTitle9" && token == QXmlStreamReader::StartElement)
            {
                OutputTitle9.Clear();
                OutputTitle9.ParseXml(&xmlReader);
            }else if(xmlReader.name() == "OutputVisible1" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible1 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible2" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible2 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible3" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible3 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible4" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible4 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible5" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible5 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible6" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible6 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible7" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible7 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible8" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible8 = xmlReader.text().toString().toInt();
            }else if(xmlReader.name() == "OutputVisible9" && token == QXmlStreamReader::StartElement)
            {
                xmlReader.readNext();
                OutputVisible9 = xmlReader.text().toString().toInt();
            }
            else if((xmlReader.name() == "Model" && token == QXmlStreamReader::EndElement))
            {
                is_inside_model = false;
            }else  if((xmlReader.name() == "Model" && token == QXmlStreamReader::StartElement) || (xmlReader.name() == "ModelList" && token == QXmlStreamReader::EndElement))
            {
                is_inside_model = true;
                IResourceModel* m = ReadModel(attr);
                if(m)
                {
                    m->SetDescription(Description);
                    m->SetSectionName(SectionName);
                    m->setParent(resources);
                    m->SetDefaults(Defaults);
                    Defaults.clear();
                    resources->GetModelList()->append(m);
                }
                attr.clear();

            }else if((xmlReader.name() == "Default" && token == QXmlStreamReader::EndElement))
            {
                is_inside_default = false;
            }else  if((xmlReader.name() == "Default" && token == QXmlStreamReader::StartElement) || (xmlReader.name() == "Defaults" && token == QXmlStreamReader::EndElement))
            {
                is_inside_default = true;
                IResourceModel* m = ReadModel(attrDefault);
                if(m)
                {
                    m->SetDescription(DescriptionDefault);
                    m->SetSectionName(SectionNameDefault);
                    m->setParent(resources);
                    Defaults.append(m);
                }
                attrDefault.clear();

            }


            else if(token == QXmlStreamReader::StartElement && is_inside_model )
            {
                QString name = xmlReader.name().toString();
                if(name=="Description")
                {
                    Description.Clear();
                    Description.ParseXml(&xmlReader);
                }else if(name=="SectionName")
                {
                    SectionName.Clear();
                    SectionName.ParseXml(&xmlReader);
                }else
                {
                    xmlReader.readNext();
                    QString value = xmlReader.text().toString();
                    attr[name] = value;
                }
            }
            else if(token == QXmlStreamReader::StartElement && is_inside_default)
            {
                QString name = xmlReader.name().toString();
                if(name=="Description")
                {
                    DescriptionDefault.Clear();
                    DescriptionDefault.ParseXml(&xmlReader);
                }else if(name=="SectionName")
                {
                    SectionNameDefault.Clear();
                    SectionNameDefault.ParseXml(&xmlReader);
                }else
                {
                    xmlReader.readNext();
                    QString value = xmlReader.text().toString();
                    attrDefault[name] = value;
                }
            }



        }
        if (xmlReader.hasError())
        {
            ErrorString = xmlReader.errorString();
            return;
        }
        Result = true;
    }

    void XmlResourceController::WriteModel(QXmlStreamWriter &xmlWriter,IResourceModel *m)
    {

        xmlWriter.writeTextElement("Name",m->GetName());
        xmlWriter.writeStartElement("Description");
            m->GetDescription().WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("SectionName");
            m->GetSectionName().WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();

        xmlWriter.writeTextElement("VisibilityConditionValue",m->GetVisibilityConditionValue());
        xmlWriter.writeTextElement("VisibilityConditionVariable",m->GetVisibilityConditionVariable());
        xmlWriter.writeTextElement("Type",m->GetTypeId());
        xmlWriter.writeTextElement("IsAdvanced",QString::number(m->GetIsAdvanced()));
        xmlWriter.writeTextElement("Visible",QString::number(m->GetVisibleByUser()));
        xmlWriter.writeTextElement("Enabled",QString::number(m->GetEnabledByUser()));
        xmlWriter.writeTextElement("AllowedTypes",m->GetAllowedTypes());
        if(m->GetTypeId() == "FixedString")
        {
            ResourceModelFixedString * r = qobject_cast<ResourceModelFixedString *>(m);
            xmlWriter.writeTextElement("Value",r->GetValue());
            xmlWriter.writeTextElement("NotEmpty",QString::number((int)(r->GetNotEmpty())));

        }else if(m->GetTypeId() == "FixedInteger")
        {
            ResourceModelFixedInteger * r = qobject_cast<ResourceModelFixedInteger *>(m);
            xmlWriter.writeTextElement("Value",QString::number(r->GetValue()));
            xmlWriter.writeTextElement("MinValue",QString::number(r->GetMinValue()));
            xmlWriter.writeTextElement("MaxValue",QString::number(r->GetMaxValue()));
        }
        else if(m->GetTypeId() == "RandomString")
        {
            ResourceModelRandomString * r = qobject_cast<ResourceModelRandomString *>(m);
            xmlWriter.writeTextElement("Value",r->GetValue());
        }else if(m->GetTypeId() == "RandomInteger")
        {
            ResourceModelRandomInteger * r = qobject_cast<ResourceModelRandomInteger *>(m);
            xmlWriter.writeTextElement("MinUserValue",QString::number(r->GetMinUserValue()));
            xmlWriter.writeTextElement("MinDesignValue",QString::number(r->GetMinDesignValue()));
            xmlWriter.writeTextElement("MaxUserValue",QString::number(r->GetMaxUserValue()));
            xmlWriter.writeTextElement("MaxDesignValue",QString::number(r->GetMaxDesignValue()));

        }else if(m->GetTypeId() == "Database")
        {
            ResourceModelDatabase * r = qobject_cast<ResourceModelDatabase *>(m);


            QStringList ColumnIds;
            foreach(int ColumnInt, r->GetColumnIds())
            {
                ColumnIds.append(QString::number(ColumnInt));
            }

            xmlWriter.writeTextElement("GroupList",r->GetGroupList().join(","));
            xmlWriter.writeTextElement("TableId",QString::number(r->GetTableId()));
            xmlWriter.writeTextElement("ColumnIds",ColumnIds.join(","));
            xmlWriter.writeTextElement("Clean",QString::number(r->GetClean()));
            xmlWriter.writeTextElement("Mix",QString::number(r->GetMix()));
            xmlWriter.writeTextElement("MaxSuccess",QString::number(r->GetSuccessAttempts()));
            xmlWriter.writeTextElement("MaxFail",QString::number(r->GetFailAttempts()));
            xmlWriter.writeTextElement("MaxSimultaneous",QString::number(r->GetNumberSimultaneousUse()));
            xmlWriter.writeTextElement("Interval",QString::number(r->GetIntervalBetweenUsage()));
            xmlWriter.writeTextElement("ReloadInterval",QString::number(r->GetLoadInterval()));
            xmlWriter.writeTextElement("RenewInterval",QString::number(r->GetRenewInterval()));
            xmlWriter.writeTextElement("Greedy",QString::number(r->GetGreedy()));

        }else if(m->GetTypeId() == "LinesFromFile")
        {
            ResourceModelFile * r = qobject_cast<ResourceModelFile *>(m);
            xmlWriter.writeTextElement("Filename",r->GetFilename());
            xmlWriter.writeTextElement("Clean",QString::number(r->GetWrite()));
            xmlWriter.writeTextElement("Read",QString::number(r->GetRead()));
            xmlWriter.writeTextElement("Mix",QString::number(r->GetMix()));
            xmlWriter.writeTextElement("MaxSuccess",QString::number(r->GetSuccessAttempts()));
            xmlWriter.writeTextElement("MaxFail",QString::number(r->GetFailAttempts()));
            xmlWriter.writeTextElement("MaxSimultaneous",QString::number(r->GetNumberSimultaneousUse()));
            xmlWriter.writeTextElement("Interval",QString::number(r->GetIntervalBetweenUsage()));
            xmlWriter.writeTextElement("ReloadInterval",QString::number(r->GetLoadInterval()));
            xmlWriter.writeTextElement("RenewInterval",QString::number(r->GetRenewInterval()));
            xmlWriter.writeTextElement("Greedy",QString::number(r->GetGreedy()));

        }else if(m->GetTypeId() == "FilesFromDirectory")
        {
            ResourceModelDirectory * r = qobject_cast<ResourceModelDirectory *>(m);
            xmlWriter.writeTextElement("FilesFromDirectory",r->GetDirectory());
            xmlWriter.writeTextElement("Wildcard",r->GetWildcard());
            xmlWriter.writeTextElement("Clean",QString::number(r->GetClean()));
            xmlWriter.writeTextElement("Mix",QString::number(r->GetMix()));
            xmlWriter.writeTextElement("MaxSuccess",QString::number(r->GetSuccessAttempts()));
            xmlWriter.writeTextElement("MaxFail",QString::number(r->GetFailAttempts()));
            xmlWriter.writeTextElement("MaxSimultaneous",QString::number(r->GetNumberSimultaneousUse()));
            xmlWriter.writeTextElement("Interval",QString::number(r->GetIntervalBetweenUsage()));
            xmlWriter.writeTextElement("ReloadInterval",QString::number(r->GetLoadInterval()));
            xmlWriter.writeTextElement("RenewInterval",QString::number(r->GetRenewInterval()));
            xmlWriter.writeTextElement("Greedy",QString::number(r->GetGreedy()));

        }else if(m->GetTypeId() == "LinesFromUrl")
        {
            ResourceModelUrl * r = qobject_cast<ResourceModelUrl *>(m);
            xmlWriter.writeTextElement("LinesFromUrl",r->GetUrl());
            xmlWriter.writeTextElement("Mix",QString::number(r->GetMix()));
            xmlWriter.writeTextElement("MaxSuccess",QString::number(r->GetSuccessAttempts()));
            xmlWriter.writeTextElement("MaxFail",QString::number(r->GetFailAttempts()));
            xmlWriter.writeTextElement("MaxSimultaneous",QString::number(r->GetNumberSimultaneousUse()));
            xmlWriter.writeTextElement("Interval",QString::number(r->GetIntervalBetweenUsage()));
            xmlWriter.writeTextElement("ReloadInterval",QString::number(r->GetLoadInterval()));
            xmlWriter.writeTextElement("RenewInterval",QString::number(r->GetRenewInterval()));
            xmlWriter.writeTextElement("CaptureMethod",QString::number(r->GetCaptureMethod()));
            xmlWriter.writeTextElement("CaptureArgument",r->GetCaptureArgument());
            xmlWriter.writeTextElement("Greedy",QString::number(r->GetGreedy()));

        }else if(m->GetTypeId() == "Select")
        {
            ResourceModelSelect * r = qobject_cast<ResourceModelSelect *>(m);
            xmlWriter.writeTextElement("Values",r->GetValues().join("\r\n"));

            QString selected;
            bool first = true;
            foreach(int s,r->GetSelected())
            {
                if(!first)
                    selected += ",";

                first = false;
                selected += QString::number(s);

            }
            xmlWriter.writeTextElement("Selected",selected);
            xmlWriter.writeTextElement("SelectType",QString::number(r->GetSelectType()));
        }





    }

    void XmlResourceController::FromModelToView(IResources * resources, bool Clear)
    {
        QFile file(FileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            Result = false;
            ErrorString = QString("Can't write file %1").arg(FileName);
            return;
        }
        QXmlStreamWriter xmlWriter;
        xmlWriter.setAutoFormatting(true);
        xmlWriter.setAutoFormattingIndent(5);
        xmlWriter.setDevice(&file);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("BrowserAutomationStudioProject");
        xmlWriter.writeTextElement("Script",Script);
        xmlWriter.writeTextElement("DatabaseId",DatabaseId);
        xmlWriter.writeTextElement("Schema",Schema);

        xmlWriter.writeTextElement("ConnectionIsRemote",(ConnectionIsRemote) ? "true" : "false");
        xmlWriter.writeTextElement("ConnectionServer",ConnectionServer);
        xmlWriter.writeTextElement("ConnectionPort",ConnectionPort);
        xmlWriter.writeTextElement("ConnectionLogin",ConnectionLogin);
        xmlWriter.writeTextElement("ConnectionPassword",ConnectionPassword);

        xmlWriter.writeTextElement("ScriptName",ScriptName);
        xmlWriter.writeTextElement("HideBrowsers",(HideBrowsers) ? "true" : "false");
        xmlWriter.writeTextElement("ScriptVersion",ScriptVersion);
        xmlWriter.writeTextElement("AvailableLanguages",AvailableLanguages);

        if(!EngineVersion.isEmpty())
            xmlWriter.writeTextElement("EngineVersion",EngineVersion);
        if(!SettingsWorker.isEmpty())
            xmlWriter.writeTextElement("SettingsWorker",SettingsWorker);
        if(!ChromeCommandLine.isEmpty())
            xmlWriter.writeTextElement("ChromeCommandLine",ChromeCommandLine);
        if(!ModulesMetaJson.isEmpty())
            xmlWriter.writeTextElement("ModulesMetaJson",ModulesMetaJson);


        xmlWriter.writeStartElement("OutputTitle1");
            OutputTitle1.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle2");
            OutputTitle2.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle3");
            OutputTitle3.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle4");
            OutputTitle4.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle5");
            OutputTitle5.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle6");
            OutputTitle6.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle7");
            OutputTitle7.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle8");
            OutputTitle8.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("OutputTitle9");
            OutputTitle9.WriteXml(&xmlWriter);
        xmlWriter.writeEndElement();

        xmlWriter.writeTextElement("OutputVisible1",QString::number(OutputVisible1));
        xmlWriter.writeTextElement("OutputVisible2",QString::number(OutputVisible2));
        xmlWriter.writeTextElement("OutputVisible3",QString::number(OutputVisible3));
        xmlWriter.writeTextElement("OutputVisible4",QString::number(OutputVisible4));
        xmlWriter.writeTextElement("OutputVisible5",QString::number(OutputVisible5));
        xmlWriter.writeTextElement("OutputVisible6",QString::number(OutputVisible6));
        xmlWriter.writeTextElement("OutputVisible7",QString::number(OutputVisible7));
        xmlWriter.writeTextElement("OutputVisible8",QString::number(OutputVisible8));
        xmlWriter.writeTextElement("OutputVisible9",QString::number(OutputVisible9));
        QList<IResourceModel * > * model = resources->GetModelList();
        int size = model->size();
        xmlWriter.writeStartElement("ModelList");
        for(int i = 0;i<size;i++)
        {
            IResourceModel *m = model->at(i);
            xmlWriter.writeStartElement("Model");
                WriteModel(xmlWriter,m);
            xmlWriter.writeEndElement();

            QList<IResourceModel *> Defaults = m->GetDefaults();
            xmlWriter.writeStartElement("Defaults");
            foreach(IResourceModel *md,Defaults)
            {
                xmlWriter.writeStartElement("Default");
                WriteModel(xmlWriter,md);
                xmlWriter.writeEndElement();
            }


            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        Result = true;
    }
}
