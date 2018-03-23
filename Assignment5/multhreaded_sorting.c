/**
 * Multithreaded Sorting Application
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 * John Lee 893003137
 * Chloe Ho 890712797
 * Long Nguyen 893548198
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE               10
#define NUMBER_OF_THREADS  3

/* thread that performs basic sorting algorithm */
void *sorter(void *params);
/* thread that performs merging of results */
void *merger(void *params);

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
    int from_index;
    int to_index;
} parameters;

int main (int argc, const char * argv[])
{
    int i;
    
    printf("\nORIGINAL: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d  ",list[i]);
    }
    printf("\n");
    

    pthread_t workers[NUMBER_OF_THREADS];
    pthread_attr_t attr;
    parameters data;
    
    /* get the default attributes */
    pthread_attr_init(&attr);
    
    //establish the first sorting thread
    pthread_create(&workers[0], &attr, sorter, &(parameters) { 0, (SIZE/2)-1});
    
    //establish the second sorting thread
    pthread_create(&workers[1], &attr, sorter, &(parameters) { (SIZE/2), SIZE - 1});
    
    //wait for the 2 sorting threads to finish
    for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
        pthread_join(workers[i], NULL);
    
    //establish the merge thread
    pthread_create(&workers[2], &attr, merger, &(parameters) { 0, (SIZE-1)});
    
    //wait for the merge thread to finish
    pthread_join(workers[2], NULL);
    
    /* output the sorted array */
    printf("\nSORTED: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d  ",result[i]);
    }
    printf("\n\n");
    
    return 0;
}

/**************************************************************
 * Sorting thread                                             *
 * This thread can essentially use any algorithm for sorting. *
 *************************************************************/
void *sorter(void *params)
{
    // Insert your sorting algorithm
    // TODO: replace 'return NULL' with exit thread

    parameters* p = (parameters *)params;
    
    //SORT
    
    int begin = p->from_index;
    int end = p->to_index+1;
    
    int temp=0;
    
    for(int i=begin; i< end; i++)
    {
        for(int j=begin; j< end-1; j++)
        {
            
            if(list[j] > list[j+1])
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
                
            }
        }
    }
    
    for(int i=begin; i<end; i++)
    {
        result[i] = list[i];
    }
    
    pthread_exit(NULL);
}

/*************************************************************
 * Merge thread                                              *
 * Uses simple merge sort for merging two sublists.          *
 ************************************************************/
void *merger(void *params)
{
    // Insert your merging algorithm
    // TODO: replace 'return NULL' with exit thread
    parameters* p = (parameters *)params;
    int begin = p->from_index;
    int end = p->to_index+1;
    
    int temp;
    for(int i=begin; i< end; i++)
    {
        for(int j=begin; j< end-1; j++)
        {
            if(result[j] > result[j+1])
            {
                temp= result[j];
                result[j] = result[j+1];
                result[j+1] = temp;
                
            }
        }
    }

    // printf("\n\nFINAL RESULT IS:\n");
    // for(int d=begin+1; d<end; d++)
    // {
    //     printf("The final resulting array is: %d\n", result[d]);
    // }

    pthread_exit(NULL);}
