//
// Created by lorenzo on 4/16/23.
//
#include "InstanceHost.c"
#include "InstanceHost.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//struct for representing the load balancer


//structure to track jobs as they are created. serves as list node.
/*
struct job_node {
    int user_id;          //unique id of user
    int data;             //input data provided by user.
    int* data_result;     //pointer to place in global memory to store result.
    //negative one (-1) means result not computed.
    struct job_node* next;//pointer to the next job in a list of jobs.
};
*/
//forward declarations for (public) functions

/**
 * Initializes the load balancer. Takes batch size as parameter.
 */
balancer* balancer_create(int batch_size)
{
    ///  Properly initialized the batch size and mutex
    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        struct job_node* batch_next;
        pthread_mutex_t lock;
    };

    struct balancer {
       int batch_count;
       int batch_limit;
       host** somehost;
       pthread_mutex_t list_lock;
       struct job_node *head;
   };

//Instantiate New Balancer
   struct balancer* lb = (struct balancer*)malloc(sizeof(struct balancer));
   lb->batch_limit = batch_size;

//Intitialize Mutex
    pthread_mutex_init(&lb->list_lock,NULL);

    //Instantiate new Host to host servers
    lb->somehost= host_create();

    //  Return your new balancer/Host instantiation
        return lb;
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_destroy(balancer** lb)
{
    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        struct job_node* batch_next;
        pthread_mutex_t lock;
    };

    struct balancer {
        int batch_count;
        int batch_limit;
        host* somehost;
        pthread_mutex_t list_lock;
        struct job_node *head;
    };
///Shuts down the load balancer.


    struct balancer* ThisBalancer =(struct balancer*) lb;
    ;

  //  void host_destroy(lb->somehost**);
  if((( ThisBalancer->batch_count > ThisBalancer->batch_limit) % ThisBalancer->batch_limit) < ThisBalancer->batch_limit )
  {
      {
          struct job_node* list = (struct job_node*)malloc(sizeof(struct job_node));
          list->next = ThisBalancer->head;
          while (list->next != NULL) {
              list->user_id = ThisBalancer->head->user_id;
              list->data = ThisBalancer->head->data;
              list->data_result = ThisBalancer->head->data_result;
              list = list->next;

          }
          host_request_instance( ThisBalancer->somehost,  list);
      }
  }
  else{

      struct job_node* iter = ThisBalancer->head;
      while(iter !=NULL )
      {
         struct job_node* tmp = iter->next;
          free(iter);
          iter = (tmp);

      }
      free(ThisBalancer);
      ThisBalancer = NULL;

  }
    pthread_mutex_destroy( &lb);
}

/**
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 *
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */
void balancer_add_job(balancer* lb, int user_id, int data, int* data_return) {



    struct host
    {
        struct jobnode** batchBunch_next;
        struct job_node* batch;
        struct job_node* batch_next;
        pthread_mutex_t lock;
    };

     struct balancer {
       int batch_count;
       int batch_limit;
       host* somehost;
       pthread_mutex_t list_lock;
       struct job_node *head;
   };




     struct balancer* ThisBalancer =(struct balancer*) lb;
    /// Do we run our do-while for only one job add at a time or add all jobs until batch limit is completed?
    ///Jobs are inserted in the batch correctly while being protected by a mutex.

    printf("LoadBalancer : Received new job from user #%d to process data=%d and store it at %p.\n", user_id, data,
           data_return);
    struct job_node *newjob = (struct job_node *) malloc(sizeof(struct job_node));
    newjob->user_id = user_id;
    newjob->data = data;
    newjob->data_result = data_return;

    if(ThisBalancer->batch_count != ThisBalancer->batch_limit)
    {
        pthread_mutex_lock(&ThisBalancer-> list_lock);
        newjob->next = ThisBalancer->head;
        ThisBalancer->head = newjob;
        ThisBalancer->batch_count++;
        pthread_mutex_unlock(&ThisBalancer);
    }

        ///When enough jobs have been added, creates a batch and sends it to instance host
        if (ThisBalancer->batch_count == ThisBalancer->batch_limit)
        {
                struct job_node* list = (struct job_node*)malloc(sizeof(struct job_node));
                list->next = ThisBalancer->head;
                while (list->next != NULL) {
                    list->user_id = ThisBalancer->head->user_id;
                    list->data = ThisBalancer->head->data;
                    list->data_result = ThisBalancer->head->data_result;
                    list = list->next;

                                            }

             host_request_instance( ThisBalancer->somehost,  list);

        }
        else if (((ThisBalancer->batch_count > ThisBalancer->batch_limit) % ThisBalancer->batch_limit) < ThisBalancer->batch_limit  )
        {
            struct job_node* list = (struct job_node*)malloc(sizeof(struct job_node));
            list->next = ThisBalancer->head;
            while (list->next != NULL) {
                list->user_id = ThisBalancer->head->user_id;
                list->data = ThisBalancer->head->data;
                list->data_result = ThisBalancer->head->data_result;
                list = list->next;

            }

            host_request_instance( ThisBalancer->somehost,  list);
        }

}