#ifndef VOCABULARYTEST_H
#define VOCABULARYTEST_H
#include "engine_global.h"

#include <QDialog>
#include "istringbuilder.h"

namespace Ui {
class VocabularyTest;
}

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT VocabularyTest : public QDialog
    {
        Q_OBJECT
        IStringBuilder* StringBuilder;
    public:
        explicit VocabularyTest(QWidget *parent = 0);
        void SetStringBuilder(IStringBuilder *StringBuilder);
        ~VocabularyTest();
    signals:
        void Changed(const QString& str);
    private:
        Ui::VocabularyTest *ui;
        void changeEvent(QEvent *e);
    public slots:
        void SetText(const QString& str);
    private slots:
        void on_pushButton_clicked();
        void on_TestButton_clicked();
    };
}

#endif // VOCABULARYTEST_H
