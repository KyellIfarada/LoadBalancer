//
// Created by lorenzo on 4/16/23.
//
//struct for representing the host
#include "LoadBalancer.h"
#include "LoadBalancer.c"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct host host;

struct job_node; //defined in LoadBalancer

//forward declarations for (public) functions

/**
* Initializes the host environment.
*/
host* host_create()
{
    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        struct job_node* batch_next;
        pthread_mutex_t lock;
    };
    struct host* newhost = (struct host*)malloc(sizeof(struct host));
    pthread_mutex_init(&newhost->lock,NULL);

    //  Crit Section
    //  pthread_mutex_unlock(&newhost->lock);



    return  newhost;
   /// Initialize any local variables, including mutexes.

}

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
/// DO THIS BEFORE LOADBALANCER DESTROY THIS IS YOUR SECOND TO LAST FUNCTION! :)
///Checks for remaining batches and completes them. Any mutexes created in host_init are destroyed.
void host_destroy(host** host)
{
    struct batchBunch
    {
        struct host** batch;
        struct host** batchBunch_next;

    };

    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        struct job_node* batch_next;
        pthread_mutex_t lock;
    };
    //Copy Host
    struct host* iter_copy  =(struct host*)*host;
    struct host* iter;
    struct host* tmp;
    iter = iter_copy->batch;
    while(iter_copy !=NULL) {
        while (iter != NULL) {
            tmp = &iter->batch_next;
            free(iter);
            iter = tmp;
        }
        iter_copy= iter_copy->batchBunch_next ;
    }

    free(host);
    host = NULL;
    pthread_mutex_destroy(&host);

    ///Uses a instance to complete any leftover jobs.
}

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host* h, struct job_node* batch)
        {
    printf( "LoadBalancer : Received batch and spinning up new instance . \n " );
    pthread_t tid;

     struct batchBunch
     {
     struct host** batch;
     struct host** batchBunch_next;

     };

     struct batchBunch* head;



    //Create Struct
    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        pthread_mutex_t lock;
    };

    //Pass Params
    struct host* newHost  =(struct h*)h;
    newHost->batch =(struct job_node*) batch;
    //Set iter to list
    struct job_node* iter = batch;
    //Process data
            //P_Thread_Create
            // pthread_mutex_lock(&newHost->lock);
    pthread_create(&tid, NULL,(void*)iter->data , NULL);

    //Calculation
    while( iter->next != NULL )
    {
       int TheData = iter->data;
        TheData = TheData*TheData;
       iter->data_result = &TheData;
       iter = iter->next;
    }
            //P_Thread_Join
    pthread_join(tid,iter->data_result);
    pthread_mutex_unlock(&newHost->lock);
    ///Each batch has a separate thread.
    //Add Bunch to BunchList
    newHost->batchBunch_next = head;
    head->batchBunch_next = newHost;

    ///Each job is processed and returned to the user correctly.
}