#ifndef IVERSIONINFO_H
#define IVERSIONINFO_H
#include "engine_global.h"

#include <QObject>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IVersionInfo : public QObject
    {
        Q_OBJECT
    public:
        explicit IVersionInfo(QObject *parent = 0);
        virtual int MajorVersion() = 0;
        virtual int MinorVersion() = 0;
        virtual int BuildVersion() = 0;
        virtual QString VersionString() = 0;
        virtual void ShowAboutWindow() = 0;
    signals:

    public slots:

    };
}

#endif // IVERSIONINFO_H
