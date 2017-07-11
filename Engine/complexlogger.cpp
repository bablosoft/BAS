#include "complexlogger.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    ComplexLogger::ComplexLogger(QObject *parent) :
        ILogger(parent)
    {
    }

    void ComplexLogger::SetReplaceActionIdWithLink()
    {

    }
    void ComplexLogger::SetReplaceActionIdWithColor()
    {

    }

    void ComplexLogger::AddLogger(ILogger* Logger)
    {
        Loggers.append(Logger);
    }

    QString ComplexLogger::GetFileName()
    {
        foreach(ILogger *log,Loggers)
        {
            QString res = log->GetFileName();
            if(!res.isEmpty())
                return res;

        }
    }

    void ComplexLogger::Clear()
    {
        foreach(ILogger *log,Loggers)
            log->Clear();
    }

    void ComplexLogger::Write(const QString& line)
    {
        foreach(ILogger *log,Loggers)
            log->Write(line);

        emit NewLine();
    }

    void ComplexLogger::WriteHtml(const QString& line_html, const QString& line_raw)
    {
        foreach(ILogger *log,Loggers)
            log->WriteHtml(line_html, line_raw);

        emit NewLine();
    }

    void ComplexLogger::WriteFail(const QString& line)
    {
        foreach(ILogger *log,Loggers)
            log->WriteFail(line);

        emit NewLine();
    }
    void ComplexLogger::WriteSuccess(const QString& line)
    {
        foreach(ILogger *log,Loggers)
            log->WriteSuccess(line);

        emit NewLine();
    }

}
