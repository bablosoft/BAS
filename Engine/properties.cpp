#include "properties.h"
#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    Properties::Properties(QObject *parent) :
        IProperties(parent)
    {
    }
    QString Properties::Get(const QString& Group, const QString& Key)
    {
        if(!Data.contains(Group))
            return QString();
        QSharedPointer<QHash<QString, QString> > Keys = Data.value(Group);
        if(!Keys->contains(Key))
            return QString();
        return Keys->value(Key);
    }
    void Properties::Set(const QString& Group, const QString& Key, const QString & Value)
    {
        QSharedPointer<QHash<QString, QString> > Keys;
        if(!Data.contains(Group))
        {
            Keys.reset(new QHash<QString, QString>());

            Data[Group] = Keys;
        }else
        {
            Keys = Data.value(Group);
        }
        Keys->insert(Key,Value);
    }
    void Properties::Clear(const QString& Group, const QString& Key)
    {
        if(Group.isEmpty() && Key.isEmpty())
        {
            Data.clear();
        }else if(Key.isEmpty())
        {
            Data.remove(Group);
        }else
        {
            if(!Data.contains(Group))
                return;
            QSharedPointer<QHash<QString, QString> > Keys = Data.value(Group);
            if(!Keys->contains(Key))
                return;
            Keys->remove(Key);
        }
    }

}
