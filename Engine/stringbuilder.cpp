#include "stringbuilder.h"
#include "vocabularytest.h"
#include <QSettings>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    StringBuilder::StringBuilder(QObject *parent) :
        IStringBuilder(parent)
    {
        vocabulary.insert("ELowVow","{a|e|i|o|u}");
        vocabulary.insert("EUpVow","{A|E|I|O|U}");
        vocabulary.insert("ELowCons","{b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|w|x|y|z}");
        vocabulary.insert("EUpCons","{B|C|D|F|G|H|J|K|L|M|N|P|Q|R|S|T|V|W|X|Y|Z}");
        vocabulary.insert("EUp","{<EUpVow>|<EUpCons>}");
        vocabulary.insert("ELow","{<ELowVow>|<ELowCons>}");
        vocabulary.insert("EFemName","{Mary|Jennifer|Lisa|Sandra|Michelle|Patricia|Maria|Nancy|Donna|Laura|Linda|Susan|Karen|Carol|Sarah|Barbara|Margaret|Betty|Ruth|Kimberly|Elizabeth|Dorothy|Helen|Sharon|Deborah}");
        vocabulary.insert("EFemNameLow","{mary|jennifer|lisa|sandra|michelle|patricia|maria|nancy|donna|laura|linda|susan|karen|carol|sarah|barbara|margaret|betty|ruth|kimberly|elizabeth|dorothy|helen|sharon|deborah}");
        vocabulary.insert("EMaleName","{James|David|Christopher|George|Ronald|John|Richard|Daniel|Kenneth|Anthony|Robert|Charles|Paul|Steven|Kevin|Michael|Joseph|Mark|Edward|Jason|William|Thomas|Donald|Brian|Jeff}");
        vocabulary.insert("EMaleNameLow","{james|david|christopher|george|ronald|john|richard|daniel|kenneth|anthony|robert|charles|paul|steven|kevin|michael|joseph|mark|edward|jason|william|thomas|donald|brian|jeff}");
        vocabulary.insert("ESurname","{Smith|Anderson|Clark|Wright|Mitchell|Johnson|Thomas|Rodriguez|Lopez|Perez|Williams|Jackson|Lewis|Hill|Roberts|Jones|White|Lee|Scott|Turner|Brown|Harris|Walker|Green|Phillips|Davis|Martin|Hall|Adams|Campbell|Miller|Thompson|Allen|Baker|Parker|Wilson|Garcia|Young|Gonzalez|Evans|Moore|Martinez|Hernandez|Nelson|Edwards|Taylor|Robinson|King|Carter|Collins}");
        vocabulary.insert("ESurnameLow","{smith|anderson|clark|wright|mitchell|johnson|thomas|rodriguez|lopez|perez|williams|jackson|lewis|hill|roberts|jones|white|lee|scott|turner|brown|harris|walker|green|phillips|davis|martin|hall|adams|campbell|miller|thompson|allen|baker|parker|wilson|garcia|young|gonzalez|evans|moore|martinez|hernandez|nelson|edwards|taylor|robinson|king|carter|collins}");


        vocabulary.insert("Birth","19{6|7|8}?");
        vocabulary.insert("Numbers","{2000|2010|2011|2012|99|9|100}");

    }

    void StringBuilder::AddFromSettings(const QString& IniFile,const QStringList& Keys)
    {
        QSettings settings(IniFile,QSettings::IniFormat);
        settings.setIniCodec("UTF-8");
        foreach(QString key,Keys)
        {
            vocabulary.insert(key,QString::fromUtf8(settings.value(key).toByteArray()));
        }
    }

    void StringBuilder::AddAdditionalData(const QHash<QString,QString>& Data)
    {
        vocabulary.unite(Data);
    }

    QString RandomChar()
    {
        static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
        return QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
    }

    QString RandomDigit()
    {
        static const char alphanum[] = "0123456789";
        return QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
    }

    QString StringBuilder::Expand(const QString& str)
    {
        QString res = str;
        int j;
        int i = 0;
        while(true)
        {
            i++;
            bool no_activity = true;
            while ((j = res.indexOf("<AnyLetter>")) != -1)
            {
                no_activity = false;
                res.replace(j,11,RandomChar());
            }
            while ((j = res.indexOf("<AnyDigit>")) != -1)
            {
                no_activity = false;
                res.replace(j,10,RandomDigit());
            }

            while(true)
            {

                QRegExp regexp("\\{([^\\}\\{]+)\\}");
                j = res.indexOf(regexp);

                if(j<0)
                    break;
                no_activity = false;
                QStringList list = regexp.capturedTexts().at(1).split("|");
                QString r = list.at(qrand() % (list.size()));
                res.replace(j,regexp.matchedLength(),r);
            }

            QHashIterator<QString, QString> it(vocabulary);
            while (it.hasNext())
            {
                it.next();
                QString key = "<" + it.key() + ">";
                if(res.contains(key))
                {
                    no_activity = false;
                    res.replace(key,it.value());
                }
            }

            if(no_activity || i>100)
                break;
        }



        return res;
    }


    void StringBuilder::Show(const QString& str)
    {
        VocabularyTest w;
        w.SetStringBuilder(this);
        connect(&w,SIGNAL(Changed(QString)),this,SIGNAL(Changed(QString)));
        w.SetText(str);
        w.setModal(true);
        w.exec();
    }
}
