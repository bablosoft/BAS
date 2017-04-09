#include "csvhelper.h"
#include <QStringList>
#include <QChar>

#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    CsvHelper::CsvHelper(QObject *parent) :
        ICsvHelper(parent)
    {
    }

    QString CsvHelper::Generate(const QStringList& List, QChar Separator)
    {
        QString res;
        bool First = true;
        foreach(QString Item,List)
        {
            QString add = Item;
            if(Item.contains(";") || Item.contains(":") || Item.contains(","))
            {
                add = QString("\"") + add.replace("\"","\"\"") + QString("\"");
            }
            if(!First)
                res.append(Separator);
            res.append(add);
            First = false;
        }
        return res;
    }
    QStringList CsvHelper::Parse(const QString& Line)
    {
        QStringList res;
        int index = 0, len = Line.length();

        bool InsideQuotes = false;

        QString CurrentElement;
        while(index<len)
        {
            QChar c = Line.at(index);
            QChar n;
            bool HasNext = index + 1 < len;
            if(HasNext)
                n = Line.at(index + 1);

            index ++;

            if(c == '\"')
            {
                if(InsideQuotes)
                {
                    if(!HasNext || n != '\"')
                    {
                        InsideQuotes = false;
                        continue;
                    }else
                    {
                        CurrentElement.append("\"");
                        index++;
                        continue;
                    }
                }else
                {
                    InsideQuotes = true;
                    continue;
                }

            }

            if(c == ':' || c == ';' || c == ',')
            {
                if(InsideQuotes)
                {
                    CurrentElement.append(c);
                    continue;
                }else
                {
                    res.append(CurrentElement);
                    CurrentElement.clear();
                    continue;
                }
            }

            CurrentElement.append(c);
        }
        res.append(CurrentElement);

        return res;
    }
}
