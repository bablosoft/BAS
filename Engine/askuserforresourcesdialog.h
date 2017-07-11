#ifndef ASKUSERFORRESOURCESDIALOG_H
#define ASKUSERFORRESOURCESDIALOG_H
#include "engine_global.h"
#include "ivalidator.h"
#include <QDialog>

namespace Ui {
class AskUserForResourcesDialog;
}
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT AskUserForResourcesDialog : public QDialog
    {
        Q_OBJECT
        QWidget *Widget;
        IValidator *Validator;
        bool IsAdvanced;
        QPushButton *DatabaseButton;
        QAction *Advanced;
    public:
        explicit AskUserForResourcesDialog(int width, int height, QWidget *parent = 0);
        ~AskUserForResourcesDialog();
        QWidget *GetContentWidget();
        void ClearContentWidget();
        void SetValidator(IValidator *Validator);
        virtual void done(int r);
        QPushButton * AddResetButton();
        void RemoveLanguageChooser();
        void HideDatabaseButton();

    private:
        Ui::AskUserForResourcesDialog *ui;
        void changeEvent(QEvent *e);
    signals:
        void Default();
        void Load(const QString& FileName);
        void Save(const QString& FileName);
        void ShowLanguage();
        void Reset();

        void ShowAdvanced();
        void ShowDatabase();
        void HideAdvanced();
        void ShowLogLocation();
    private slots:

        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_4_clicked();
        void on_pushButton_5_clicked();
        void on_pushButton_6_clicked();
    };
}

#endif // ASKUSERFORRESOURCESDIALOG_H
