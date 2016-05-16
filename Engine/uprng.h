#ifndef UPRNG_H
#define UPRNG_H

#include <QObject>

class UPRNG : public QObject
{
    Q_OBJECT
    int _prime;
    int _max;
    int _a;
    int _b;
    int _c;
    int _n;
    int _cur_step;

public:
    explicit UPRNG(QObject *parent = 0);
    void Init(int Max);
    int GenerateNext();
private:
    int get_step(int const step);
    void init_prime(int const max);
    int l(int X, int a, int b, int p);
    int g(int X, int c, int p);

};

#endif // UPRNG_H
