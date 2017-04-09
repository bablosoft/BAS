#include "engineresourcestringbox.h"
#include "stringresourcehandler.h"
#include <QStringList>
#include <QDebug>

#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    EngineResourceStringBox::EngineResourceStringBox(QObject *parent) :
        EngineResourceAbstract(parent)
    {
        DatabaseConnector = 0;
    }
    void EngineResourceStringBox::SetValue(IStringBox* Box)
    {
        this->Box = Box;
    }

    void EngineResourceStringBox::SetStringBoxProxy(IStringBoxProxy* StringBoxProxy)
    {
        this->StringBoxProxy = StringBoxProxy;
    }

    void EngineResourceStringBox::SetDatabase(IDatabaseConnector* DatabaseConnector, int TableId, ICsvHelper *_CsvHelper, const QList<int>& ColumnIds)
    {
        this->DatabaseConnector = DatabaseConnector;
        this->TableId = TableId;
        this->_CsvHelper = _CsvHelper;
        this->ColumnIds = ColumnIds;
    }

    IResourceHandler* EngineResourceStringBox::GetHandler(const QSet<QString>& refuse)
    {
        StringResourceHandler *handler = new StringResourceHandler();
        IStringBox::StringBoxItem item = Box->Get(refuse);
        switch(item.Status)
        {
            case IStringBox::StringBoxItem::Ready:
            {
                handler->SetString(item.Value);
                connect(handler,SIGNAL(DieSignal()),this,SLOT(Die()));
                connect(handler,SIGNAL(SuccessSignal()),this,SLOT(Success()));
                connect(handler,SIGNAL(FailSignal()),this,SLOT(Fail()));
                if(DatabaseConnector)
                {
                    connect(handler,SIGNAL(PurgeSignal()),this,SLOT(Purge()));
                    connect(handler,SIGNAL(UpdateSignal(QStringList)),this,SLOT(Update(QStringList)));
                }
                handler->SetHandlerStatus(IResourceHandler::Ready);
            }
            break;
            case IStringBox::StringBoxItem::NotAvailable:
            {
                handler->SetHandlerStatus(IResourceHandler::NotAvailable);
            }
            break;
            case IStringBox::StringBoxItem::Wait:
            {
                handler->SetHandlerStatus(IResourceHandler::Wait);
            }
            break;
            case IStringBox::StringBoxItem::Refused:
            {
                handler->SetHandlerStatus(IResourceHandler::Refused);
            }
            break;

        }
        return handler;
    }

    QList<QScriptValue> EngineResourceStringBox::GetRandomSubarrayData(int size)
    {
        QList<QScriptValue> res;
        foreach(QString str,Box->GetRandomSubarrayData(size))
        {
            res.append(QScriptValue(str));
        }
        return res;
    }

    QScriptValue EngineResourceStringBox::GetAtIndex(int index)
    {
        bool IsNull;
        QString res = Box->GetAtIndex(index,IsNull);
        if(IsNull)
            return QScriptValue(QScriptValue::NullValue);

        return QScriptValue(res);
    }

    void EngineResourceStringBox::SetAtIndex(int index, const QString& val)
    {
        Box->SetAtIndex(index,val);
    }

    int EngineResourceStringBox::GetTotalLength()
    {
        return  Box->GetTotalLength();
    }



    QList<QScriptValue> EngineResourceStringBox::GetAllData()
    {
        QList<QScriptValue> res;
        foreach(QString str,Box->GetAll())
        {
            res.append(QScriptValue(str));
        }
        return res;

    }

    void EngineResourceStringBox::Success()
    {
        StringResourceHandler* handler = qobject_cast<StringResourceHandler*>(sender());
        QString string = handler->GetString();
        Box->Success(string);
    }
    void EngineResourceStringBox::Fail()
    {
        StringResourceHandler* handler = qobject_cast<StringResourceHandler*>(sender());
        QString string = handler->GetString();
        Box->Fail(string);
    }

    void EngineResourceStringBox::Update(const QStringList& Params)
    {
        StringResourceHandler* handler = qobject_cast<StringResourceHandler*>(sender());
        QString string = handler->GetString();

        int index = string.lastIndexOf(QChar(':'));

        QString id = string.right(string.length() - index - 1);
        QString dat = string.mid(0,index);

        QList<DatabaseColumn> Columns = DatabaseConnector->GetColumns(TableId);

        DatabaseItem item;
        item.Id = id;
        item.IsNull = false;

        for(int i = 0;i<Params.length() - 1;i+=2)
        {
            int ColumnIndex = Params.at(i).toInt();
            QString val = Params.at(i+1);

            QVariant VariantParam;
            foreach(DatabaseColumn Column, Columns)
            {
                if(ColumnIndex == Column.Id)
                {
                    switch(Column.Type)
                    {
                        case DatabaseColumn::Int: VariantParam = QVariant(val.toInt());break;
                        case DatabaseColumn::String: VariantParam = QVariant(val);break;
                        case DatabaseColumn::Bool: VariantParam = QVariant(val == "true");break;
                        case DatabaseColumn::Date:
                        {
                            QDateTime timestamp;
                            if(val.length() > 0)
                            {
                                timestamp.setTime_t(val.toLongLong() / 1000);
                            }
                            else
                                timestamp = QDateTime::currentDateTime();
                            VariantParam = QVariant(timestamp);
                        }break;
                    }

                    break;
                }
            }
            item.Data[ColumnIndex] = VariantParam;
        }

        DatabaseConnector->Update(item,TableId);





        QStringList dat_parsed = _CsvHelper->Parse(dat);
        if(dat_parsed.length() == ColumnIds.length())
        {


            int len = dat_parsed.length();
            for(int column_index = 0;column_index < len;column_index++)
            {
                int ColumnId = ColumnIds[column_index];
                if(item.Data.contains(ColumnId))
                {
                    dat_parsed[column_index] = item.Data[ColumnId].toString();
                }
            }


            dat_parsed.append(id);
            QString new_string = _CsvHelper->Generate(dat_parsed,':');

            Box->Update(string,new_string);
            handler->SetString(new_string);
        }


    }


    void EngineResourceStringBox::Purge()
    {
        StringResourceHandler* handler = qobject_cast<StringResourceHandler*>(sender());
        QString string = handler->GetString();

        int index = string.lastIndexOf(QChar(':'));
        if(index>=0)
        {
            QString id = string.right(string.length() - index - 1);

            DatabaseItems Items;
            Items.IsNull = false;
            Items.IsInverseSelection = false;
            QSet<QString> sr = QSet<QString>()<<id;
            Items.SelectedRows = sr;


            DatabaseGroups GroupIds;
            GroupIds.IsNull = true;

            DatabaseFilters Filters;
            Filters.IsNull = true;

            DatabaseMassSelector Selector;
            Selector.Filters = Filters;
            Selector.TableId = TableId;
            Selector.Items = Items;
            Selector.Groups = GroupIds;


            DatabaseConnector->Delete(Selector);
        }
        Box->Die(string);
    }

    void EngineResourceStringBox::Die()
    {
        StringResourceHandler* handler = qobject_cast<StringResourceHandler*>(sender());
        QString string = handler->GetString();
        Box->Die(string);
    }

    void EngineResourceStringBox::Reload()
    {
        StringBoxProxy->ReloadOnDemad();
    }

    void EngineResourceStringBox::Insert(const QString& value, bool onlywrite)
    {
        Box->Insert(value, onlywrite);
    }

    void EngineResourceStringBox::Sync()
    {
        emit Synced();
    }


}
