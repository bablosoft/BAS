#ifndef SUBSTAGEMANAGER_H
#define SUBSTAGEMANAGER_H

#include <QHash>
#include "iworker.h"
#include "ibrowser.h"

class SubstageManager
{
    struct Substage
    {
        int Id;
        qint64 MaxSuccessLeft;
        qint64 MaxFailureLeft;
        qint64 ThreadsWorking;
        bool IsDead = false;
        QList<BrowserAutomationStudioFramework::IWorker *> Workers;
        QList<BrowserAutomationStudioFramework::IBrowser *> Browsers;
    };
    QHash<int, Substage> Stages;
public:


    SubstageManager();
    void AddSubstage(int Id, qint64 MaxSuccessLeft, qint64 MaxFailureLeft, qint64 ThreadsWorking, QList<BrowserAutomationStudioFramework::IBrowser *> Browsers);
    void RemoveStage(int Id);
    QList<BrowserAutomationStudioFramework::IWorker *> * GetWorkers(int Id);
    QList<BrowserAutomationStudioFramework::IBrowser *> * GetBrowsers(int Id);
    QList<BrowserAutomationStudioFramework::IWorker *> GetAllWorkers();
    QList<BrowserAutomationStudioFramework::IBrowser *> GetAllBrowsers();
    int TotalWorkers();
    void Success(int Id);
    void Failure(int Id);
    void Die(int Id);
    void EndThread(int Id);
    bool CreateThread(int Id);
    bool NeedToFinishStage(int Id);
    void Clear();

};

#endif // SUBSTAGEMANAGER_H
