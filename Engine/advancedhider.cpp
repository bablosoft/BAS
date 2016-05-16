#include "advancedhider.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    AdvancedHider::AdvancedHider(QObject *parent) :
        QObject(parent)
    {
    }
    void AdvancedHider::SetAskUserForResourcesDialog(AskUserForResourcesDialog *Ask)
    {
        connect(Ask,SIGNAL(ShowAdvanced()),this,SLOT(ShowAdvanced()));
        connect(Ask,SIGNAL(HideAdvanced()),this,SLOT(HideAdvanced()));
        this->Ask = Ask;
    }
    void AdvancedHider::ShowAdvanced()
    {
        foreach(IResourceWidget*w,Data)
        {
            w->VisibilityAdvancedChanged(true);
        }
    }
    void AdvancedHider::HideAdvanced()
    {
        foreach(IResourceWidget*w,Data)
        {
            w->VisibilityAdvancedChanged(false);
        }
    }
    void AdvancedHider::InsertResourceWidget(IResourceWidget *Widget)
    {
        Data.append(Widget);
    }
}
