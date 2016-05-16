#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H
#include "engine_global.h"

#include "istringbuilder.h"
#include <QHash>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringBuilder : public IStringBuilder
    {
        Q_OBJECT
        QHash<QString,QString> vocabulary;
    public:
        explicit StringBuilder(QObject *parent = 0);

    signals:

    public slots:
        void AddFromSettings(const QString& IniFile,const QStringList& Keys);
        virtual void AddAdditionalData(const QHash<QString,QString>& Data);
        virtual QString Expand(const QString& str);
        virtual void Show(const QString& str);
    };
}

#endif // STRINGBUILDER_H
