#ifndef IPOSTPREPARESTRATEGYFACTORY_H
#define IPOSTPREPARESTRATEGYFACTORY_H
#include <QObject>
#include "ipostpreparestrategy.h"


class IPostPrepareStrategy;
class IPostPrepareStrategyFactory : public QObject
{
    Q_OBJECT
public:
    explicit IPostPrepareStrategyFactory(QObject *parent = 0);
    virtual IPostPrepareStrategy* Create(const QString& type) = 0;
signals:

public slots:

};


#endif // IPOSTPREPARESTRATEGYFACTORY_H
