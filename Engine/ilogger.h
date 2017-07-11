#ifndef ILOGGER_H
#define ILOGGER_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ILogger : public QObject
    {
    Q_OBJECT
    public:
        explicit ILogger(QObject *parent = 0);

    signals:
        void NewLine();
    public slots:
        virtual QString GetFileName() = 0;
        virtual void Write(const QString& line) = 0;
        virtual void Clear() = 0;
        virtual void WriteHtml(const QString& line_html, const QString& line_raw) = 0;
        virtual void WriteFail(const QString& line) = 0;
        virtual void WriteSuccess(const QString& line) = 0;
        virtual void SetReplaceActionIdWithLink() = 0;
        virtual void SetReplaceActionIdWithColor() = 0;

    };
}

#endif // ILOGGER_H
