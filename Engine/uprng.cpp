#include "uprng.h"
#include <math.h>
//#include <QDebug>
#include "every_cpp.h"

bool is_prime(int const v)
{
    int const v_sqrt = sqrt(v);
    for (int d = 3; d <= v_sqrt; d++) {
        if ((v % d) == 0) {
            return false;
        }
    }
    return true;
}

int find_next_prime(int const v)
{
    int p;
    if ((v & 1) == 0) {
        p = v + 1;
    }
    else {
        p = v;
    }

    while (true) {
        if (is_prime(p)) {
            return p;
        }
        p += 2;
    }

    return 0;
}

int gcd(int a, int b)
{
    int c;
    while (a != 0) {
        c = a;
        a = b%a;
        b = c;
    }
    return b;
}


int random_prime(int const n)
{

    int ret, g;
    do {
        //qrand() % ((max + 1) - min) + min
        //ret = rand_eng(0, n-2);
        if(n == 2)
            ret = 1;
        else
            ret = qrand() % (n-2) + 1;
        g = gcd(ret, n);
    }
    while (g != 1);

    return ret;
}



UPRNG::UPRNG(QObject *parent) :
    QObject(parent)
{
}

void UPRNG::Init(int Max)
{
    _max = Max;
    if(_max == 0)
        return;

    //qrand() % ((max + 1) - min) + min
    //_a = rand_eng(1, max-1);
    //_b = rand_eng(0, max-1);
    if(Max == 1)
        _a = 1;
    else
        _a = qrand() % (Max - 1) + 1;
    _b = qrand() % Max;


    init_prime(Max);
    _c = random_prime(_prime-1);
    //qrand() % ((max + 1) - min) + min
    //_n = rand_eng(1, 4);
    _n = qrand() % 4 + 1;


    //qDebug() << Max << " " << _prime << " " << _a << " " << _b << " " << _c << " " << _n ;

    _cur_step = 0;
}


int UPRNG::GenerateNext()
{
    if(_max == 0)
        return 0;
    int res;
    do
    {
        int pos = _cur_step++;
        if (_cur_step == _prime) {
            _cur_step = 0;
        }

        res = get_step(pos);
    }
    while (res >= _max);

    return res;
}

int UPRNG::get_step(int const step)
{
    int ret = step;
    for (int i = 0; i < _n; i++) {
        ret = g(l(ret, _a, _b, _prime), _c, _prime);
    }
    return ret;
}


void UPRNG::init_prime(int const max)
{
    _prime = find_next_prime(max);
}

int UPRNG::l(int X, int a, int b, int p)
{
    return (( unsigned long long)a*(unsigned long long)X+( unsigned long long)b)%p;
}

int UPRNG::g(int X, int c, int p)
{
    int r = 1;
    while (c > 0) {
        if ((c & 1) == 1) {
            r = ((unsigned long long)r*(unsigned long long)X) % p;
        }
        c >>= 1;
        X = ((unsigned long long)X*(unsigned long long)X) % p;
    }
    return r;
}
