#include "ihttpclient.h"
IHttpClient::IHttpClient(QObject *parent) :
    QObject(parent)
{
}

PostOptions::PostOptions()
{
    PrepareStrategy = "multipart";
}


