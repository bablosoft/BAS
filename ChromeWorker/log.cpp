#include "log.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

bool write_logs = false;

bool is_write_logs()
{
    return write_logs;
}

std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}

void worker_log_init(bool do_write)
{
    write_logs = do_write;
    if(write_logs)
    {
        try
        {
           std::remove("worker_log.txt");
        }catch(...)
        {

        }

        try
        {
           std::remove("network_log.txt");
        }catch(...)
        {

        }
    }
}


void network_log(const std::string& text)
{
    if(!write_logs || text.length() > 3000)
        return;
    try
    {
        std::ofstream outfile;

        outfile.open("network_log.txt", std::ios_base::app);
        outfile<<text<<std::endl;

    }catch(...)
    {

    }
}


void worker_log(const std::string& text)
{
    if(!write_logs)
        return;
    try
    {
        std::ofstream outfile;

        outfile.open("worker_log.txt", std::ios_base::app);
        outfile<< "[" <<currentDateTime()<<"] "<< text<<std::endl;

    }catch(...)
    {

    }
}

void worker_log_thread()
{
    if(!write_logs)
        return;

    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string mystring = ss.str();
    worker_log(std::string("CurrentThread<<") + mystring);
}

