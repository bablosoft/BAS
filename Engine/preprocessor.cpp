#include "preprocessor.h"
#include <QRegExp>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    Preprocessor::Preprocessor(QObject *parent) :
        IPreprocessor(parent)
    {
        Encryptor = 0;
        GenerateKey();
        IsRecord = false;
    }

    void Preprocessor::SetIsRecord(bool IsRecord)
    {
        this->IsRecord = IsRecord;
    }

    bool Preprocessor::GetIsRecord()
    {
        return IsRecord;
    }

    bool Preprocessor::IsInsideComment(const QString& str,int start)
    {
        int j = start - 1;
        QString start_str;

        while(j>=0 && str[j] != '\r' && str[j] != '\n')
        {
            start_str.insert(0,str[j]);
            --j;
        }


        start_str.replace(QRegExp("\\\\\\\""),"");
        start_str.replace(QRegExp("\\\\\\'"),"");

        QRegExp r1("\\\".*\\\"");
        r1.setMinimal(true);
        start_str.replace(r1,"");

        QRegExp r2("\\'.*\\'");
        r2.setMinimal(true);
        start_str.replace(r2,"");

        bool res = start_str.contains("\'") || start_str.contains("\"");
        return res;
    }

    void Preprocessor::SetEncryptor(IEncryptor* Encryptor)
    {
        this->Encryptor = Encryptor;
    }

    void Preprocessor::SetKey(const QString& Key)
    {
        this->Key = Key;
    }

    void Preprocessor::GenerateKey()
    {
        QString res;
        static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz0123456789";
        for(int i = 0;i<10;i++)
        {
            res += QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
        }
        Key = res;
    }

    QString Preprocessor::Encrypt(const QString& Script,int ParanoicLevel)
    {
        if(ParanoicLevel == 0)
            return Script;

        EncryptIterator++;
        if(EncryptIterator % ParanoicLevel == 0)
            return QString("DEC('") + QString::fromUtf8(Encryptor->Encrypt(Script.toUtf8(),Key).toBase64()) + QString("')");

        return Script;
    }

    QString Preprocessor::Decrypt(const QString& Script)
    {
        return QString::fromUtf8(Encryptor->Decrypt(QByteArray::fromBase64(Script.toUtf8()),Key));
    }

    QString Preprocessor::DecryptNotSafe(const QString& Script)
    {
        return QString::fromUtf8(Encryptor->DecryptNotSafe(QByteArray::fromBase64(Script.toUtf8()),Key));
    }

    QString Preprocessor::Preprocess(const QString& Script,int ParanoicLevel)
    {
        EncryptIterator = 0;
        QString Res = Script;
        {
            QRegExp Regexp("\\/\\*.*\\*\\/");
            Regexp.setMinimal(true);

            int pos = 0;
            while ((pos = Regexp.indexIn(Res, pos)) != -1)
            {
                bool Remove = !IsInsideComment(Res,Regexp.pos());
                if(Remove)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),"");
                }else
                {
                    pos += Regexp.matchedLength();
                }


            }
        }
        {
            QRegExp Regexp("\\/\\/([^\\r\\n]+)");
            int pos = 0;
            while ((pos = Regexp.indexIn(Res, pos)) != -1)
            {
                bool Remove = !IsInsideComment(Res,Regexp.pos());
                if(Remove)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),"");
                }else
                {
                    pos += Regexp.matchedLength();
                }
            }
        }

        if(!IsRecord)
        {
            {
                QRegExp Regexp("section\\_start\\(\\s*\\\"[^\\\"]*\\\"\\s*\\,\\s*\\-?\\d*\\)\\!");
                int pos = 0;
                while ((pos = Regexp.indexIn(Res, pos)) != -1)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),";");
                }
            }

            {
                QRegExp Regexp("section\\_end\\(\\)\\!");
                int pos = 0;
                while ((pos = Regexp.indexIn(Res, pos)) != -1)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),";");
                }
            }

            {
                QRegExp Regexp("section\\_insert\\(\\)");
                int pos = 0;
                while ((pos = Regexp.indexIn(Res, pos)) != -1)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),"");
                }
            }

            {
                QRegExp Regexp("wait\\_code\\(\\)\\!");
                int pos = 0;
                while ((pos = Regexp.indexIn(Res, pos)) != -1)
                {
                    Res.replace(Regexp.pos(),Regexp.matchedLength(),"");
                }
            }
        }

        int from = 0;
        QString async_str = "/*!async*/";
        int async_str_length = async_str.length();
        while(true)
        {
            int length = Res.length();
            int index_start = Res.indexOf(");" + async_str, from);
            from = index_start + async_str_length + 2;
            bool is_one_argument = false;
            int index_search = index_start - 1;
            while(true)
            {
                if(index_search>=0)
                {
                    QChar c = Res.at(index_search);
                    if(c.isSpace())
                    {

                    }else if(c == '(')
                    {
                        is_one_argument = true;
                        break;
                    }
                    else
                    {
                        break;
                    }

                    index_search--;
                }else
                    break;
            }

            if(Res.indexOf(");" + async_str)<0)
            {
                break;
            }
            int index_end = index_start + async_str_length + 2;
            int open_bracket = 0;
            while(true)
            {
                if(index_end >= length - 1)
                {
                    QString all = Res.mid(index_start + async_str_length + 2);
                    if(all.indexOf(");" + async_str)>=0)
                        break;
                    Res = Res.replace(index_start + async_str_length + 2,all.length(),Encrypt(all,ParanoicLevel));

                    Res = Res.replace(index_start,2,", function(){");
                    Res = Res.append("})");
                    from = 0;

                    break;
                }else
                {
                    QChar c = Res.at(index_end);
                    if(c == '{')
                    {
                        open_bracket ++;
                    }else if(c == '}')
                    {
                        open_bracket --;
                        if(open_bracket<0)
                        {
                            QString all = Res.mid(index_start + async_str_length + 2, index_end - index_start - async_str_length - 2);
                            if(all.indexOf(");" + async_str)>=0)
                                break;


                            Res = Res.replace(index_end,1,"})}");
                            Res = Res.replace(index_start + async_str_length + 2,all.length(),Encrypt(all,ParanoicLevel));

                            QString replace_string = "function(){";
                            if(!is_one_argument)
                                replace_string = "," + replace_string;

                            Res = Res.replace(index_start,2,replace_string);
                            from = 0;

                            break;
                        }
                    }

                    if(index_end == length - 1)
                    {
                        QString all = Res.mid(index_start + async_str_length + 2);
                        if(all.indexOf(");" + async_str)>=0)
                            break;
                        Res = Res.replace(index_start + async_str_length + 2,all.length(),Encrypt(all,ParanoicLevel));


                        Res.append("})");
                        QString replace_string = "function(){";
                        if(!is_one_argument)
                            replace_string = "," + replace_string;

                        Res = Res.replace(index_start,2,replace_string);
                        from = 0;

                        break;
                    }
                    index_end++;
                }

            }

        }

        return Res;

    }



}
