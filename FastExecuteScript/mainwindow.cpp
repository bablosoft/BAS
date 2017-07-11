#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scriptmultiworker.h"
#include "plaintextlogger.h"
#include "scriptresourcesfromqt.h"
#include "timeoutwaiterfactory.h"
#include "manualcaptchasolver.h"
#include "solverfactory.h"
#include "resourcehandlersfactory.h"
#include "scriptworkerfactory.h"
#include "httpclientfactory.h"
#include "pop3clientfactory.h"
#include "resources.h"
#include "engineresourcecontroller.h"
#include "stringbuilder.h"
#include "engineresources.h"
#include "qtresourcecontroller.h"
#include "xmlresourcecontroller.h"
#include "askuserforresourcesdialog.h"
#include <QDir>
#include "networkaccessmanagerfactory.h"
#include "resourceuserwidgetfactory.h"
#include "processcomunicatorfactory.h"
#include "subprocessbrowserfactory.h"
#include "subprocessnetworkaccessmanagerfactory.h"
#include "preprocessor.h"
#include "additionalsettingswidgets.h"
#include "copyresourcecontroller.h"
#include <QTime>
#include <QProcess>
#include <QPushButton>
#include "skincontroller.h"
#include "complexlogger.h"
#include "filelogger.h"
#include <QDesktopServices>
#include "systemtraynotifier.h"
#include "toprightpositioner.h"
#include "scriptsuspender.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include "helper.h"
#include "languagemodel.h"
#include "scriptlanguagechooserdialog.h"
#include "periodicalhttprequest.h"
#include "htmlparser.h"
#include "imapclientfactory.h"
#include "advancedhider.h"
#include "htmlparserfactory.h"
#include "helperfactory.h"
#include "memoryinfo.h"
#include "loglocationchooser.h"
#include "properties.h"
#include "databaseconnectionwindow.h"
#include <QDirIterator>
#include "workersettings.h"
#include "noneencryptor.h"

using namespace BrowserAutomationStudioFramework;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),Worker(0),
    ui(new Ui::MainWindow)//, UserWidgetControllerPointer(0), CaptchaWidgetPresent(false), IsClosingWindow(false), AlreadyShowedBrowserPanel(false), _DatabaseAdmin(0), Ask(0), _DataBaseConnector(0)
{
    qDebug()<<"Start 018.0";
    UserWidgetControllerPointer = 0;
    IsSilent = false;
    CaptchaWidgetPresent = false;
    IsClosingWindow = false;
    AlreadyShowedBrowserPanel = false;
    _DatabaseAdmin = 0;
    Ask = 0;
    _DataBaseConnector = 0;
    qDebug()<<"Start 018.1";

    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));

    _TabBlink = new MainWindowTabBlink(this);
    _TabBlink->SetWidget(this);
    qDebug()<<"Start 018.2";
    ui->setupUi(this);
    qDebug()<<"Start 018.3";
    _MultiTimer = new MultiTimer(this);
    qDebug()<<"Start 018.4";
    //_MultiTimer = 0;
    this->hide();
    qDebug()<<"Start 018.5";

}

void MainWindow::SetDatabaseConnector(MongoDatabaseConnector * _DatabaseConnector, MongoDatabaseConnector * _DatabaseConnector2, MongoDatabaseConnector * _DatabaseConnector3, DatabaseState* _DataBaseState, CsvHelper* _CsvHelper)
{
    this->_DataBaseConnector = _DatabaseConnector;
    this->_DataBaseConnector2 = _DatabaseConnector2;
    this->_DataBaseConnector3 = _DatabaseConnector3;
    this->_DataBaseState = _DataBaseState;
    this->_CsvHelper = _CsvHelper;
}

void MainWindow::SetIsSilent()
{
    IsSilent = true;
}

void MainWindow::SetRemote(const QString& Remote)
{
    this->Remote = Remote;
}

void MainWindow::Abort()
{
    if(Worker)
    {
        QStringList items;
        items << tr("Stop instant") << tr("Wait each thread");

        bool ok;
        QString item = QInputDialog::getItem(this, tr("Stop"), tr("Stop type"), items, 0, false, &ok);

        if(Worker)
        {
            if(ok && !item.isEmpty())
            {
                if(item == items[0])
                    Worker->Abort();
                else
                    Worker->AbortNotInstant();
            }
        }
    }
}

void MainWindow::Start()
{

    _ModuleManager = new ModuleManager(this);

    NeedRestart = false;
    BrowserFactory = 0;
    AlreadyShowsMessage = false;

    TranslateEngine.SetDirectory(":/engine/translate");
    TranslateFastExecuteScript.SetDirectory(":/fastexecutescript/translate");
    qDebug()<<"Start 020";
    bool DataBaseConnectorPreserved = _DataBaseConnector;
    qDebug()<<"Start 021";
    if(!DataBaseConnectorPreserved)
    {
        qDebug()<<"Start 022";
        _DataBaseConnector = new MongoDatabaseConnector(this);
        {
            DatabaseConnectionWindow * _DatabaseConnectionWindow = new DatabaseConnectionWindow(_DataBaseConnector);
            _DatabaseConnectionWindow->SetIsSilent(IsSilent);
            _DataBaseConnector->SetDatabaseConnectionWindow(_DatabaseConnectionWindow);
        }

        qDebug()<<"Start 023";
        _CsvHelper = new CsvHelper(_DataBaseConnector);
        qDebug()<<"Start 024";
        _DataBaseConnector->SetCsvHelper(_CsvHelper);
        qDebug()<<"Start 025";

        _DataBaseState = new DatabaseState(this);
        qDebug()<<"Start 026";
        _DataBaseConnector2 = new MongoDatabaseConnector(_DataBaseState);
        {
            DatabaseConnectionWindow * _DatabaseConnectionWindow = new DatabaseConnectionWindow(_DataBaseConnector2);
            _DatabaseConnectionWindow->SetIsSilent(IsSilent);
            _DataBaseConnector2->SetDatabaseConnectionWindow(_DatabaseConnectionWindow);
        }
        qDebug()<<"Start 027";
        _DataBaseState->SetDatabaseConnector(_DataBaseConnector2);
        qDebug()<<"Start 028";
        connect(_DataBaseConnector,SIGNAL(GroupManipulated()),_DataBaseState,SLOT(Reload()));
        qDebug()<<"Start 029";
        _DataBaseConnector3 = new MongoDatabaseConnector(this);
        {
            DatabaseConnectionWindow * _DatabaseConnectionWindow = new DatabaseConnectionWindow(_DataBaseConnector3);
            _DatabaseConnectionWindow->SetIsSilent(IsSilent);
            _DataBaseConnector3->SetDatabaseConnectionWindow(_DatabaseConnectionWindow);
        }
        qDebug()<<"Start 030";
    }

    qDebug()<<"Start 031";
    LangModel = new LanguageModel(this);
    TrayNotifier = new SystemTrayNotifier(this);
    TrayNotifier->Init();
    qDebug()<<"Start 032";

    Settings = new QSettings("settings.ini",QSettings::IniFormat,this);
    LogLocation = Settings->value("LogLocation","../../logs").toString();
    qDebug()<<"Start 033";

    SkinController * skin = new SkinController();
    skin->ApplyTheme(Settings->value("Theme","DarkFusion").toString());
    skin->deleteLater();
    qDebug()<<"Start 034";

    Language = Settings->value("DefaultLanguageScript","").toString().toLower();
    qDebug()<<"Start 035";
    if(Language.isEmpty())
    {
        if(!IsSilent)
        {
            ScriptLanguageChooserDialog LangDialog;
            LangDialog.SetLanguageModel(LangModel);
            if(!LangDialog.exec())
            {
                QTimer::singleShot(50,this,SLOT(Close()));
                return;
            }
            Language = LangDialog.GetLang();

            Settings->setValue("DefaultLanguageScript",Language);
        }else
        {
            Language = "en";
        }
    }
    LangModel->SetInterfaceLanguage(Language);
    qDebug()<<"Start 036";

    qDebug()<<"Start 047";
    TranslateEngine.Translate(Language);
    TranslateFastExecuteScript.Translate(Language);
    LangModel->SetScriptAvailableLanguagesString(Language);
    qDebug()<<"Start 048";

    LogMenuButton = new QPushButton(ui->tab_2);
    LogMenuButton->setIcon(QIcon(":/images/menu2.png"));
    LogMenuButton->setMaximumWidth(30);

    TopRightPositioner * AllButtonPositioner = new TopRightPositioner(this);
    AllButtonPositioner->SetChild(LogMenuButton);
    AllButtonPositioner->SetParent(ui->tab_2);
    AllButtonPositioner->SetMarginRight(30);
    AllButtonPositioner->SetMarginTop(20);
    AllButtonPositioner->Start();
    connect(LogMenuButton,SIGNAL(clicked()),this,SLOT(LogMenu_Click()));

    qDebug()<<"Start 049";

    movie = new QMovie(":/fastexecutescript/images/loading.gif");
    movie->setParent(this);
    ui->LabelGif->setMovie(movie);
    movie->start();


    qDebug()<<"Start 050";


    InitRecources();

    if(!Remote.isEmpty())
    {
        qDebug()<<"Work on remote "<<Remote;
        IHttpClient * Client = _HttpClientFactory->GetHttpClient();
        QEventLoop loop;
        Client->Connect(&loop, SLOT(quit()));
        Client->Download(Remote,"project.xml");
        //connect(_DataBaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
        //loop.exec();
        qDebug()<<"Done downloading. Was Error - "<<Client->WasError()<<". Error string\""<<Client->GetErrorString()<<"\"";
    }

    qDebug()<<"Start 051";
    InitWidgets();
    qDebug()<<"Start 052";

    IPreprocessor * _Preprocessor = new Preprocessor(this);
    _Preprocessor->SetEncryptor(new NoneEncryptor(_Preprocessor));
    qDebug()<<"Start 053";

    XmlResourceController loader;

    //Load from file
    loader.SetFileName("project.xml");

    qDebug()<<"Start 063";
    //Find actual and default files location
    QDir dir(QCoreApplication::applicationDirPath());
    QString ActualFilePath = dir.absoluteFilePath(QString("./Actual") + QString(".xml"));
    QString DefaultFilePath = ActualFilePath + ".default.xml";
    qDebug()<<"Start 065";

    //Delete actual if defaults not exists
    if(!QFile::exists(DefaultFilePath) && QFile::exists(ActualFilePath))
    {
        QFile(ActualFilePath).remove();
    }

    qDebug()<<"Start 066";
    Res->FromViewToModel(&loader);

    {
        QFile f("chrome_command_line.txt");
        if(f.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&f);
            out<<loader.GetChromeCommandLine();
        }
        f.close();
    }
    {
        QFile f("settings_worker.ini");
        if(f.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&f);
            out<<loader.GetSettingsWorker();
        }
        f.close();
    }
    {
        QFile f("modules/meta.json");
        if(f.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&f);
            out<<loader.GetModulesMetaJson();
        }
        f.close();
    }

    if(!DataBaseConnectorPreserved)
    {
        qDebug()<<"Start 037";
        _DataBaseConnector->Init(Language);
        if(!_DataBaseConnector->Start(loader.GetSchema(), loader.GetDatabaseId(), loader.GetConnectionIsRemote(), loader.GetConnectionServer(), loader.GetConnectionPort(), loader.GetConnectionLogin(), loader.GetConnectionPassword()))
        {
            QEventLoop loop;
            connect(_DataBaseConnector, SIGNAL(Started()), &loop, SLOT(quit()));
            loop.exec();
        }
        qDebug()<<"Start 038";
        if(_DataBaseConnector->HasDatabase())
        {
            qDebug()<<"Start 039";
            if(_DataBaseConnector->WasError())
            {
                //QMessageBox::information(0, tr("Database Error"), _DataBaseConnector->GetError());
                QTimer::singleShot(50,this,SLOT(Close()));
                return;
            }
            qDebug()<<"Start 040";

            if(!_DataBaseConnector2->Start(loader.GetSchema(), loader.GetDatabaseId(), loader.GetConnectionIsRemote(), loader.GetConnectionServer(), loader.GetConnectionPort(), loader.GetConnectionLogin(), loader.GetConnectionPassword()))
            {
                QEventLoop loop;
                connect(_DataBaseConnector2, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            qDebug()<<"Start 041";
            if(_DataBaseConnector2->WasError())
            {
                //QMessageBox::information(0, tr("Database Error"), _DataBaseConnector2->GetError());
                QTimer::singleShot(50,this,SLOT(Close()));
                return;
            }
            qDebug()<<"Start 042";

            if(!_DataBaseConnector3->Start(loader.GetSchema(), loader.GetDatabaseId(), loader.GetConnectionIsRemote(), loader.GetConnectionServer(), loader.GetConnectionPort(), loader.GetConnectionLogin(), loader.GetConnectionPassword()))
            {
                QEventLoop loop;
                connect(_DataBaseConnector3, SIGNAL(Started()), &loop, SLOT(quit()));
                loop.exec();
            }
            qDebug()<<"Start 043";
            if(_DataBaseConnector3->WasError())
            {
                //QMessageBox::information(0, tr("Database Error"), _DataBaseConnector3->GetError());
                QTimer::singleShot(50,this,SLOT(Close()));
                return;
            }
            qDebug()<<"Start 044";
            _DataBaseState->Reload();
        }else
        {
            qDebug()<<"Start 045";
            ui->actionData->setVisible(false);
        }
    }else
    {
        qDebug()<<"Start 046";
        if(!_DataBaseConnector->HasDatabase())
        {
            ui->actionData->setVisible(false);
        }
    }



    this->setWindowTitle(QString("%1(%2)").arg(loader.GetScriptName()).arg(loader.GetScriptVersion()));

    bool NeedToUseAdditionalSettings = Settings->value("RenderMethodVisible","false").toString().toLower() == "true";
    qDebug()<<"Start 067";

    AdditionalSettingsWidgets AdditionalSettingsStatic;
    AdditionalSettings = &AdditionalSettingsStatic;
    qDebug()<<"Start 068";

    if(NeedToUseAdditionalSettings)
        AdditionalSettings->SetDefault(Settings->value("DefaultWorker").toString());

    qDebug()<<"Start 069";
    XmlResourceController XmlActualStatic;
    XmlResourceController *XmlActual = &XmlActualStatic;
    qDebug()<<"Start 070";

    //Load From File

    XmlActual->SetFileName(ActualFilePath);
    qDebug()<<"Start 071";

    if(true/*Res->NeedToFillByUser()*/)
    {
        //Create dialog
        AskUserForResourcesDialog ask(Settings->value("AskUserForResourcesWidth", 900).toInt(),Settings->value("AskUserForResourcesHeight", 600).toInt());
        Ask = &ask;


        
        if(Settings->value("HideLanguageChooser",false).toBool())
        {
            Ask->RemoveLanguageChooser();
        }
        Ask->setWindowTitle(QString("%1(%2)").arg(loader.GetScriptName()).arg(loader.GetScriptVersion()));
        ask.setModal(true);



        //Update with actual settings
        {
            Resources ResActual;
            ResActual.FromViewToModel(XmlActual);

            Resources ResDefault;
            XmlResourceController XmlDefaults;
            XmlDefaults.SetFileName(DefaultFilePath);
            ResDefault.FromViewToModel(&XmlDefaults);


            CopyResourceController Copy;
            Copy.SetResources(&ResActual);
            Copy.SetDefaults(&ResDefault);
            Res->FromViewToModel(&Copy);
        }


        ShowData();
        connect(Ask,SIGNAL(Default()),this,SLOT(SetDefault()));
        connect(Ask,SIGNAL(Save(QString)),this,SLOT(SaveActual(QString)));
        connect(Ask,SIGNAL(Load(QString)),this,SLOT(LoadActual(QString)));
        connect(Ask,SIGNAL(Reset()),this,SLOT(Restart()));
        connect(Ask,SIGNAL(ShowLanguage()),this,SLOT(ChooseLanguage()));
        connect(Ask,SIGNAL(ShowLogLocation()),this,SLOT(ChooseLogLocation()));
        connect(Ask,SIGNAL(ShowDatabase()),this,SLOT(ShowDatabase()));

        if(!_DataBaseConnector->HasDatabase())
        {
            Ask->HideDatabaseButton();
        }

        //Ask user for input
        if(!IsSilent)
        {
            bool ask_exec_res = ask.exec();

            Settings->setValue("AskUserForResourcesWidth", ask.width());
            Settings->setValue("AskUserForResourcesHeight", ask.height());
            Settings->sync();

            if(!ask_exec_res)
            {
                QTimer::singleShot(50,this,SLOT(Close()));
                delete UserWidgetControllerPointer;
                UserWidgetControllerPointer = 0;
                return;
            }
        }

        //Save defaults
        {
            Resources ResDefaults;

            ResDefaults.FromViewToModel(&loader);
            XmlResourceController XmlDefaults;
            XmlDefaults.SetFileName(DefaultFilePath);
            ResDefaults.FromModelToView(&XmlDefaults);
        }


        if(NeedToUseAdditionalSettings)
        {
            Settings->setValue("DefaultWorker",AdditionalSettings->ParseWidget());
            InitBrowserList(AdditionalSettings->ParseWidget());
        }else
        {
            InitBrowserList(Settings->value("DefaultWorker", "MultiProcessQt5").toString());
        }

        //Load data to new model and then to engine resources
        Resources UserRes;
        UserRes.FromViewToModel(UserWidgetControllerPointer);
        UserRes.FromModelToView(XmlActual);
        UserRes.FromModelToView(EngineResController);

        //Clean memory
        delete UserWidgetControllerPointer;
        UserWidgetControllerPointer = 0;
        Ask = 0;
    }



    //Prepare Worker
    ScriptMultiWorker* worker = new ScriptMultiWorker(this);
    WorkerSettings *_WorkerSettings = new WorkerSettings(worker);
    _WorkerSettings->SetWorkerPathSafe(Settings->value("Worker5Safe",QVariant("./Worker/Worker.exe")).toString());
    _WorkerSettings->SetWorkerPathNotSafe(Settings->value("Worker5NotSafe",QVariant("./WorkerNotSafe/Worker.exe")).toString());
    {
        QSettings SettingsWorker("settings_worker.ini",QSettings::IniFormat);
        _WorkerSettings->ParseFromSettings(SettingsWorker);
    }
    worker->SetWorkerSettings(_WorkerSettings);

    worker->SetProjectPath(QDir::current().absoluteFilePath("project.xml"));
    worker->SetModuleManager(_ModuleManager);
    worker->SetStringBuilder(StringBuild);
    worker->SetAdditionEngineScripts(_ModuleManager->GetModuleEngineCode());
    worker->SetPreprocessor(_Preprocessor);

    worker->SetBrowserFactory(BrowserFactory);


    Output->Clear();
    Output->disconnect();
    ReportData = new ScriptMultiWorkerReportData(this);
    ResVisualizer = new ResourcesVisualizer(this);
    connect(ResVisualizer,SIGNAL(ChangedState(bool)),this,SLOT(ResourcesReportStateChanged(bool)));
    ResVisualizer->SetReportData(EngineResController->GetWatcherList());
    DataVisualizer = new ReportDataVisualizer(this);
    DataVisualizer->SetReportData(ReportData);
    connect(ui->actionShow_Report,SIGNAL(triggered()),DataVisualizer,SLOT(ShowReport()));
    connect(FactorySolver,SIGNAL(UsedSolver(QString)),ReportData,SLOT(CaptchaUsed(QString)));
    connect(FactorySolver,SIGNAL(FailedSolver(QString)),ReportData,SLOT(CaptchaFailed(QString)));

    connect(ui->actionShow,SIGNAL(triggered()),this,SLOT(show()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(Close()));
    connect(ui->actionRestart,SIGNAL(triggered()),this,SLOT(Restart()));
    connect(ui->actionRestart,SIGNAL(triggered()),this,SLOT(Close()));
    connect(ui->actionData,SIGNAL(triggered()),this,SLOT(ShowDatabase()));
    connect(TrayNotifier,SIGNAL(Show()),this,SLOT(show()));

    QMenu *Menu = new QMenu(this);
    Menu->addAction(ui->actionShow);
    Menu->addSeparator();
    Menu->addAction(ui->actionExit);
    TrayNotifier->SetContextmenu(Menu);



    connect(worker,SIGNAL(Success()),Output,SLOT(Success()));
    connect(worker,SIGNAL(Failed()),Output,SLOT(Failed()));
    connect(worker,SIGNAL(ProgressMaximum(int)),Output,SLOT(ProgressMaximum(int)));
    connect(worker,SIGNAL(ProgressValue(int)),Output,SLOT(ProgressValue(int)));
    connect(worker,SIGNAL(Finished()),Output,SLOT(Finished()));



    //Set Loggers
    QDateTime CurrentDateTime = QDateTime::currentDateTime();
    QString datestringfile = CurrentDateTime.toString("yyyy.MM.dd.hh.mm.ss");

    Output->SetOutputTitle1(loader.GetOutputTitle1());
    Output->SetOutputTitle2(loader.GetOutputTitle2());
    Output->SetOutputTitle3(loader.GetOutputTitle3());
    Output->SetOutputTitle4(loader.GetOutputTitle4());
    Output->SetOutputTitle5(loader.GetOutputTitle5());
    Output->SetOutputTitle6(loader.GetOutputTitle6());
    Output->SetOutputTitle7(loader.GetOutputTitle7());
    Output->SetOutputTitle8(loader.GetOutputTitle8());
    Output->SetOutputTitle9(loader.GetOutputTitle9());

    ComplexLogger *ComplexLoggerResults1 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults1 = new FileLogger(ComplexLoggerResults1);
    QString FileName1 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle1().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName1(FileName1);
    FileLoggerResults1->SetFileName(FileName1);
    PlainTextLogger * PlainTextLoggerResults1 = new PlainTextLogger(ComplexLoggerResults1);
    PlainTextLoggerResults1->SetPlainTextElement(Output->GetOutput(0));
    ComplexLoggerResults1->AddLogger(FileLoggerResults1);
    ComplexLoggerResults1->AddLogger(PlainTextLoggerResults1);
    connect(ComplexLoggerResults1, SIGNAL(NewLine()), this, SLOT(AddedOutput1()));

    ComplexLogger *ComplexLoggerResults2 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults2 = new FileLogger(ComplexLoggerResults2);
    QString FileName2 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle2().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName2(FileName2);
    FileLoggerResults2->SetFileName(FileName2);
    PlainTextLogger * PlainTextLoggerResults2 = new PlainTextLogger(ComplexLoggerResults2);
    PlainTextLoggerResults2->SetPlainTextElement(Output->GetOutput(1));
    ComplexLoggerResults2->AddLogger(FileLoggerResults2);
    ComplexLoggerResults2->AddLogger(PlainTextLoggerResults2);
    connect(ComplexLoggerResults2, SIGNAL(NewLine()), this, SLOT(AddedOutput2()));

    ComplexLogger *ComplexLoggerResults3 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults3 = new FileLogger(ComplexLoggerResults3);
    QString FileName3 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle3().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName3(FileName3);
    FileLoggerResults3->SetFileName(FileName3);
    PlainTextLogger * PlainTextLoggerResults3 = new PlainTextLogger(ComplexLoggerResults3);
    PlainTextLoggerResults3->SetPlainTextElement(Output->GetOutput(2));
    ComplexLoggerResults3->AddLogger(FileLoggerResults3);
    ComplexLoggerResults3->AddLogger(PlainTextLoggerResults3);
    connect(ComplexLoggerResults3, SIGNAL(NewLine()), this, SLOT(AddedOutput3()));

    ComplexLogger *ComplexLoggerResults4 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults4 = new FileLogger(ComplexLoggerResults4);
    QString FileName4 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle4().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName4(FileName4);
    FileLoggerResults4->SetFileName(FileName4);
    PlainTextLogger * PlainTextLoggerResults4 = new PlainTextLogger(ComplexLoggerResults4);
    PlainTextLoggerResults4->SetPlainTextElement(Output->GetOutput(3));
    ComplexLoggerResults4->AddLogger(FileLoggerResults4);
    ComplexLoggerResults4->AddLogger(PlainTextLoggerResults4);
    connect(ComplexLoggerResults4, SIGNAL(NewLine()), this, SLOT(AddedOutput4()));

    ComplexLogger *ComplexLoggerResults5 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults5 = new FileLogger(ComplexLoggerResults5);
    QString FileName5 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle5().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName5(FileName5);
    FileLoggerResults5->SetFileName(FileName5);
    PlainTextLogger * PlainTextLoggerResults5 = new PlainTextLogger(ComplexLoggerResults5);
    PlainTextLoggerResults5->SetPlainTextElement(Output->GetOutput(4));
    ComplexLoggerResults5->AddLogger(FileLoggerResults5);
    ComplexLoggerResults5->AddLogger(PlainTextLoggerResults5);
    connect(ComplexLoggerResults5, SIGNAL(NewLine()), this, SLOT(AddedOutput5()));

    ComplexLogger *ComplexLoggerResults6 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults6 = new FileLogger(ComplexLoggerResults6);
    QString FileName6 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle6().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName6(FileName6);
    FileLoggerResults6->SetFileName(FileName6);
    PlainTextLogger * PlainTextLoggerResults6 = new PlainTextLogger(ComplexLoggerResults6);
    PlainTextLoggerResults6->SetPlainTextElement(Output->GetOutput(5));
    ComplexLoggerResults6->AddLogger(FileLoggerResults6);
    ComplexLoggerResults6->AddLogger(PlainTextLoggerResults6);
    connect(ComplexLoggerResults6, SIGNAL(NewLine()), this, SLOT(AddedOutput6()));

    ComplexLogger *ComplexLoggerResults7 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults7 = new FileLogger(ComplexLoggerResults7);
    QString FileName7 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle7().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName7(FileName7);
    FileLoggerResults7->SetFileName(FileName7);
    PlainTextLogger * PlainTextLoggerResults7 = new PlainTextLogger(ComplexLoggerResults7);
    PlainTextLoggerResults7->SetPlainTextElement(Output->GetOutput(6));
    ComplexLoggerResults7->AddLogger(FileLoggerResults7);
    ComplexLoggerResults7->AddLogger(PlainTextLoggerResults7);
    connect(ComplexLoggerResults7, SIGNAL(NewLine()), this, SLOT(AddedOutput7()));

    ComplexLogger *ComplexLoggerResults8 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults8 = new FileLogger(ComplexLoggerResults8);
    QString FileName8 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle8().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName8(FileName8);
    FileLoggerResults8->SetFileName(FileName8);
    PlainTextLogger * PlainTextLoggerResults8 = new PlainTextLogger(ComplexLoggerResults8);
    PlainTextLoggerResults8->SetPlainTextElement(Output->GetOutput(7));
    ComplexLoggerResults8->AddLogger(FileLoggerResults8);
    ComplexLoggerResults8->AddLogger(PlainTextLoggerResults8);
    connect(ComplexLoggerResults8, SIGNAL(NewLine()), this, SLOT(AddedOutput8()));

    ComplexLogger *ComplexLoggerResults9 = new ComplexLogger(worker);
    FileLogger *FileLoggerResults9 = new FileLogger(ComplexLoggerResults9);
    QString FileName9 = QDir::cleanPath(LogLocation + QDir::separator() + QString("%2/%1.txt").arg(datestringfile).arg(Output->GetOutputTitle9().GetTranslation("en").replace(QRegExp("\\s"),".").replace(QRegExp("[^a-zA-Z1-9]"),"")));
    Output->SetFileName9(FileName9);
    FileLoggerResults9->SetFileName(FileName9);
    PlainTextLogger * PlainTextLoggerResults9 = new PlainTextLogger(ComplexLoggerResults9);
    PlainTextLoggerResults9->SetPlainTextElement(Output->GetOutput(8));
    ComplexLoggerResults9->AddLogger(FileLoggerResults9);
    ComplexLoggerResults9->AddLogger(PlainTextLoggerResults9);
    connect(ComplexLoggerResults9, SIGNAL(NewLine()), this, SLOT(AddedOutput9()));




    Output->SetOutputVisible1(loader.GetOutputVisible1());
    Output->SetOutputVisible2(loader.GetOutputVisible2());
    Output->SetOutputVisible3(loader.GetOutputVisible3());
    Output->SetOutputVisible4(loader.GetOutputVisible4());
    Output->SetOutputVisible5(loader.GetOutputVisible5());
    Output->SetOutputVisible6(loader.GetOutputVisible6());
    Output->SetOutputVisible7(loader.GetOutputVisible7());
    Output->SetOutputVisible8(loader.GetOutputVisible8());
    Output->SetOutputVisible9(loader.GetOutputVisible9());


    Output->SetConfiguratorVisible(false);


    worker->SetResults1(ComplexLoggerResults1);
    worker->SetResults2(ComplexLoggerResults2);
    worker->SetResults3(ComplexLoggerResults3);
    worker->SetResults4(ComplexLoggerResults4);
    worker->SetResults5(ComplexLoggerResults5);
    worker->SetResults6(ComplexLoggerResults6);
    worker->SetResults7(ComplexLoggerResults7);
    worker->SetResults8(ComplexLoggerResults8);
    worker->SetResults9(ComplexLoggerResults9);



    ui->Results->clear();

    ComplexLogger *ComplexLoggerLog = new ComplexLogger(worker);
    FileLogger *FileLoggerLog = new FileLogger(ComplexLoggerLog);
    LogFileName = QDir::cleanPath(LogLocation + QDir::separator() + QString("log/%1.txt").arg(datestringfile));
    FileLoggerLog->SetFileName(LogFileName);
    PlainTextLogger * PlainTextLoggerLog = new PlainTextLogger(ComplexLoggerLog);
    PlainTextLoggerLog->SetPlainTextElement(ui->Results);
    PlainTextLoggerLog->SetReplaceActionIdWithColor();

    ComplexLoggerLog->AddLogger(FileLoggerLog);
    ComplexLoggerLog->AddLogger(PlainTextLoggerLog);



    worker->SetLogger(ComplexLoggerLog);

    worker->SetScript(_Preprocessor->Preprocess(loader.GetScript(),0));

    worker->SetScriptResources(ScriptResources);

    TimeoutWaiterFactory *WaiterFactory = new TimeoutWaiterFactory(worker);
    WaiterFactory->SetMultiWorker(_MultiTimer);
    worker->SetWaiterFactory(WaiterFactory);

    worker->SetSolverFactory(FactorySolver);

    worker->SetEngineResources(EngineRes);

    worker->SetResourceHandlersFactory(new ResourceHandlersFactory(worker));
    worker->SetHttpClientFactory(_HttpClientFactory);
    worker->SetPop3ClientFactory(_Pop3ClientFactory);
    worker->SetImapClientFactory(_ImapClientFactory);
    worker->SetCsvHelper(_CsvHelper);
    worker->SetDatabaseConnector(_DataBaseConnector3);


    worker->SetScriptSuspender(new ScriptSuspender(worker));
    worker->SetWorkerFactory(new ScriptWorkerFactory(worker));

    connect(worker,SIGNAL(Finished()),this,SLOT(Finished()));
    worker->SetReportData(ReportData);
    Worker = worker;

    Worker->SetDoTrace(false);

    //Modules

    Worker->SetHtmlParserFactory(_HtmlParserFactory);
    Worker->SetHelperFactory(_HelperFactory);

    Worker->AddModule(new MemoryInfo(worker),"MemoryInfo",true,true);

    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(Abort()));
    connect(ui->actionResources_Report,SIGNAL(triggered()),this,SLOT(ResourcesReport()));

    TrayNotifier->Start();


    ui->actionResources_Report->setEnabled(true);
    ui->actionResources_Report->setIcon(QIcon(":/fastexecutescript/images/resources_ok.png"));
    ResVisualizer->SetEnabled();
    //Run Worker

    worker->SetProperties(new Properties(worker));


    #ifdef ONLY_REMOTE
       CheckLicense * Checker = new CheckLicense(worker);
       Checker->Preprocessor = _Preprocessor;
       Checker->Data = ContentLoader.GetData();
       Checker->MultiWorker = worker;
       Checker->MachineIdObtainer = MachineIdObtainer;
       Checker->Salt = ContentLoader.GetSalt();
       Checker->Start();
    #endif

    _ModuleManager->StartAllDlls();

    QTimer::singleShot(50,worker,SLOT(Run()));
    //worker->Run();

    if(!IsSilent)
        this->show();

}


void MainWindow::ResourcesReportStateChanged(bool IsEmpty)
{
    if(ui->actionResources_Report->isEnabled())
    {
        if(IsEmpty)
            ui->actionResources_Report->setIcon(QIcon(":/fastexecutescript/images/resources_error.png"));
        else
            ui->actionResources_Report->setIcon(QIcon(":/fastexecutescript/images/resources_ok.png"));
    }
}


void MainWindow::ResourcesReport()
{
    ResVisualizer->ShowReport();
}



void MainWindow::ChooseLanguage()
{
    ScriptLanguageChooserDialog LangDialog;
    LangDialog.ChangesWillTakeEffectAfterRestart();
    LangDialog.SetLang(Language);
    LangDialog.SetLanguageModel(LangModel);
    if(LangDialog.exec())
    {
        Language = LangDialog.GetLang();
        Settings->setValue("DefaultLanguageScript",Language);
        //ShowData();
    }

}

void MainWindow::ChooseLogLocation()
{
    LogLocationChooser Dialog;

    Dialog.SetLogLocation(LogLocation);

    if(Dialog.exec())
    {
        LogLocation = Dialog.GetLogLocation();
        Settings->setValue("LogLocation",LogLocation);
    }
}

void MainWindow::ShowDatabase()
{
    if(!_DatabaseAdmin)
    {
        _DatabaseAdmin = new DatabaseAdmin();
        _DatabaseAdmin->SetDatabaseConnector(_DataBaseConnector);
    }


    QDialog d;
    QHBoxLayout *l = new QHBoxLayout(&d);
    l->setMargin(0);
    d.setLayout(l);
    d.resize(_DatabaseAdmin->width(),_DatabaseAdmin->height());
    d.layout()->addWidget(_DatabaseAdmin);

    _DatabaseAdmin->Show();
    d.exec();
    _DatabaseAdmin->setParent(0);
    if(Ask)
        Ask->show();

}

void MainWindow::ShowData()
{
    bool NeedToUseAdditionalSettings = Settings->value("RenderMethodVisible","false").toString().toLower() == "true";
    Ask->ClearContentWidget();

    //Load current model to dialog
    if(UserWidgetControllerPointer)
        delete UserWidgetControllerPointer;
    UserWidgetControllerPointer = new QtResourceController();

    AdvancedHider * Hider = new AdvancedHider(UserWidgetControllerPointer);
    Hider->SetAskUserForResourcesDialog(Ask);
    connect(UserWidgetControllerPointer,SIGNAL(NewResourceWidget(IResourceWidget*)),Hider,SLOT(InsertResourceWidget(IResourceWidget*)));
    connect(UserWidgetControllerPointer,SIGNAL(WidgetGenerationDone()),Hider,SLOT(HideAdvanced()));

    Ask->SetValidator(UserWidgetControllerPointer->GetValidator());
    UserWidgetControllerPointer->SetLanguage(Language);
    UserWidgetControllerPointer->SetLanguageModel(LangModel);

    UserWidgetControllerPointer->SetIncludeSections(true);

    ResourceUserWidgetFactory *f = new ResourceUserWidgetFactory(UserWidgetControllerPointer);
    f->SetStringBuilder(StringBuild);
    f->SetDatabaseState(_DataBaseState);
    UserWidgetControllerPointer->SetResourceWidgetFactory(f);
    UserWidgetControllerPointer->SetWidget(Ask->GetContentWidget());

    Res->FromModelToView(UserWidgetControllerPointer);

    if(NeedToUseAdditionalSettings)
        Ask->GetContentWidget()->layout()->addWidget(AdditionalSettings->GetWidget());
}


void MainWindow::SetDefault()
{
    XmlResourceController loader;
    if(LastLoaderResult.isEmpty())
    {
        #ifndef ONLY_REMOTE
            //Load from file
            loader.SetFileName("project.xml");
        #endif
    }else
    {
        loader.SetFileContent(LastLoaderResult);
    }
    Res->FromViewToModel(&loader);

    ShowData();
}

void MainWindow::SaveActual(const QString& filename)
{
    XmlResourceController XmlActualStatic;
    XmlResourceController *XmlActual = &XmlActualStatic;

    XmlActual->SetFileName(filename);

    Resources UserRes;
    UserRes.FromViewToModel(UserWidgetControllerPointer);
    UserRes.FromModelToView(XmlActual);

    Resources ResDefaults;
    XmlResourceController loader;
    if(LastLoaderResult.isEmpty())
    {
        #ifndef ONLY_REMOTE
            //Load from file
            loader.SetFileName("project.xml");
        #endif
    }else
    {
        loader.SetFileContent(LastLoaderResult);
    }

    ResDefaults.FromViewToModel(&loader);
    XmlResourceController XmlDefaults;
    XmlDefaults.SetFileName(filename + ".default.xml");
    ResDefaults.FromModelToView(&XmlDefaults);

}

void MainWindow::LoadActual(const QString& filename)
{
    XmlResourceController XmlActualStatic;
    XmlResourceController *XmlActual = &XmlActualStatic;

    XmlActual->SetFileName(filename);

    Resources ResActual;
    ResActual.FromViewToModel(XmlActual);

    Resources ResDefault;
    XmlResourceController XmlDefaults;
    XmlDefaults.SetFileName(filename + ".default.xml");
    ResDefault.FromViewToModel(&XmlDefaults);

    CopyResourceController Copy;
    Copy.SetResources(&ResActual);
    Copy.SetDefaults(&ResDefault);

    Res->FromViewToModel(&Copy);
    ShowData();

}


void MainWindow::AddedOutput1()
{
    Output->AddedOutput(0);
}

void MainWindow::AddedOutput2()
{
    Output->AddedOutput(1);
}

void MainWindow::AddedOutput3()
{
    Output->AddedOutput(2);
}

void MainWindow::AddedOutput4()
{
    Output->AddedOutput(3);
}

void MainWindow::AddedOutput5()
{
    Output->AddedOutput(4);
}

void MainWindow::AddedOutput6()
{
    Output->AddedOutput(5);
}

void MainWindow::AddedOutput7()
{
    Output->AddedOutput(6);
}

void MainWindow::AddedOutput8()
{
    Output->AddedOutput(7);
}

void MainWindow::AddedOutput9()
{
    Output->AddedOutput(8);
}

void MainWindow::InitRecources()
{
    _HttpClientFactory = new HttpClientFactory(this);
    _Pop3ClientFactory = new Pop3ClientFactory(this);
    _ImapClientFactory = new ImapClientFactory(this);
    _HtmlParserFactory = new HtmlParserFactory(this);
    _HelperFactory = new HelperFactory(this);

    Res = new Resources(this);
    StringBuild = new BrowserAutomationStudioFramework::StringBuilder(this);
    StringBuild->AddFromSettings(":/engine/text/strings.ini",QStringList()<<"RFemName"<<"TFemName"<<"RMaleName"<<"TMaleName"<<"RSurname"<<"TSurname");



    EngineRes = new EngineResources(Res);
    ScriptResources = new ScriptResourcesFromQt(this);

    EngineResController = new EngineResourceController(Res);
    TimeoutWaiterFactory *WaiterFactory = new TimeoutWaiterFactory(Res);
    WaiterFactory->SetMultiWorker(_MultiTimer);
    EngineResController->SetWaiterFactory(WaiterFactory);
    EngineResController->SetHttpClientFactory(_HttpClientFactory);
    EngineResController->SetEngineResources(EngineRes);
    EngineResController->SetStringBuilder(StringBuild);
    EngineResController->SetDatabaseConnector(_DataBaseConnector3);
    EngineResController->SetCsvHelper(_CsvHelper);

    EngineRes->SetEngineResourcesController(EngineResController);
    EngineRes->SetResources(Res);


}

void MainWindow::InitWidgets()
{
    Output = new OutputSection(this);
    Output->SetLanguageModel(LangModel);
    ui->ResultsLayout->addWidget(Output->GetWidget());


    SolverFactory *fs = new SolverFactory(this);
    fs->SetHttpClientFactory(_HttpClientFactory);

    ManualCaptchaSolver *cw = qobject_cast<ManualCaptchaSolver *>(fs->GetSolver("manual"));
    FactorySolver = fs;
    connect(fs,SIGNAL(UsedSolver(QString)),Output,SLOT(UsedSolver(QString)));
    connect(cw,SIGNAL(ChangedSize(int)),this,SLOT(UpdateCaptchaSize(int)));


}

void MainWindow::Restart()
{
    NeedRestart = true;

}


void MainWindow::Close()
{
    IsClosingWindow = true;
    if(Worker)
        Worker->Abort();
    close();

}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!IsClosingWindow)
    {
        hide();
        if(!AlreadyShowsMessage)
        {
            TrayNotifier->ShowMessage(tr("Application is still running"),tr("Use exit menu item to shut it down"));
            AlreadyShowsMessage = true;
        }
        event->ignore();

    }else
    {
        hide();
        this->deleteLater();
        
        if(NeedRestart)
        {
            MainWindow *w = new MainWindow();
            if(IsSilent)
                w->SetIsSilent();
            w->SetDatabaseConnector(_DataBaseConnector,_DataBaseConnector2,_DataBaseConnector3,_DataBaseState, _CsvHelper);
            _DataBaseConnector->setParent(w);
            _DataBaseConnector3->setParent(w);
            _DataBaseState->setParent(w);
            QObject *d = new QObject(this);
            
            connect(d,SIGNAL(destroyed()),w,SLOT(Start()));
        }else
        {
            qApp->setQuitOnLastWindowClosed(true);
        }



    }
}

void MainWindow::InitBrowserList(const QString& WrokerType)
{

    {
        SubprocessBrowserFactory *sf = new SubprocessBrowserFactory(this);
        connect(sf,SIGNAL(OnBrowserCreated()),this,SLOT(ShowBrowserPanel()));
        sf->SetLanguage(Language);
        ProcessComunicatorFactory *cf = new ProcessComunicatorFactory(sf);
        cf->SetCommandLineParams(QStringList()<<"%keyin%"<<"%keyout%"<<"%pid%");

        sf->SetProcessComunicatorFactory(cf);
        sf->SetNetworkAccessManager(new SubprocessNetworkAccessManagerFactory(this));
        ui->BrowserLayout->insertWidget(0,sf->GetWidget(false));
        BrowserFactory = sf;
    }
    ui->splitter->setSizes(QList<int>()<<0<<this->height());
}

void MainWindow::ShowBrowserPanel()
{
    if(!AlreadyShowedBrowserPanel)
    {
        AlreadyShowedBrowserPanel = true;
        ui->splitter->setSizes(QList<int>()<<this->height()/3<<2*this->height()/3);
    }
}


void MainWindow::Finished()
{
    _ModuleManager->StopAllDlls();
    ResVisualizer->SetDisabled();
    ui->actionResources_Report->setEnabled(false);
    ui->actionResources_Report->setIcon(QIcon(":/fastexecutescript/images/resources_ok.png"));
    ui->actionStop->setEnabled(false);
    ui->LabelGif->setVisible(false);
    ui->LabelRunning->setVisible(false);
    TrayNotifier->Stop();
    sender()->deleteLater();
    Worker = 0;
    movie->stop();
    if(IsSilent)
    {
        QTimer::singleShot(50,this,SLOT(Close()));
        return;
    }

    if(!IsClosingWindow)
        DataVisualizer->ShowReport();
}

void MainWindow::UpdateCaptchaSize(int size)
{
    if(!CaptchaWidgetPresent)
    {
        CaptchaWidgetPresent = true;
        ManualCaptchaSolver *cw = qobject_cast<ManualCaptchaSolver *>(FactorySolver->GetSolver("manual"));


        QWidget *w = new QWidget(ui->tabWidget);

        QVBoxLayout *l = new QVBoxLayout(w);
        w->setLayout(l);

        l->addWidget(cw->GetWidget());
        ui->tabWidget->addTab(w,"Captcha");
    }

    QString text = QString(tr("Captcha (%1)")).arg(size);
    ui->tabWidget->setTabText (2, text);

    _TabBlink->SetText(text.split(" ").first());
    if(size > 0)
        _TabBlink->Start();
    else
        _TabBlink->Stop();
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::LogMenu_Click()
{
    QPoint globalPos = LogMenuButton->mapToGlobal(QPoint(0,LogMenuButton->height()));

    QMenu myMenu;
    myMenu.setStyleSheet("QMenu{background-color:#353535} QMenu::item:selected{color:black;background-color:#c663ff} ");
    QAction * AllLogAction = myMenu.addAction(QString(tr("All log")));
    QAction * ClearLogAction = myMenu.addAction(QString(tr("Clear log")));

    QAction *res = myMenu.exec(globalPos);
    if(AllLogAction == res)
    {
        QFileInfo info(LogFileName);
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
    }
    if(ClearLogAction == res)
    {
        if(Worker)
            Worker->GetLogger()->Clear();
        ui->Results->setHtml("");
    }
}

void MainWindow::changeEvent(QEvent *e)
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
