#ifndef PLAINTEXTLOGGER_H
#define PLAINTEXTLOGGER_H
#include "engine_global.h"

#include "ilogger.h"
#include <QTextBrowser>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT PlainTextLogger : public ILogger
    {
    Q_OBJECT
        QTextBrowser * TextEdit;
        int NumberOfLines;
        QStringList Tail;
        QString Color;
        bool ReplaceActionIdWithLink;
        bool ReplaceActionIdWithColor;
        void WriteInternal(const QString& line,const QString& suffix,const QString& prefix, bool escape);
    public:
        explicit PlainTextLogger(QObject *parent = 0);

        void SetPlainTextElement(QTextBrowser * TextEdit);
        QTextBrowser * GetSetPlainTextElement();

    signals:

    public slots:
        virtual QString GetFileName();
        virtual void Clear();
        virtual void Write(const QString& line);
        virtual void WriteHtml(const QString& line_html, const QString& line_raw);
        virtual void WriteFail(const QString& line);
        virtual void WriteSuccess(const QString& line);
        virtual void SetReplaceActionIdWithLink();
        virtual void SetReplaceActionIdWithColor();
    };
}

#endif // PLAINTEXTLOGGER_H
