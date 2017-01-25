#ifndef ISOLVER_H
#define ISOLVER_H
#include "engine_global.h"

#include <QObject>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ISolver : public QObject
    {
        Q_OBJECT
    public:
        explicit ISolver(QObject *parent = 0);


    signals:
        void Done(const QString& val, const QString& id, bool res,const QString& solver_id);
        void Used();
        void Failed();
    public slots:
        virtual bool TimeLimited() = 0;
        virtual QString Solve(const QString& base64,const QStringList& props) = 0;
        virtual void ReportBad(const QString& id) = 0;
    };
}

#endif // ISOLVER_H
