#ifndef OPENLINKSFROMFILESYSTEM_H
#define OPENLINKSFROMFILESYSTEM_H

#include "engine_global.h"
#include <QObject>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT OpenLinksFromFileSystem : public QObject
    {
        Q_OBJECT
    public:
        explicit OpenLinksFromFileSystem(QObject *parent = 0);

    signals:

    private slots:
        void AnchorClicked(const QUrl & url);

    };
}

#endif // OPENLINKSFROMFILESYSTEM_H
