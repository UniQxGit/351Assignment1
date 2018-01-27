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

// Stack node and the node creation function
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

// Stack and the correspoding operations
struct queue {
   slist_node *top;
   int numberOfItems;
};

/**************************************************
 * Function create_stack creates an empty stack.  *
 **************************************************/
queue *create_queue() {
   stack* thequeue = (queue *)malloc(sizeof(queue));
   theQueue->numberOfItems = 0;
   theQueue->top = NULL;
   
   return theQueue;
}

/**********************************************
 * Function isEmpty returns true if the stack *
 * is empty, or false otherwise.              *
 **********************************************/
bool is_empty(queue *theQueue) {
   return (theQueue->numberOfItems == 0);
};

/*****************************************************
 * Function push pushes the argument onto the stack. *
 *****************************************************/
void push(queue *theQueue, void *theData) {
   slist_node *theNode = create_stack_node(theData);
   theNode->next = theQueue->top;
   theQueue->top = theNode;
   theQueue->numberOfItems++;
};

/************************************************
 * Function pop removes the value at the top of *
 * of the stack.                                *
 ***********************************************/
void pop(queue *theQueue) {
   if (is_empty(theQueue)) {
      fprintf(stderr, "queue is empty\n");
   }
   else {
      slist_node *theNode = theQueue->top;
      theQueue->top = theNode->next;
      theQueue->numberOfItems--;
      free(theNode);
   }
}

/***************************************************
 * Function top returns the top node in the stack. *
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
void printAll(stack *theQueue) {
   if (is_empty(theQueue)) {
      printf("stack is empty\n");
      return;
   }
   
   slist_node *theNode = (slist_node *)top(theStack);
   while (theNode != NULL) {
      printf("%p\n", theNode->data);
      theNode = theNode->next;
   }
   printf("\n");
}

/*********************************************************
 * Function printAll prints the address of all elements. *
 ********************************************************/
void printAllIntegers(stack *theStack) {
   if (is_empty(theStack)) {
      printf("stack is empty\n");
      return;
   }
   
   slist_node *theNode = (slist_node *)top(theStack);
   printf("My current stack: { ");
   while (theNode != NULL) {
      printf("%i ", *((int *) theNode->data));
      theNode = theNode->next;
   }
   printf("}\n");
}

/****************************************************
 * Function size returns the size of the stack.     *
 ***************************************************/
int size(stack *theStack) {
   return theStack->numberOfItems;
}

int main() {
   // create a stack
   stack *intStack = create_stack();
   // add 2 elements to stack
   int number5 = 5;
   push(intStack, &number5);
   int number3 = 3;
   push(intStack, &number3);
   
   // check if stack is not empty
   bool isEmpty = is_empty(intStack);
   printf("Is stack empty (1=yes, 0=no)? %i\n", isEmpty);
   
   // get the current stack size
   printf("Stack size after 2 inserstions: %i\n",
          intStack->numberOfItems);
   
   // print all elements
   printAllIntegers(intStack);
   
   // top element
   slist_node *topElement = top(intStack);
   // printf("top element: %p\n", topElement->data);
   int *theInteger = (int *) topElement->data;
   printf("top element value: %i\n\n", *(theInteger));

   // pop the top element
   pop(intStack);
   // get the current stack size
   printf("Stack size after pop: %i\n", intStack->numberOfItems);

   // print all elements
   printAllIntegers(intStack);

   // get and print the top element
   topElement = top(intStack);
   theInteger = (int *) topElement->data;
   printf("Top element: %i\n", *(theInteger));

   free(intStack);
   printf("\n");
   return 0;
}
