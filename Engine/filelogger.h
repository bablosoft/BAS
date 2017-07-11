#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "engine_global.h"

#include "ilogger.h"
#include <QFile>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT FileLogger : public ILogger
    {
        Q_OBJECT
        QFile *File;
        QString FileName;
        int FileIterator;
        int FlushNumber;
        int NewFileNumber;
    public:
        explicit FileLogger(QObject *parent = 0);
        void SetFileName(const QString& FileName);
        ~FileLogger();
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

#endif // FILELOGGER_H
