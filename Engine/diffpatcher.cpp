#include "diffpatcher.h"
#include "diff_match_patch.h"
#include <QList>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DiffPatcher::DiffPatcher(QObject *parent) :  IDiffPatcher(parent)
    {

    }

    void DiffPatcher::Init(const QString& Text)
    {
        LastText = Text;
    }

    QString DiffPatcher::ApplyPatch(const QString& PatchString)
    {
        diff_match_patch diff;
        QList<Patch> PatchObject = diff.patch_fromText(PatchString);
        LastText = diff.patch_apply(PatchObject, LastText).first;
        return LastText;
    }


}
