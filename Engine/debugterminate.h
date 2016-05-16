#ifndef DEBUGTERMINATE_H
#define DEBUGTERMINATE_H

class Terminate
{
public:
    Terminate();
    void DoTerminate(int how);
private:
    int f;
    void DoNothing();
};

#endif // DEBUGTERMINATE_H
