#ifndef COMPILEWINDOW_H
#define COMPILEWINDOW_H

#include <QDialog>
#include "compiler.h"
namespace Ui {
class CompileWindow;
}

class CompileWindow : public QDialog
{
    Q_OBJECT
    Compiler *compiler;
public:
    explicit CompileWindow(Compiler *compiler,QWidget *parent = 0);
    void GuiUpdate();
    ~CompileWindow();

private:
    Ui::CompileWindow *ui;
private slots:
    void Accepted();
    void Resize();
    void on_NoProtection_clicked();
    void on_PrivateScriptUserEnterPass_clicked();
    void on_PrivateScriptEnterPassForUser_clicked();
};

#endif // COMPILEWINDOW_H
