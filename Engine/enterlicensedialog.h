#ifndef ENTERLICENSEDIALOG_H
#define ENTERLICENSEDIALOG_H
#include "engine_global.h"

#include <QDialog>
#include <QSettings>
#include <QHash>
#include <QUrl>

namespace Ui {
class EnterLicenseDialog;
}

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EnterLicenseDialog : public QDialog
    {
        Q_OBJECT
        QSettings *Settings;
        QString FileName;
        QString Language;
        QString LastSelectedScript;
        QPushButton *NeedAKeyButton;
        QString PromoLink;
        int HeightTotal;
        int WidthTotal;
        struct ScriptData{QString Description;QString Link;QString Version;bool IsFree = false;};
        QHash<QString,ScriptData> Scripts;
        QString AddSpacesToScriptName(const QString& ScriptName,const QString& Version);
        void SetScriptData(const ScriptData& Data);
        QPushButton * DataButton;
    public:
        explicit EnterLicenseDialog(QWidget *parent = 0);
        ~EnterLicenseDialog();
        QString GetEmail();
        QString GetPassword();
        QString GetScriptId();
        void SetProjectFile(const QString& FileName);
        void SetLanguage(const QString& Language);
        void Init();
        void HideDatabaseButton();

    private:

        Ui::EnterLicenseDialog *ui;
        void changeEvent(QEvent *e);
    signals:
        void ShowDatabase();
    private slots:
        void LinkClicked(QUrl url);
        void NeedAKeyClicked();
        void Accepted();
        void UpdateDescription(const QString & Text);
    };
}

#endif // ENTERLICENSEDIALOG_H
