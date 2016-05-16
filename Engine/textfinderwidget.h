#ifndef TEXTFINDERWIDGET_H
#define TEXTFINDERWIDGET_H

#include <QWidget>
#include "engine_global.h"

namespace Ui {
class TextFinderWidget;
}

class ENGINESHARED_EXPORT TextFinderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextFinderWidget(QWidget *parent = 0);
    ~TextFinderWidget();


public slots:
    void Show();
signals:
    void TermChanged(const QString& Term);
    void FindNext(bool Direction);

private slots:
    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TextFinderWidget *ui;
};

#endif // TEXTFINDERWIDGET_H
