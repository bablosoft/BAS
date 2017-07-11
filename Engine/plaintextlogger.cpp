#include "plaintextlogger.h"
#include <QApplication>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    PlainTextLogger::PlainTextLogger(QObject *parent) : ILogger(parent), TextEdit(0)
    {
        NumberOfLines = 0;
        ReplaceActionIdWithLink = false;
        ReplaceActionIdWithColor = false;
    }

    void PlainTextLogger::SetReplaceActionIdWithLink()
    {
        ReplaceActionIdWithLink = true;
    }
    void PlainTextLogger::SetReplaceActionIdWithColor()
    {
        ReplaceActionIdWithColor = true;
    }


    QString PlainTextLogger::GetFileName()
    {
        return QString();
    }


    void PlainTextLogger::SetPlainTextElement(QTextBrowser * TextEdit)
    {
        this->TextEdit = TextEdit;
        //TextEdit->setOpenExternalLinks(true);
    }

    QTextBrowser * PlainTextLogger::GetSetPlainTextElement()
    {
        return TextEdit;
    }

    void PlainTextLogger::WriteInternal(const QString& line,const QString& suffix,const QString& prefix, bool escape)
    {
        if(!TextEdit)
            return;

        if(NumberOfLines>=1000)
        {
            NumberOfLines = 100;
            TextEdit->setHtml("");
            foreach(QString str, Tail)
                TextEdit->append(str);
            Tail.clear();
        }else if(NumberOfLines>=900)
        {
            Tail.append(line);
        }

        NumberOfLines++;
        emit NewLine();
        QString res = line;

        if(escape)
            res.replace("<","&lt;").replace(">","&gt;");

        QRegExp ReplaceIds("^\\[(\\d+)\\]");

        if(ReplaceActionIdWithLink)
            res = res.replace(ReplaceIds,"<a href='action://action\\1' style='color:gray;'>[\\1]</a>");
        else if (ReplaceActionIdWithColor)
            res = res.replace(ReplaceIds,"<span style='color:gray;'>[\\1]</span>");

        TextEdit->append(suffix + res + prefix);
    }

    void PlainTextLogger::WriteHtml(const QString& line_html, const QString& line_raw)
    {
        WriteInternal(line_html,"","",false);
    }

    void PlainTextLogger::Write(const QString& line)
    {
        if(Color.isEmpty())
        {
            Color = QApplication::palette().color(QPalette::Text).name();
        }
        WriteInternal(line,QString("<font color='%1'>").arg(Color),"</font>",true);
    }

    void PlainTextLogger::Clear()
    {
        TextEdit->clear();
        NumberOfLines = 0;
        Tail.clear();
        Color.clear();
    }

    void PlainTextLogger::WriteFail(const QString& line)
    {
        WriteInternal(line,"<font color='red'>","</font>",true);
    }

    void PlainTextLogger::WriteSuccess(const QString& line)
    {
        WriteInternal(line,"<font color='#1c1'>","</font>",true);
    }
}
