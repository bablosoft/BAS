#ifndef ISTRINGBOX_H
#define ISTRINGBOX_H
#include "engine_global.h"

#include <QObject>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IStringBox : public QObject
    {
        Q_OBJECT
    public:
        struct StringBoxItem
        {
            QString Value;
            enum StringBoxItemStatus{Ready = 0,Wait = 1,NotAvailable = 2,Refused};
            StringBoxItemStatus Status;
        };
        explicit IStringBox(QObject *parent = 0);
        virtual void Put(const QStringList& list) = 0;
        virtual StringBoxItem Get(const QSet<QString>& refuse) = 0;
        virtual QList<QString> GetAll() = 0;

        virtual QList<QString> GetRandomSubarrayData(int size) = 0;
        virtual QString GetAtIndex(int index, bool & IsNull) = 0;
        virtual void SetAtIndex(int index, const QString& value) = 0;
        virtual int GetTotalLength() = 0;


    signals:
        void Removed(const QString& line);
        void NeedToUpdate();
        void Inserted(const QString& str);
    public slots:
        virtual void Success(const QString& str) = 0;
        virtual void Fail(const QString& str) = 0;
        virtual void Update(const QString& str, const QString& replace) = 0;
        virtual void Die(const QString& str) = 0;
        virtual void Remove(const QString& str) = 0;
        virtual void SetDontGiveUp(bool dontgiveup) = 0;
        virtual void Reload() = 0;
        virtual void SetDoMix(bool DoMix) = 0;
        virtual void SetGreedy(bool Greedy) = 0;
        virtual void Insert(const QString& str, bool onlywrite) = 0;
    };
}

#endif // ISTRINGBOX_H
