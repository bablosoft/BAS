#ifndef OUTPUTSECTION_H
#define OUTPUTSECTION_H
#include "engine_global.h"

#include <QObject>
#include <QTextBrowser>
#include "outputwidget.h"
#include "multilanguagestring.h"
#include "ilanguagemodel.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT OutputSection : public QObject
    {
        Q_OBJECT
        OutputWidget* WidgetOutput;
    public:
        explicit OutputSection(QObject *parent = 0);
        QTextBrowser *GetOutput(int number);
        QWidget *GetWidget();

    signals:

    public slots:
        void SetFileName1(const QString& FileName1);
        void SetFileName2(const QString& FileName2);
        void SetFileName3(const QString& FileName3);
        void SetFileName4(const QString& FileName4);
        void SetFileName5(const QString& FileName5);
        void SetFileName6(const QString& FileName6);
        void SetFileName7(const QString& FileName7);
        void SetFileName8(const QString& FileName8);
        void SetFileName9(const QString& FileName9);

        void Success();
        void Failed();
        void UsedSolver(const QString &Solver);
        void Finished();
        void AddedOutput(int number);
        void Clear();
        void ProgressValue(int value);
        void ProgressMaximum(int maximum);
        MultiLanguageString GetOutputTitle1();
        MultiLanguageString GetOutputTitle2();
        MultiLanguageString GetOutputTitle3();
        MultiLanguageString GetOutputTitle4();
        MultiLanguageString GetOutputTitle5();
        MultiLanguageString GetOutputTitle6();
        MultiLanguageString GetOutputTitle7();
        MultiLanguageString GetOutputTitle8();
        MultiLanguageString GetOutputTitle9();
        bool GetOutputVisible1();
        bool GetOutputVisible2();
        bool GetOutputVisible3();
        bool GetOutputVisible4();
        bool GetOutputVisible5();
        bool GetOutputVisible6();
        bool GetOutputVisible7();
        bool GetOutputVisible8();
        bool GetOutputVisible9();

        void SetOutputTitle1(const MultiLanguageString& OutputTitle1);
        void SetOutputTitle2(const MultiLanguageString& OutputTitle2);
        void SetOutputTitle3(const MultiLanguageString& OutputTitle3);
        void SetOutputTitle4(const MultiLanguageString& OutputTitle4);
        void SetOutputTitle5(const MultiLanguageString& OutputTitle5);
        void SetOutputTitle6(const MultiLanguageString& OutputTitle6);
        void SetOutputTitle7(const MultiLanguageString& OutputTitle7);
        void SetOutputTitle8(const MultiLanguageString& OutputTitle8);
        void SetOutputTitle9(const MultiLanguageString& OutputTitle9);
        void SetOutputVisible1(bool OutputVisible1);
        void SetOutputVisible2(bool OutputVisible2);
        void SetOutputVisible3(bool OutputVisible3);
        void SetOutputVisible4(bool OutputVisible4);
        void SetOutputVisible5(bool OutputVisible5);
        void SetOutputVisible6(bool OutputVisible6);
        void SetOutputVisible7(bool OutputVisible7);
        void SetOutputVisible8(bool OutputVisible8);
        void SetOutputVisible9(bool OutputVisible9);
        void SetConfiguratorVisible(bool Visible);
        void SetDefaults();
        void SetLanguageModel(ILanguageModel* LanguageModel);
    };
}

#endif // OUTPUTSECTION_H
