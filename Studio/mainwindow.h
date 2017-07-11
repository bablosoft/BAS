#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include "isolverfactory.h"
#include "imultiworker.h"
#include "resources.h"
#include "qtresourcecontroller.h"
#include "iscriptresources.h"
#include "engineresources.h"
#include "engineresourcecontroller.h"
#include "stringbuilder.h"
#include <QSettings>
#include "compiler.h"
#include "ihttpclientfactory.h"
#include "ipop3clientfactory.h"
#include "outputsection.h"
#include "isystemtraynotifier.h"
#include <QPushButton>
#include "askuserforresourcesdialog.h"
#include "additionalsettingswidgets.h"
#include "scriptmultiworkerreportdata.h"
#include "reportdatavisualizer.h"
#include "resourcesvisualizer.h"
#include "ilanguagemodel.h"
#include "translator.h"
#include "imapclientfactory.h"
#include "icodeeditor.h"
#include "textfinderwidget.h"
#include "ihtmlparserfactory.h"
#include "ihelperfactory.h"
#include "multitimer.h"
#include "databaseadmin.h"
#include "mongodatabaseconnector.h"
#include "csvhelper.h"
#include "databasestate.h"
#include "recordprocesscommunication.h"
#include "modulemanager.h"
#include "diffpatcher.h"
#include "mainwindowtabblink.h"

namespace Ui {
    class MainWindow;
}
using namespace BrowserAutomationStudioFramework;
class MainWindow : public QMainWindow {
    Q_OBJECT
    ICodeEditor *TextEditor;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    DiffPatcher _DiffPatcher;
    MultiTimer *_MultiTimer;
    QString LogFileName;
    OutputSection *Output;
    IBrowserFactory *BrowserFactory;
    ISolverFactory *FactorySolver;
    Resources *Res;
    QSettings *Settings;
    QtResourceController *WidgetController;
    EngineResources *EngineRes;
    EngineResourceController *EngineResController;
    BrowserAutomationStudioFramework::StringBuilder *StringBuild;
    IMultiWorker * Worker;
    QString CurrentFileName;
    IScriptResources* ScriptResources;
    TextFinderWidget* _TextFinderWidget;
    DatabaseAdmin *_DatabaseAdmin;
    MongoDatabaseConnector *_DataBaseConnector;
    MongoDatabaseConnector *_DataBaseConnector2;
    MongoDatabaseConnector *_DataBaseConnector3;
    DatabaseState *_DataBaseState;
    RecordProcessCommunication *_RecordProcessCommunication;
    MainWindowTabBlink *_TabBlink;
    QString Schema;
    QString DatabaseId;
    bool ConnectionIsRemote;
    QString ConnectionServer;
    QString ConnectionPort;
    QString ConnectionLogin;
    QString ConnectionPassword;
    bool IsDatabaseDirty;

    QList<IRecordProcessCommunication::ResourceDescription> LastResourceList;

    CsvHelper *_CsvHelper;
    void closeEvent(QCloseEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    Compiler *compiler;
    IHttpClientFactory * _HttpClientFactory;
    IPop3ClientFactory * _Pop3ClientFactory;
    IImapClientFactory * _ImapClientFactory;
    IHtmlParserFactory *_HtmlParserFactory;
    IHelperFactory *_HelperFactory;
    QMovie *movie;
    ISystemTrayNotifier *TrayNotifier;
    QPushButton * LogMenuButton;
    QString LogLocation;


    AskUserForResourcesDialog *Ask;
    AdditionalSettingsWidgets *AdditionalSettings;
    QtResourceController *UserWidgetControllerPointer;
    QDockWidget *dockWidgetCaptcha;

    ILanguageModel *LangModel;
    QString LanguageScript, LanguageInterface;
    Translator TranslateEngine;
    Translator TranslateStudio;

    ModuleManager *_ModuleManager;


    //Reports
    bool AlreadyShowsMessage;
    ScriptMultiWorkerReportData *ReportData;
    ReportDataVisualizer *DataVisualizer;
    ResourcesVisualizer *ResVisualizer;
    bool IsClosingWindow;

    bool IsRecordLast;
    bool NeedRestart;
    bool IsModified;

private:
    Ui::MainWindow *ui;


private slots:
    void InitBrowserList(const QString& WrokerType, bool IsRecord);
    void AddedOutput1();
    void AddedOutput2();
    void AddedOutput3();
    void AddedOutput4();
    void AddedOutput5();
    void AddedOutput6();
    void AddedOutput7();
    void AddedOutput8();
    void AddedOutput9();
    void Run();
    void Record();
    void RunInternal(bool IsRecord);
    void Compile();
    void New();
    void Open();
    void Show();
    bool SavePrevious();
    void Close();
    void CloseNoSave();
    void ResourcesReport();
    QString OpenFromFile(const QString& fileName);
    void OpenFromFileOrDisplayMessageBox(const QString& fileName);
    void ResourcesNotEmpty();
    void ResourcesEmpty();
    void HighlightAction(QUrl url);

    void SetIsDirty(bool IsDirty);
    void OpenDefault();
    void LoadSchema();
    void Save();
    void AbortInstant();
    void Abort();
    void SaveAs();
    QPair<bool,QString> SaveToFileSilent(const QString& file);
    void SaveToFile(const QString& file);
    void InitAction();
    void InitRecources();
    void InitWidgets();
    void StartAction(const QString& ActionName);
    void StopAction();
    void UpdateCaptchaSize(int size);
    void ClearState();
    void RestoreState();
    void ResourcesReportStateChanged(bool IsEmpty);
    void RestoreMaxHeight();
    void SetCurrentFileName(const QString& CurrentFileName);
    void UpdateTitle();
    void SetModified();
    void SetNotModified();

    void LogMenu_Click();
    void SetDefault();
    void ShowData();
    void ShowDataBaseDialogNoAsk();
    void ShowDataBaseManager();
    void ShowDataBase();
    void ShowDataBaseDialog();
    void SaveActual(const QString& filename);
    void LoadActual(const QString& filename);
    void Documentation();
    void Localization();
    void ChangeScriptLanguage();
    void ChangeInterfaceLanguage();
    void ChooseLogLocation();

    void AboutEngine();
    void RegexpConstructor();
    void FingerprintSwitcher();
    void ShowModuleManager();
    void SetDefaultText();

    void SendCode();
    void ReceiveCode(const QString& Code);
    void SetNeedRestart();

    void on_ButtonAddNewResource_clicked();
};

#endif // MAINWINDOW_H
