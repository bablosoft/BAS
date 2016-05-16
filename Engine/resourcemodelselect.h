#ifndef RESOURCEMODELSELECT_H
#define RESOURCEMODELSELECT_H
#include "engine_global.h"

#include "resourcemodelabstract.h"
#include <QStringList>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelSelect : public ResourceModelAbstract
    {
        Q_OBJECT
        QStringList Values;
        QList<int> Selected;


    public:
        explicit ResourceModelSelect(QObject *parent = 0);
        enum SelectType { Combo, Radio, Check, DragAndDrop};
    signals:

    public slots:
        QStringList GetValues();
        void SetValues(const QStringList& val);
        QList<int> GetSelected();
        void SetSelected(const QList<int>& val);
        virtual QString GetTypeId();
        SelectType GetSelectType();
        void SetSelectType(SelectType val);
    private:
        SelectType Type;
    };

}
#endif // RESOURCEMODELSELECT_H
