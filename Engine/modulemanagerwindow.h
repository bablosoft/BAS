#ifndef MODULEMANAGERWINDOW_H
#define MODULEMANAGERWINDOW_H

#include <QDialog>
#include "imodulemanager.h"
#include "engine_global.h"


namespace Ui {
class ModuleManagerWindow;
}

using namespace BrowserAutomationStudioFramework;

class ENGINESHARED_EXPORT ModuleManagerWindow : public QDialog
{
    Q_OBJECT
    IModuleManager * ModuleManager;
public:
    explicit ModuleManagerWindow(QWidget *parent = 0);
    void SetModuleManager(IModuleManager *ModuleManager);
    void Reload();


    ~ModuleManagerWindow();

private slots:
    void on_Close_clicked();

    void on_Reload_clicked();
    void LabelClicked();
    void CheckBoxClicked();

    void on_DeselectAll_clicked();

    void on_SelectAll_clicked();

private:
    Ui::ModuleManagerWindow *ui;
};

#endif // MODULEMANAGERWINDOW_H
