#ifndef PROJECTBACKUP_H
#define PROJECTBACKUP_H
#include "engine_global.h"
#include "icodeeditor.h"
#include <QTimer>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ProjectBackup : public QObject
    {
        Q_OBJECT
        ICodeEditor * CodeEditor;
        int milliseconds;
        QString DestFolder;
        QTimer* Timer;
        QString LastProject;
    public:
        explicit ProjectBackup(QObject *parent = 0);

        void SetCodeEditor(ICodeEditor * CodeEditor);
        void SetPeriod(int milliseconds);
        void SetDestFolder(const QString& DestFolder);

        void Start();
    signals:

    private slots:
        void DoBackups();
    };
}

#endif // PROJECTBACKUP_H
