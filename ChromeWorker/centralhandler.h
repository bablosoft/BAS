#ifndef CENTRALHANDLER_H
#define CENTRALHANDLER_H

#include "include/cef_client.h"


class CentralHandler : public CefClient
{
public:
    CentralHandler();
    IMPLEMENT_REFCOUNTING(CentralHandler);

};

#endif // CENTRALHANDLER_H
