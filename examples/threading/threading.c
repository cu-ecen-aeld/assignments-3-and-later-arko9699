#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data *thread_args = (struct thread_data *) thread_param;

    usleep(thread_args->wait_to_obtain);

    if (pthread_mutex_lock(thread_args->mutex) != 0) {
        ERROR_LOG("Could not obtain mutual exclusion");
        thread_args->thread_complete_success = false;
        return thread_param;
    }

    usleep(thread_args->wait_to_release);

    if (pthread_mutex_unlock(thread_args->mutex) != 0) {
        ERROR_LOG("Could not unlock mutual exclusion");
        thread_args->thread_complete_success = false;
        return thread_param;
    }

    thread_args->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    struct thread_data *tdata = malloc(sizeof(struct thread_data));
    if (!tdata) {
        ERROR_LOG("Failed to allocate memory to thread");
        return false;
    }

    tdata->mutex = mutex;
    tdata->wait_to_obtain = wait_to_obtain_ms;
    tdata->wait_to_release = wait_to_release_ms;
    tdata->thread_complete_success = false;

    if (pthread_create(thread, NULL, threadfunc, tdata) != 0) {
        ERROR_LOG("Failed to create new thread");
        free(tdata);
        return false;
    }

    return true;
}

