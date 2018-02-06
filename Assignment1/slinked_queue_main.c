//
// linked_queue_main.c
//
// John Lee 893003137
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// forward declaration
typedef struct slist_node slist_node;
typedef struct queue queue;

// Queue node and the node creation function
struct slist_node {
    void *data;
    slist_node *next;
};

/*****************************************************************
 * Function create_queue_node creates a node with the given data *
 ****************************************************************/

slist_node *create_queue_node(void *theData) {
    slist_node *nodePointer = (slist_node *) malloc(sizeof(slist_node));
    nodePointer->data = theData;
    nodePointer->next = NULL;
    return nodePointer;
}

// Singly linked list queue and the correspoding operations
struct queue {
    slist_node *top;
    slist_node *tail;
    int numberOfItems;
};

/**************************************************
 * Function create_queue creates an empty queue.  *
 **************************************************/
queue *create_ready_queue() {
   queue* theQueue = (queue *)malloc(sizeof(queue));
   theQueue->numberOfItems = 0;
   theQueue->top = NULL;
   theQueue->tail = NULL;

   return theQueue;
}

/**********************************************
 * Function isEmpty returns true if the queue *
 * is empty, or false otherwise.              *
 **********************************************/
bool is_empty(queue *theQueue) {
  return (theQueue->numberOfItems == 0);

};

/*****************************************************
 * Function enqueue pushes the argument onto the queue. *
 *****************************************************/
void enqueue(queue *theQueue, void *theData) {
    slist_node *theNode = create_queue_node(theData);
    if(theQueue->numberOfItems > 0)
    {
        theQueue->tail->next = theNode;
    }
    else{
        //first insertion
        theQueue->top = theNode;
    }
    theQueue->tail = theNode;
    theQueue->numberOfItems++;
};


/************************************************
 * Function dequeue removes the value at the top of *
 * of the queue.                                *
 ***********************************************/
void dequeue(queue *theQueue) {
    if (is_empty(theQueue)) {
        fprintf(stderr, "queue is empty\n");
    }
    else {
        slist_node *theNode = theQueue->top;
        if(theQueue->numberOfItems == 2)
            theQueue->tail = theNode->next;
        theQueue->top = theNode->next;
        theQueue->numberOfItems--;
        free(theNode);
    }
}

/**********************************************************************
 * Function top returns the top node in the queue without removing it *
 **********************************************************************/
slist_node *top(queue *theQueue) {
    slist_node *theNode = NULL;
    if (is_empty(theQueue)) {
        fprintf(stderr, "queue is empty\n");
    }
    else {
        theNode = theQueue->top;
    }
    return theNode;
    
}

/**********************************************************************
 * Function back returns the tail node in the queue without removing it *
 **********************************************************************/
slist_node *tail(queue *theQueue) {
    slist_node *theNode = NULL;
    if (is_empty(theQueue)) {
        fprintf(stderr, "queue is empty\n");
    }
    else {
        theNode = theQueue->tail;
    }
    return theNode;
}


/*********************************************************
 * Function printAll prints the address of all elements. *
 ********************************************************/
void printAll(queue *theQueue) {
    if (is_empty(theQueue)) {
        printf("queue is empty\n");
        return;
    }
    
    slist_node *theNode = (slist_node *)top(theQueue);
    while (theNode != NULL) {
        printf("%p\n", theNode->data);
        theNode = theNode->next;
    }
    printf("\n");
}

/*********************************************************
 * Function printAll prints the address of all elements. *
 ********************************************************/
void printAllIntegers(queue *theQueue) {
    if (is_empty(theQueue)) {
        printf("queue is empty\n");
        return;
    }
    
    slist_node *theNode = (slist_node *)top(theQueue);
    printf("My current queue: { ");
    while (theNode != NULL) {
        printf("%i ", *((int *) theNode->data));
        theNode = theNode->next;
    }
    printf("}\n");

}

/****************************************************
 * Function size returns the size of the queue.     *
 ***************************************************/
int size(queue *theQueue) {
    return theQueue->numberOfItems;
}

int main() {
  // create an array queue
  queue *intQueue = create_ready_queue();

  int i;

  // add 2 elements to queue
  int numbers[] = {5,3,7,9,0};
  int nItems = sizeof(numbers)/sizeof(numbers[0]);

  int *theInteger;
  slist_node *topElement;
  slist_node *tailElement;

  for(i = 0; i < nItems; i++)
  {
    enqueue(intQueue, &numbers[i]);
  }
   
   // check if queue is not empty
   printf("Is array queue empty (1=yes, 0=no)? %i\n", is_empty(intQueue));
   
   // get the current queue size
   printf("Array queue size after %i inserstions: %i\n",
          intQueue->numberOfItems, intQueue->numberOfItems);
   
   // print all elements
   printAllIntegers(intQueue);
   
   // print all elements' pointers
   printf("\n");
   printf("Address Values:\n");
   printAll(intQueue);
   

   for (i = 0; i < nItems; i++) {
      // print all elements
      printAllIntegers(intQueue);

      // check the front of queue
      topElement = top(intQueue);
      if (topElement != NULL) {
         theInteger = (int *) topElement->data;
         printf("top element value: %i\n", *(theInteger));
      }
      // check the back of queue
      tailElement = tail(intQueue);
      if (tailElement != NULL) {
         theInteger = (int *) tailElement->data;
         printf("tail element value: %i\n", *(theInteger));
      }

      dequeue(intQueue);
      printf("Queue size after dequeue: %i\n\n", intQueue->numberOfItems);

      
   }
   
   free(intQueue);
   return 0;
}

