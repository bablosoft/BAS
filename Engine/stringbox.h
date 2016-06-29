#ifndef STRINGBOX_H
#define STRINGBOX_H
#include "engine_global.h"

#include "istringbox.h"
#include <QDateTime>
#include <QHash>
#include <QSet>
#include <QStringList>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringBox : public IStringBox
    {
        Q_OBJECT
        int MaxSuccess,MaxFail,MaxSimultaneousUse,MaxInterval;
        bool DontGiveUp;
        struct StringBoxNode
        {
           QDateTime LastUsage;
           int Success, Fail;
           int NumberOfUse;
        };
        QList<QPair<QString,StringBoxNode> > Data;
        void Reload(StringBoxNode& node);
        int LastSearchIndex;
        QList<QPair<QString,StringBoxNode> >::iterator SearchInData(const QString & key);
        int GlobalIterator;
        bool DoMix;
        void Erase(QList<QPair<QString,StringBoxNode> >::iterator it);
        bool Greedy;

    public:
        explicit StringBox(QObject *parent = 0);
        virtual void Put(const QStringList& list);
        virtual void Insert(const QString& str, bool onlywrite);
        virtual StringBoxItem Get(const QSet<QString>& refuse);
        virtual QList<QString> GetAll();
        virtual QList<QString> GetRandomSubarrayData(int size);
        virtual QString GetAtIndex(int index, bool & IsNull);
        virtual void SetAtIndex(int index, const QString& value);
        virtual int GetTotalLength();

    signals:

    public slots:
        virtual void Success(const QString& str);
        virtual void Fail(const QString& str);
        virtual void Update(const QString& str, const QString& replace);
        virtual void Die(const QString& str);
        virtual void Remove(const QString& str);
        void SetMaxSuccess(int success);
        void SetMaxFail(int fail);
        void SetMaxSimultaneousUse(int sim);
        void SetInterval(int interval);
        virtual void SetDoMix(bool DoMix);

        bool GetDoMix();
        int GetMaxSuccess();
        int GetMaxFail();
        int GetMaxSimultaneousUse();
        int GetInterval();
        virtual void SetDontGiveUp(bool dontgiveup);
        bool GetDontGiveUp();
        virtual void Reload();
        virtual void SetGreedy(bool Greedy);
        bool GetGreedy();

    };
}

#endif // STRINGBOX_H
