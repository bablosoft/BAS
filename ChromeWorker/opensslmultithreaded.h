#ifndef OPENSSLMULTITHREADED_H
#define OPENSSLMULTITHREADED_H

#include <mutex>
#include <curl/curl.h>
#include <openssl/ssl.h>

static std::mutex* aMutex;

void locking_function(int mode, int n, const char* file, int line)
{
    if(mode & CRYPTO_LOCK){
        aMutex[n].lock();
    }
    else{
        aMutex[n].unlock();
    }
}

unsigned long id_function()
{
    return (unsigned long)std::hash<std::thread::id>()   (std::this_thread::get_id());
}

int thread_setup()
{
    aMutex = new std::mutex[CRYPTO_num_locks()];
    curl_global_init(CURL_GLOBAL_ALL);

    if(!aMutex)
        return 0;
    else{
        CRYPTO_set_id_callback(id_function);
        CRYPTO_set_locking_callback(locking_function);
    }
    return 1;
}

int thread_cleanup()
{
    if(!aMutex)
        return 0;

    curl_global_cleanup();
    CRYPTO_set_id_callback(NULL);
    CRYPTO_set_locking_callback(NULL);
    delete[] aMutex;
    aMutex = NULL;
    return 1;
}


#endif // OPENSSLMULTITHREADED_H
