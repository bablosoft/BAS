#include "outputsection.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    OutputSection::OutputSection(QObject *parent) :
        QObject(parent)
    {
        WidgetOutput = new OutputWidget();
    }

    void OutputSection::SetLanguageModel(ILanguageModel* LanguageModel)
    {
        WidgetOutput->SetLanguageModel(LanguageModel);
    }

    QTextBrowser *OutputSection::GetOutput(int number)
    {
        return WidgetOutput->GetOutput(number);
    }

    QWidget *OutputSection::GetWidget()
    {
        return WidgetOutput;
    }

    void OutputSection::Success()
    {
        WidgetOutput->Success();
    }

    void OutputSection::Failed()
    {
        WidgetOutput->Failed();
    }

    void OutputSection::UsedSolver(const QString &Solver)
    {
        WidgetOutput->UsedSolver(Solver);
    }

    void OutputSection::Finished()
    {
        WidgetOutput->Finished();
    }

    void OutputSection::AddedOutput(int number)
    {
        WidgetOutput->AddedOutput(number);
    }

    void OutputSection::Clear()
    {
        WidgetOutput->Clear();
    }

    void OutputSection::ProgressValue(int value)
    {
        WidgetOutput->ProgressValue(value);
    }

    void OutputSection::ProgressMaximum(int maximum)
    {
        WidgetOutput->ProgressMaximum(maximum);
    }

    void OutputSection::SetFileName1(const QString& FileName1)
    {
        WidgetOutput->SetFileName1(FileName1);
    }
    void OutputSection::SetFileName2(const QString& FileName2)
    {
        WidgetOutput->SetFileName2(FileName2);
    }
    void OutputSection::SetFileName3(const QString& FileName3)
    {
        WidgetOutput->SetFileName3(FileName3);
    }
    void OutputSection::SetFileName4(const QString& FileName4)
    {
        WidgetOutput->SetFileName4(FileName4);
    }
    void OutputSection::SetFileName5(const QString& FileName5)
    {
        WidgetOutput->SetFileName5(FileName5);
    }
    void OutputSection::SetFileName6(const QString& FileName6)
    {
        WidgetOutput->SetFileName6(FileName6);
    }
    void OutputSection::SetFileName7(const QString& FileName7)
    {
        WidgetOutput->SetFileName7(FileName7);
    }
    void OutputSection::SetFileName8(const QString& FileName8)
    {
        WidgetOutput->SetFileName8(FileName8);
    }
    void OutputSection::SetFileName9(const QString& FileName9)
    {
        WidgetOutput->SetFileName9(FileName9);
    }

    MultiLanguageString OutputSection::GetOutputTitle1()
    {
        return WidgetOutput->GetOutputTitle1();
    }

    MultiLanguageString OutputSection::GetOutputTitle2()
    {
        return WidgetOutput->GetOutputTitle2();
    }

    MultiLanguageString OutputSection::GetOutputTitle3()
    {
        return WidgetOutput->GetOutputTitle3();
    }

    MultiLanguageString OutputSection::GetOutputTitle4()
    {
        return WidgetOutput->GetOutputTitle4();
    }

    MultiLanguageString OutputSection::GetOutputTitle5()
    {
        return WidgetOutput->GetOutputTitle5();
    }

    MultiLanguageString OutputSection::GetOutputTitle6()
    {
        return WidgetOutput->GetOutputTitle6();
    }

    MultiLanguageString OutputSection::GetOutputTitle7()
    {
        return WidgetOutput->GetOutputTitle7();
    }

    MultiLanguageString OutputSection::GetOutputTitle8()
    {
        return WidgetOutput->GetOutputTitle8();
    }

    MultiLanguageString OutputSection::GetOutputTitle9()
    {
        return WidgetOutput->GetOutputTitle9();
    }

    bool OutputSection::GetOutputVisible1()
    {
        return WidgetOutput->GetOutputVisible1();
    }

    bool OutputSection::GetOutputVisible2()
    {
        return WidgetOutput->GetOutputVisible2();
    }

    bool OutputSection::GetOutputVisible3()
    {
        return WidgetOutput->GetOutputVisible3();
    }

    bool OutputSection::GetOutputVisible4()
    {
        return WidgetOutput->GetOutputVisible4();
    }

    bool OutputSection::GetOutputVisible5()
    {
        return WidgetOutput->GetOutputVisible5();
    }

    bool OutputSection::GetOutputVisible6()
    {
        return WidgetOutput->GetOutputVisible6();
    }

    bool OutputSection::GetOutputVisible7()
    {
        return WidgetOutput->GetOutputVisible7();
    }

    bool OutputSection::GetOutputVisible8()
    {
        return WidgetOutput->GetOutputVisible8();
    }

    bool OutputSection::GetOutputVisible9()
    {
        return WidgetOutput->GetOutputVisible9();
    }



    void OutputSection::SetOutputTitle1(const MultiLanguageString& OutputTitle1)
    {
        WidgetOutput->SetOutputTitle1(OutputTitle1);
    }

    void OutputSection::SetOutputTitle2(const MultiLanguageString& OutputTitle2)
    {
        WidgetOutput->SetOutputTitle2(OutputTitle2);
    }

    void OutputSection::SetOutputTitle3(const MultiLanguageString& OutputTitle3)
    {
        WidgetOutput->SetOutputTitle3(OutputTitle3);
    }

    void OutputSection::SetOutputTitle4(const MultiLanguageString& OutputTitle4)
    {
        WidgetOutput->SetOutputTitle4(OutputTitle4);
    }

    void OutputSection::SetOutputTitle5(const MultiLanguageString& OutputTitle5)
    {
        WidgetOutput->SetOutputTitle5(OutputTitle5);
    }

    void OutputSection::SetOutputTitle6(const MultiLanguageString& OutputTitle6)
    {
        WidgetOutput->SetOutputTitle6(OutputTitle6);
    }

    void OutputSection::SetOutputTitle7(const MultiLanguageString& OutputTitle7)
    {
        WidgetOutput->SetOutputTitle7(OutputTitle7);
    }

    void OutputSection::SetOutputTitle8(const MultiLanguageString& OutputTitle8)
    {
        WidgetOutput->SetOutputTitle8(OutputTitle8);
    }

    void OutputSection::SetOutputTitle9(const MultiLanguageString& OutputTitle9)
    {
        WidgetOutput->SetOutputTitle9(OutputTitle9);
    }


    void OutputSection::SetOutputVisible1(bool OutputVisible1)
    {
        WidgetOutput->SetOutputVisible1(OutputVisible1);
    }

    void OutputSection::SetOutputVisible2(bool OutputVisible2)
    {
        WidgetOutput->SetOutputVisible2(OutputVisible2);
    }

    void OutputSection::SetOutputVisible3(bool OutputVisible3)
    {
        WidgetOutput->SetOutputVisible3(OutputVisible3);
    }

    void OutputSection::SetOutputVisible4(bool OutputVisible4)
    {
        WidgetOutput->SetOutputVisible4(OutputVisible4);
    }

    void OutputSection::SetOutputVisible5(bool OutputVisible5)
    {
        WidgetOutput->SetOutputVisible5(OutputVisible5);
    }

    void OutputSection::SetOutputVisible6(bool OutputVisible6)
    {
        WidgetOutput->SetOutputVisible6(OutputVisible6);
    }

    void OutputSection::SetOutputVisible7(bool OutputVisible7)
    {
        WidgetOutput->SetOutputVisible7(OutputVisible7);
    }

    void OutputSection::SetOutputVisible8(bool OutputVisible8)
    {
        WidgetOutput->SetOutputVisible8(OutputVisible8);
    }

    void OutputSection::SetOutputVisible9(bool OutputVisible9)
    {
        WidgetOutput->SetOutputVisible9(OutputVisible9);
    }

    void OutputSection::SetConfiguratorVisible(bool Visible)
    {
        WidgetOutput->SetConfiguratorVisible(Visible);
    }

    void OutputSection::SetDefaults()
    {
        MultiLanguageString ms1;
        ms1.SetTranslation("en","First Results");
        ms1.SetTranslation("ru","First Results");

        MultiLanguageString ms2;
        ms2.SetTranslation("en","Second Results");
        ms2.SetTranslation("ru","Second Results");

        MultiLanguageString ms3;
        ms3.SetTranslation("en","Third Results");
        ms3.SetTranslation("ru","Third Results");

        MultiLanguageString ms4;
        ms4.SetTranslation("en","Fourth Results");
        ms4.SetTranslation("ru","Fourth Results");

        MultiLanguageString ms5;
        ms5.SetTranslation("en","Fifth Results");
        ms5.SetTranslation("ru","Fifth Results");

        MultiLanguageString ms6;
        ms6.SetTranslation("en","Sixth Results");
        ms6.SetTranslation("ru","Sixth Results");

        MultiLanguageString ms7;
        ms7.SetTranslation("en","Seventh Results");
        ms7.SetTranslation("ru","Seventh Results");

        MultiLanguageString ms8;
        ms8.SetTranslation("en","Eighth Results");
        ms8.SetTranslation("ru","Eighth Results");

        MultiLanguageString ms9;
        ms9.SetTranslation("en","Ninth Results");
        ms9.SetTranslation("ru","Ninth Results");

        WidgetOutput->SetOutputTitle1(ms1);
        WidgetOutput->SetOutputTitle2(ms2);
        WidgetOutput->SetOutputTitle3(ms3);
        WidgetOutput->SetOutputTitle4(ms4);
        WidgetOutput->SetOutputTitle5(ms5);
        WidgetOutput->SetOutputTitle6(ms6);
        WidgetOutput->SetOutputTitle7(ms7);
        WidgetOutput->SetOutputTitle8(ms8);
        WidgetOutput->SetOutputTitle9(ms9);


        WidgetOutput->SetOutputVisible1(true);
        WidgetOutput->SetOutputVisible2(true);
        WidgetOutput->SetOutputVisible3(true);
        WidgetOutput->SetOutputVisible4(false);
        WidgetOutput->SetOutputVisible5(false);
        WidgetOutput->SetOutputVisible6(false);
        WidgetOutput->SetOutputVisible7(false);
        WidgetOutput->SetOutputVisible8(false);
        WidgetOutput->SetOutputVisible9(false);
    }

}
