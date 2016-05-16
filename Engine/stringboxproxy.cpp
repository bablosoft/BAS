#include "stringboxproxy.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    StringBoxProxy::StringBoxProxy(QObject *parent) :
        IStringBoxProxy(parent), FilterIncome(false), Loader(0), DontGiveUp(false), FirstTimeLoaded(false)
    {
    }

    void StringBoxProxy::Reload()
    {
        Box->Reload();
        if(FilterIncome)
        {
            LastPortion.clear();
            LastPortionCollect.clear();
        }
        Load();
    }

    void StringBoxProxy::ReloadOnDemad()
    {
        Box->Reload();
        if(FilterIncome)
        {
            LastPortion.clear();
            LastPortionCollect.clear();
        }
        Box->SetDontGiveUp(true);
        Loader->Load();
    }

    void StringBoxProxy::SetFilterIncome(bool filter)
    {
        FilterIncome = filter;
    }

    void StringBoxProxy::SetStringBoxLoader(IStringBoxLoader * Loader)
    {
        if(this->Loader)
        {
            disconnect(this->Loader,SIGNAL(Loaded(QStringList&)),this,SLOT(Loaded(QStringList&)));
            disconnect(this->Loader,SIGNAL(DataLoadedCompletely()),this,SLOT(DataLoadedCompletelySlot()));
        }

        this->Loader = Loader;
        connect(this->Loader,SIGNAL(Loaded(QStringList&)),this,SLOT(Loaded(QStringList&)));
        connect(this->Loader,SIGNAL(DataLoadedCompletely()),this,SLOT(DataLoadedCompletelySlot()));
    }

    void StringBoxProxy::DataLoadedCompletelySlot()
    {
        if(!GetDontGiveUp())
        {
            Box->SetDontGiveUp(false);
            FirstTimeLoaded = true;
        }
        LastPortion = LastPortionCollect;
        LastPortionCollect.clear();
        emit DataLoadedCompletely();
    }

    void StringBoxProxy::SetStringBox(IStringBox * Box)
    {
        this->Box = Box;
        connect(Box,SIGNAL(NeedToUpdate()),this,SIGNAL(NeedToUpdate()));
    }

    void StringBoxProxy::AddToBox(QStringList& list)
    {
        if(GetMix())
        {
            int n = list.size();
            for (int i=n-1; i>0; --i) list.swap(i,qrand()%(i));
        }
        Box->SetDoMix(GetMix());
        Box->Put(list);
    }

    void StringBoxProxy::Loaded(QStringList &list)
    {
        if(FilterIncome)
        {
            QStringList ToAdd;

            list.sort();
            LastPortion.sort();
            {
                int iterator1 = 0,iterator2 = 0;
                int len1 = LastPortion.length(), len2 = list.length();

                while(iterator2 < len2)
                {
                    QString str2 = list.at(iterator2);
                    if(iterator1 >= len1)
                    {
                        ToAdd.append(str2);
                        iterator2++;
                    }else
                    {
                        QString str1 = LastPortion.at(iterator1);
                        int compare = QString::compare(str1,str2);
                        if(compare == 0)
                        {
                            iterator1++;
                            iterator2++;
                        }else if(compare < 0)
                        {
                            iterator1++;
                        }else
                        {
                            ToAdd.append(str2);
                            iterator2++;
                        }
                    }
                }
            }
            /*foreach(QString str, list)
            {
                if(!LastPortion.contains(str))
                {
                    ToAdd.append(str);
                }
            }*/
            AddToBox(ToAdd);

            {
                int iterator1 = 0,iterator2 = 0;
                int len1 = list.length(), len2 = LastPortion.length();

                while(iterator2 < len2)
                {
                    QString str2 = LastPortion.at(iterator2);
                    if(iterator1 >= len1)
                    {
                        Box->Remove(str2);
                        iterator2++;
                    }else
                    {
                        QString str1 = list.at(iterator1);
                        int compare = QString::compare(str1,str2);
                        if(compare == 0)
                        {
                            iterator1++;
                            iterator2++;
                        }else if(compare < 0)
                        {
                            iterator1++;
                        }else
                        {
                            Box->Remove(str2);
                            iterator2++;
                        }
                    }
                }
            }
            /*foreach(QString str, LastPortion)
            {
                if(!list.contains(str))
                {
                    Box->Remove(str);
                }
            }*/

            LastPortionCollect<<list;
        }
        else
        {
            AddToBox(list);
        }

        emit DataLoaded(list);
    }

    void StringBoxProxy::Load()
    {
        if(!FirstTimeLoaded)
        {
            Box->SetDontGiveUp(true);
            Loader->Load();
        }
    }

    void StringBoxProxy::SetMix(bool mix)
    {
        Mix = mix;
    }
    bool StringBoxProxy::GetMix()
    {
        return Mix;
    }

    void StringBoxProxy::SetDontGiveUp(bool DontGiveUp)
    {
        this->DontGiveUp = DontGiveUp;
    }

    bool StringBoxProxy::GetDontGiveUp()
    {
        return DontGiveUp;
    }
}
