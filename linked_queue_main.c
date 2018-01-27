//
// linked_queue_main.c
//
//  Created by Gina Ackerman on 1/21/18.
//  Copyright © 2018 Gina Ackerman. All rights reserved.
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

slist_node *create_queue_node(void *theData) {
   slist_node *nodePointer = (slist_node *) malloc(sizeof(slist_node));
   nodePointer->data = theData;
   nodePointer->next = NULL;
   return nodePointer;
}

// Queue and the correspoding operations
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
   slist_node *theTmpNode = create_queue_node(theData);
   slist_node *theNode = create_queue_node(theData);
   
   if(is_empty(theQueue))
   {
      theNode->next = NULL;
      theQueue->tail = theNode;
      theQueue->top = theNode;
      theQueue->numberOfItems++;   
      return;
   }

   theQueue->tail->next = theNode;
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

/***************************************************
 * Function top returns the top node in the queue. *
 **************************************************/
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
   // create a queue
   queue *intQueue = create_ready_queue();
   // add 3 elements to queue
   int number5 = 5;
   enqueue(intQueue, &number5);
   int number3 = 3;
   enqueue(intQueue, &number3);
   int number1 = 1;
   enqueue(intQueue, &number1);
   
   // check if queue is not empty
   bool isEmpty = is_empty(intQueue);
   printf("Is queue empty (1=yes, 0=no)? %i\n", isEmpty);
   
   // get the current queue size
   printf("Queue size after 3 inserstions: %i\n",
          intQueue->numberOfItems);
   
   // print all elements
   printAllIntegers(intQueue);
   
   // top element
   slist_node *topElement = top(intQueue);
   // printf("top element: %p\n", topElement->data);
   int *theInteger = (int *) topElement->data;
   printf("top element value: %i\n\n", *(theInteger));

   // pop the top element
   dequeue(intQueue);
   // get the current queue size
   printf("Queue size after dequeue: %i\n", intQueue->numberOfItems);

   // print all elements
   printAllIntegers(intQueue);

   // get and print the top element
   topElement = top(intQueue);
   theInteger = (int *) topElement->data;
   printf("Top element: %i\n", *(theInteger));

   
   printf("\n");


   // pop the top element
   dequeue(intQueue);
   printAllIntegers(intQueue);
   // get the current queue size
   printf("Queue size after dequeue: %i\n", intQueue->numberOfItems);
   // get and print the top element
   topElement = top(intQueue);
   theInteger = (int *) topElement->data;
   printf("Top element: %i\n", *(theInteger));
   
   free(intQueue);

   return 0;
}
