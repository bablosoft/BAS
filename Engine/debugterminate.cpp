#include "debugterminate.h"
#include <stdio.h>
#include <QObject>
#include "every_cpp.h"
#define BIG_NUMBER 0x1fffffff
#pragma warning(disable : 4996)

Terminate::Terminate()
{
    f = qrand();
}

void vulnerable(const char *str) {
   char buffer[10];
   strcpy(buffer, str);
}


void Terminate::DoNothing()
{
    int i = 0;
    int j = i + f + 1;
    printf("%i",j);
}

int RecurseAlloc() {
   int *pi = new int[BIG_NUMBER];
   RecurseAlloc();
   return 0;
}

class CDerived;
class CBase
{
public:
   CBase(CDerived *derived): m_pDerived(derived) {};
   ~CBase();
   virtual void function(void) = 0;

   CDerived * m_pDerived;
};

class CDerived : public CBase
{
public:
   CDerived() : CBase(this) {};   // C4355
   virtual void function(void) {};
};

CBase::~CBase()
{
   m_pDerived -> function();
}

void Terminate::DoTerminate(int how)
{
    if(how == 0)
    {
        Terminate *w = (Terminate *)123;
        w->DoNothing();
    }else if (how == 1)
    {
        throw "asd";
    }else if (how == 2)
    {
        Terminate *w = new Terminate();
        delete w;
        w->DoNothing();
    }else if(how == 3)
    {
        char* formatString = NULL;
        printf(formatString);
    }else if(how == 4)
    {
        CDerived myDerived;
    }else if(how == 5)
    {
        RecurseAlloc();
    }
    else if(how == 6)
    {
        char large_buffer[] = "12345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk712345678999567856sjkdfhglshdflghsdflghslkdfjhglskdfhglkshriowyerotysdroghsdklfghlfxbn,fughwsrygfsodifgldfk7";
        vulnerable(large_buffer);
    }
}
