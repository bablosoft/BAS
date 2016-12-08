#include "enterlicensedialog.h"
#include "ui_enterlicensedialog.h"
#include <QPushButton>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QXmlStreamReader>
#include <QDesktopServices>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    EnterLicenseDialog::EnterLicenseDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::EnterLicenseDialog)
    {
        ui->setupUi(this);

        HeightTotal = 113;
        WidthTotal = 423;

        NeedAKeyButton = new QPushButton(ui->buttonBox);
        NeedAKeyButton->setText(tr("Need A Key?"));
        NeedAKeyButton->setVisible(false);
        NeedAKeyButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        NeedAKeyButton->resize(NeedAKeyButton->width(),24);
        connect(NeedAKeyButton,SIGNAL(clicked()),this,SLOT(NeedAKeyClicked()));
        ui->buttonBox->addButton((QAbstractButton *)NeedAKeyButton,QDialogButtonBox::ResetRole);

        DataButton = new QPushButton(ui->buttonBox);
        DataButton->setText(tr("Data"));
        DataButton->setIcon(QIcon(":/engine/images/database.png"));
        DataButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        DataButton->resize(DataButton->width(),24);
        connect(DataButton,SIGNAL(clicked()),this,SIGNAL(ShowDatabase()));
        ui->buttonBox->addButton((QAbstractButton *)DataButton,QDialogButtonBox::ResetRole);


        Settings = new QSettings("settings.ini",QSettings::IniFormat,this);
        QString email = Settings->value("email").toString();
        LastSelectedScript = Settings->value("LastSelectedScript").toString();

        bool SavePassToDisk = Settings->value("SavePassToDisk", true).toBool();
        ui->checkBox->setChecked(SavePassToDisk);
        if(SavePassToDisk)
            ui->lineEdit_2->setText(Settings->value("Pass","").toString());


        if(!email.isEmpty())
        {
            ui->lineEdit->setText(email);
            ui->lineEdit_2->setFocus();
        }

        connect(this,SIGNAL(accepted()),this,SLOT(Accepted()));

    }

    void EnterLicenseDialog::HideDatabaseButton()
    {
        DataButton->setVisible(false);
    }

    void EnterLicenseDialog::NeedAKeyClicked()
    {
        QString CurrentScript = ui->ScriptIdCombo->currentText().replace(" ","").split("(").first();
        QString Link = Scripts[CurrentScript].Link;
        QUrl Url = QUrl(Link);
        QDesktopServices::openUrl(Url);

    }

    QString EnterLicenseDialog::AddSpacesToScriptName(const QString& ScriptName,const QString& Version)
    {
        QString temp = ScriptName;
        temp = temp.replace(QRegExp("([A-Z])([A-Z])([a-z])"), "\\1 \\2\\3");
        temp = temp.replace(QRegExp("([a-z])([A-Z])"), "\\1 \\2");
        temp.append(" (");
        temp.append(Version);
        temp.append(")");
        return temp;
    }

    void EnterLicenseDialog::SetLanguage(const QString& Language)
    {
        this->Language = Language;
    }

    void EnterLicenseDialog::SetProjectFile(const QString& FileName)
    {
        this->FileName = FileName;
    }

    void EnterLicenseDialog::Init()
    {
        QFile file(FileName);
        QXmlStreamReader xmlReader;
        if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
        {
            return;
        }

        Scripts.clear();
        xmlReader.setDevice(&file);


        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if(xmlReader.name() == "RemoteList" && token == QXmlStreamReader::StartElement)
            {
                foreach(QXmlStreamAttribute attr, xmlReader.attributes())
                {
                    if(attr.name() == QString("link_") + Language)
                    {
                        PromoLink = attr.value().toString();
                    }
                }
            }
            if(xmlReader.name() == "Remote" && token == QXmlStreamReader::StartElement)
            {
                QString ScriptName;
                ScriptData Data;
                Data.IsFree = false;

                foreach(QXmlStreamAttribute attr, xmlReader.attributes())
                {
                    if(attr.name() == "ScriptName")
                    {
                        ScriptName = attr.value().toString();
                    }else if(attr.name() == Language)
                    {
                        Data.Description = attr.value().toString();
                    }
                    else if(attr.name() == QString("link_") + Language)
                    {
                        Data.Link = attr.value().toString();
                    }else if(attr.name() == QString("Free"))
                    {
                        Data.IsFree = attr.value().toString() == "true";
                    }else if(attr.name() == QString("Version"))
                    {
                        Data.Version = attr.value().toString();
                    }
                }
                if(!ScriptName.isEmpty())
                {
                    if(LastSelectedScript.isEmpty())
                        LastSelectedScript = ScriptName;

                    Scripts[ScriptName] = Data;
                    ui->ScriptIdCombo->addItem(AddSpacesToScriptName(ScriptName,Data.Version));
                }
            }
        }

        if(Scripts.count() <= 1)
        {
            ui->ScriptIdCombo->setVisible(false);
            ui->ScriptDescriptionLabel->setVisible(false);
            NeedAKeyButton->setVisible(false);
            this->resize(WidthTotal,HeightTotal);
            if(Scripts.count() == 1)
                SetScriptData(Scripts[0]);

        }else
        {
            ui->ScriptIdCombo->setCurrentText(AddSpacesToScriptName(LastSelectedScript,Scripts[LastSelectedScript].Version));
            SetScriptData(Scripts[LastSelectedScript]);


            connect(ui->ScriptIdCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(UpdateDescription(QString)));
        }
        file.close();

    }

    void EnterLicenseDialog::LinkClicked(QUrl url)
    {
        //if(url.toString().contains("seotools"))
            QDesktopServices::openUrl(url);
        //else
        //    ui->webView->load(url);
    }

    void EnterLicenseDialog::SetScriptData(const ScriptData& Data)
    {
        qDebug()<<Data.Description<<Data.IsFree<<Data.Link<<Data.Version;
        ui->ScriptDescriptionLabel->setText(Data.Description);
        int height = HeightTotal;
        if(Data.IsFree)
        {
            height = HeightTotal - 71;
        }
        this->resize(WidthTotal,height);
        ui->lineEdit->setVisible(!Data.IsFree);
        ui->lineEdit_2->setVisible(!Data.IsFree);
        ui->label->setVisible(!Data.IsFree);
        ui->label_2->setVisible(!Data.IsFree);
        ui->checkBox->setVisible(!Data.IsFree);
        //NeedAKeyButton->setVisible(!Data.IsFree);

    }

    void EnterLicenseDialog::UpdateDescription(const QString & Text)
    {
        LastSelectedScript = ui->ScriptIdCombo->currentText().replace(" ","").split("(").first();
        SetScriptData(Scripts[LastSelectedScript]);
    }

    QString EnterLicenseDialog::GetScriptId()
    {
        return LastSelectedScript;
    }

    void EnterLicenseDialog::Accepted()
    {
        Settings->setValue("email",GetEmail());
        bool SavePassToDisk = ui->checkBox->isChecked();
        Settings = new QSettings("settings.ini",QSettings::IniFormat,this);
        Settings->setValue("SavePassToDisk",SavePassToDisk);
        if(SavePassToDisk)
            Settings->setValue("Pass",ui->lineEdit_2->text());
        else
            Settings->setValue("Pass","");

        Settings->setValue("LastSelectedScript",LastSelectedScript);

    }

    QString EnterLicenseDialog::GetEmail()
    {
        return ui->lineEdit->text();
    }
    QString EnterLicenseDialog::GetPassword()
    {
        return ui->lineEdit_2->text();
    }

    EnterLicenseDialog::~EnterLicenseDialog()
    {
        delete ui;
    }

    void EnterLicenseDialog::changeEvent(QEvent *e)
    {
        QDialog::changeEvent(e);
        switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
        }
    }
}
