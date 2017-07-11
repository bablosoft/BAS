#ifndef COMPLEXLOGGER_H
#define COMPLEXLOGGER_H
#include "engine_global.h"

#include "ilogger.h"
#include <QList>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ComplexLogger : public ILogger
    {
        Q_OBJECT
        QList<ILogger*> Loggers;
    public:
        explicit ComplexLogger(QObject *parent = 0);
        void AddLogger(ILogger* Logger);
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

#endif // COMPLEXLOGGER_H
