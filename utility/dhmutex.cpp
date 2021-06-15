#include "dhmutex.h"

DHMutex::DHMutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&m_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

DHMutex::~DHMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

int DHMutex::Lock()
{
    return pthread_mutex_lock(&m_mutex);
}

int DHMutex::UnLock()
{
    return pthread_mutex_unlock(&m_mutex);
}
