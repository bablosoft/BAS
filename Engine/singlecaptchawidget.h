#ifndef SINGLECAPTCHAWIDGET_H
#define SINGLECAPTCHAWIDGET_H
#include "engine_global.h"

#include <QWidget>
namespace Ui {
class SingleCaptchaWidget;
}
namespace BrowserAutomationStudioFramework
{


    class ENGINESHARED_EXPORT SingleCaptchaWidget : public QWidget
    {
        Q_OBJECT
        QString id;
    public:
        explicit SingleCaptchaWidget(QWidget *parent = 0);
        ~SingleCaptchaWidget();
        void SetCaptcha(const QString& base64, const QString& id);

    private:
        Ui::SingleCaptchaWidget *ui;
        void changeEvent(QEvent *e);

    signals:
        void Done(const QString& val, const QString& id, bool res);
    private slots:
        void on_pushButton_2_clicked();
        void on_pushButton_clicked();
        void on_lineEdit_returnPressed();
    };
}

#endif // SINGLECAPTCHAWIDGET_H
