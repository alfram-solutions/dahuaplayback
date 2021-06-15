#ifndef DHMUTEX_H
#define DHMUTEX_H

#include <pthread.h>

class DHMutex
{
public:
    DHMutex();
    ~DHMutex();

    int Lock();
    int UnLock();

private:
    pthread_mutex_t m_mutex;
};

#endif // DHMUTEX_H
