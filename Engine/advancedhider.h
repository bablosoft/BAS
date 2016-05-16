#ifndef ADVANCEDHIDER_H
#define ADVANCEDHIDER_H
#include "engine_global.h"

#include <QObject>
#include <QList>
#include "askuserforresourcesdialog.h"
#include "iresourcewidget.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT AdvancedHider : public QObject
    {
        Q_OBJECT
        AskUserForResourcesDialog *Ask;
        QList<IResourceWidget *>Data;
    public:
        explicit AdvancedHider(QObject *parent = 0);
        void SetAskUserForResourcesDialog(AskUserForResourcesDialog *Ask);

    signals:
    public slots:
         void InsertResourceWidget(IResourceWidget *Widget);
         void ShowAdvanced();
         void HideAdvanced();

    private slots:

    };
}

#endif // ADVANCEDHIDER_H
