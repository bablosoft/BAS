#include "generalvalidator.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    GeneralValidator::GeneralValidator(QObject *parent) :
        IValidator(parent)
    {
    }


    void GeneralValidator::InsertResourceWidget(IResourceWidget* Widget)
    {
        Data.append(Widget);
    }

    bool GeneralValidator::Validate()
    {
        foreach(IResourceWidget * w,Data)
        {
            if(!w->IsValid() && w->GetRequiresValidation())
            {
                return false;
            }
        }
        return true;
    }

    void GeneralValidator::Clear()
    {
        Data.clear();
    }
}
