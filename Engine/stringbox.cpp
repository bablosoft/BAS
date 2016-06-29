#include "stringbox.h"
#include "uprng.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    StringBox::StringBox(QObject *parent) :
        IStringBox(parent),GlobalIterator(0),Greedy(false)
    {
    }

    void StringBox::Reload(StringBoxNode& node)
    {
        node.Fail = 0;
        node.Success = 0;
        node.NumberOfUse = 0;
        node.LastUsage = QDateTime(QDate(1970,1,1),QTime(0,0,0,0));
    }

    void StringBox::Reload()
    {
        Data.clear();
        GlobalIterator = 0;
    }
    QList<QString> StringBox::GetAll()
    {
        QList<QString> res;
        int len = Data.length();
        for(int i=0;i<len;i++)
        {
            QPair<QString,StringBoxNode> p = Data.at(i);
            res.append(p.first);
        }
        return res;
    }

    void StringBox::Put(const QStringList& list)
    {
        foreach(QString s, list)
        {
            StringBoxNode node;
            Reload(node);
            QPair<QString,StringBoxNode> n(s,node);
            Data.append(n);
        }
    }

    void StringBox::Insert(const QString& str, bool onlywrite)
    {
        if(!onlywrite)
            Put(QStringList()<<str);
        emit Inserted(str);
    }

    QList<QString> StringBox::GetRandomSubarrayData(int size)
    {
        QList<QString> res;
        int Size = size;
        if(Size <= 0 || Data.length() == 0)
            return res;
        if(Data.length() == 1)
        {
            res.append(Data.at(0).first);
            return res;
        }
        if(Size > Data.length())
            Size = Data.length();

        int add = 100;
        UPRNG G;G.Init(Data.length() + add);
        for(int i=0;i<Size;)
        {
            int g = G.GenerateNext();
            if(g>=add)
            {
                res.append(Data.at(g-add).first);
                i++;
            }
        }

        return res;
    }

    QString StringBox::GetAtIndex(int index, bool & IsNull)
    {
        if(index<0 || index>=Data.length())
        {
            IsNull = true;
            return QString();
        }
        IsNull = false;
        return Data.at(index).first;
    }

    void StringBox::SetAtIndex(int index, const QString& value)
    {
        if(index<0 || index>=Data.length())
        {
            return;
        }
        Data[index].first = value;
    }

    int StringBox::GetTotalLength()
    {
        return Data.length();
    }

    IStringBox::StringBoxItem StringBox::Get(const QSet<QString>& refuse)
    {
        StringBoxItem item;

        if(Data.isEmpty())
        {
            if(GetDontGiveUp())
            {
                item.Status = IStringBox::StringBoxItem::Wait;
            }else
            {
                item.Status = IStringBox::StringBoxItem::NotAvailable;
            }
            emit NeedToUpdate();
            return item;
        }


        QDateTime now = QDateTime::currentDateTime();
        if(Greedy)
        {
            GlobalIterator = 0;
        }
        QList<QPair<QString,StringBoxNode> >::iterator i = Data.begin() + GlobalIterator;
        int waiting = 0;
        int refused = 0;
        int num = 0;

        //for (i = Data.begin(); i != Data.end(); ++i)
        while(num < Data.count())
        {
            if(i >= Data.end() || i < Data.begin())
            {
                if(DoMix)
                {
                    int n = Data.count();
                    for (int j=n-1; j>0; --j) Data.swap(j,qrand()%(j));
                }

                i = Data.begin();
                GlobalIterator = 0;

            }

            GlobalIterator++;
            num++;
            StringBoxNode node = i->second;
            if(node.NumberOfUse<GetMaxSimultaneousUse() && node.LastUsage.msecsTo(now) > GetInterval())
            {
                bool contains = false;
                for(QSet<QString>::const_iterator j = refuse.begin();j != refuse.end();j++)
                {
                    if(i->first.contains(*j))
                    {
                        contains = true;
                        break;
                    }
                }

                if(!contains)
                {
                    node.NumberOfUse++;
                    i->second = node;
                    item.Status = IStringBox::StringBoxItem::Ready;
                    item.Value = i->first;
                    return item;

                }else
                {
                    refused++;
                }

            }else
            {
                waiting++;
            }
            i++;

        }
        if(waiting > 0)
            item.Status = IStringBox::StringBoxItem::Wait;
        else
        {
            if(GetDontGiveUp())
            {
                item.Status = IStringBox::StringBoxItem::Wait;
            }else
            item.Status = IStringBox::StringBoxItem::Refused;
        }
        emit NeedToUpdate();
        return item;

    }

    QList<QPair<QString,StringBox::StringBoxNode> >::iterator StringBox::SearchInData(const QString & key)
    {
        QList<QPair<QString,StringBoxNode> >::iterator i;
        LastSearchIndex = 0;
        for (i = Data.begin(); i != Data.end(); ++i)
        {
            if(i->first == key)
                return i;

            LastSearchIndex++;
        }

        return i;
    }

    void StringBox::Erase(QList<QPair<QString,StringBoxNode> >::iterator it)
    {
        Data.erase(it);
        if(GlobalIterator > LastSearchIndex)
        {
            if(GlobalIterator>0)
                GlobalIterator--;
        }
    }

    void StringBox::Success(const QString& str)
    {
        QList<QPair<QString,StringBox::StringBoxNode> >::iterator i = SearchInData(str);
        if(i != Data.end())
        {
            StringBoxNode node = i->second;
            node.Success++;
            node.NumberOfUse--;
            node.LastUsage = QDateTime::currentDateTime();
            if(node.Success>=GetMaxSuccess())
            {
                Erase(i);
                emit Removed(str);
            }else
            {
                i->second = node;
            }
        }
    }

    void StringBox::Fail(const QString& str)
    {
        QList<QPair<QString,StringBox::StringBoxNode> >::iterator i = SearchInData(str);
        if(i != Data.end())
        {
            StringBoxNode node = i->second;
            node.Fail++;
            node.NumberOfUse--;
            node.LastUsage = QDateTime::currentDateTime();
            if(node.Fail>=GetMaxFail())
            {
                Erase(i);
                emit Removed(str);
            }else
            {
                i->second = node;
            }
        }
    }

    void StringBox::Update(const QString& str, const QString& replace)
    {
        QList<QPair<QString,StringBox::StringBoxNode> >::iterator i = SearchInData(str);
        if(i != Data.end())
        {
            QPair<QString,StringBox::StringBoxNode> p = *i;
            p.first = replace;
            *i = p;
        }
    }


    void StringBox::Die(const QString& str)
    {
        QList<QPair<QString,StringBox::StringBoxNode> >::iterator i = SearchInData(str);
        if(i != Data.end())
        {
            Erase(i);
            emit Removed(str);
        }
    }

    void StringBox::Remove(const QString& str)
    {

        QList<QPair<QString,StringBox::StringBoxNode> >::iterator i = SearchInData(str);
        if(i != Data.end())
        {
            Erase(i);
        }
    }

    void StringBox::SetMaxSuccess(int success)
    {
        MaxSuccess = success;
    }
    void StringBox::SetMaxFail(int fail)
    {
        MaxFail = fail;
    }
    void StringBox::SetMaxSimultaneousUse(int sim)
    {
        MaxSimultaneousUse = sim;
    }
    void StringBox::SetInterval(int interval)
    {
        MaxInterval = interval;
    }
    int StringBox::GetMaxSuccess()
    {
        return MaxSuccess;
    }
    int StringBox::GetMaxFail()
    {
        return MaxFail;
    }
    int StringBox::GetMaxSimultaneousUse()
    {
        return MaxSimultaneousUse;
    }
    int StringBox::GetInterval()
    {
        return MaxInterval;
    }

    void StringBox::SetDontGiveUp(bool dontgiveup)
    {
        DontGiveUp = dontgiveup;
    }

    bool StringBox::GetDontGiveUp()
    {
        return DontGiveUp;
    }


    void StringBox::SetDoMix(bool DoMix)
    {
        this->DoMix = DoMix;
    }

    bool StringBox::GetDoMix()
    {
        return DoMix;
    }

    void StringBox::SetGreedy(bool Greedy)
    {
        this->Greedy = Greedy;
    }

    bool StringBox::GetGreedy()
    {
        return Greedy;
    }

}
