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
    ~CompileWindow();

private:
    Ui::CompileWindow *ui;
private slots:
    void Accepted();
};

#endif // COMPILEWINDOW_H
