#include "filelogger.h"
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{

    FileLogger::FileLogger(QObject *parent) : ILogger(parent)
    {

    }

    void FileLogger::SetReplaceActionIdWithLink()
    {

    }
    void FileLogger::SetReplaceActionIdWithColor()
    {

    }

    QString FileLogger::GetFileName()
    {
        QFileInfo info(FileName);

        return info.absoluteFilePath();
    }

    void FileLogger::Clear()
    {

    }

    void FileLogger::SetFileName(const QString& FileName)
    {
        QFileInfo info(FileName);
        this->FileName = FileName;
        FileIterator = 0;
        info.dir().mkpath(".");
        File = new QFile(FileName);
        FlushNumber = 0;
        NewFileNumber = 0;
        File->open(QIODevice::WriteOnly | QIODevice::Append);
    }

    FileLogger::~FileLogger()
    {
        File->close();
        delete File;
    }

    void FileLogger::WriteHtml(const QString& line_html, const QString& line_raw)
    {
        Write(line_raw);
    }

    void FileLogger::Write(const QString& line)
    {

        //Write
        QTextStream out(File);
        out.setCodec("UTF-8");
        out<<line<<"\r\n";

        //Increase counters
        FlushNumber++;
        NewFileNumber++;

        //Flush
        if(FlushNumber >= 100)
        {
            FlushNumber = 0;
            File->flush();
        }
        //CreateNewFile
        if(NewFileNumber >= 1000000)
        {
            FileIterator++;
            QFileInfo info(FileName);
            QString suffix = info.suffix();
            QString OldFileName = FileName;
            QString NewFileName = FileName.replace(suffix, QString::number(FileIterator) + "." + suffix);
            FileName = OldFileName;
            NewFileNumber = 0;
            File->close();
            delete File;
            File = new QFile(NewFileName);
            File->open(QIODevice::WriteOnly | QIODevice::Append);

        }
        emit NewLine();
    }

    void FileLogger::WriteFail(const QString& line)
    {
        Write(line);
    }

    void FileLogger::WriteSuccess(const QString& line)
    {
        Write(line);
    }

}
