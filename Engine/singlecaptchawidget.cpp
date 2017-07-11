#include "singlecaptchawidget.h"
#include "ui_singlecaptchawidget.h"
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    SingleCaptchaWidget::SingleCaptchaWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SingleCaptchaWidget)
    {
        ui->setupUi(this);
    }

    SingleCaptchaWidget::~SingleCaptchaWidget()
    {
        delete ui;
    }

    void SingleCaptchaWidget::SetCaptcha(const QString& base64,const QString& id)
    {
        this->id = id;
        if(base64.startsWith("BAS_USER_ASK"))
        {
            QString lab = base64;

            lab = lab.remove(0,12);
            ui->Picture->setText(lab);
            ui->Picture->show();
            ui->Picture->setWordWrap(true);
            ui->Picture->setTextInteractionFlags(Qt::TextSelectableByMouse);
            update();
        }else
        {
            QPixmap p;
            QByteArray array;
            QByteArray temp = QByteArray();
            temp.append(base64);
            array = array.fromBase64(temp);
            if(p.loadFromData(array))
            {
                int w = p.width();
                int h = p.height() + 25;
                if(w<150)
                    w = 150;
                if(h<90)
                    h = 90;

                this->setMinimumWidth(w);
                this->setMinimumHeight(h);
                this->setMaximumWidth(w);
                this->setMaximumHeight(h);
                ui->Picture->setPixmap(p);
                ui->Picture->show();
                update();
            }
        }
    }


    void SingleCaptchaWidget::on_pushButton_2_clicked()
    {
        emit Done("Closed by user",id,false);
        this->deleteLater();
    }

    void SingleCaptchaWidget::on_pushButton_clicked()
    {
        emit Done(ui->lineEdit->text(),id,true);
        this->deleteLater();
    }

    void SingleCaptchaWidget::on_lineEdit_returnPressed()
    {
        emit Done(ui->lineEdit->text(),id,true);
        this->deleteLater();
    }

    void SingleCaptchaWidget::changeEvent(QEvent *e)
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

}
