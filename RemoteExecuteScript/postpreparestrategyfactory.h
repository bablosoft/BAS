#ifndef POSTPREPARESTRATEGYFACTORY_H
#define POSTPREPARESTRATEGYFACTORY_H
#include "ipostpreparestrategyfactory.h"


class PostPrepareStrategyFactory : public IPostPrepareStrategyFactory
{
    Q_OBJECT
public:
    explicit PostPrepareStrategyFactory(QObject *parent = 0);
    virtual IPostPrepareStrategy* Create(const QString& type);
signals:

public slots:

};


#endif // POSTPREPARESTRATEGYFACTORY_H
