//
// linked_stack_main.c
//
//  Created by Gina Ackerman on 1/21/18.
//  Copyright © 2018 Gina Ackerman. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// forward declaration
typedef struct slist_node slist_node;
typedef struct stack stack;

// Stack node and the node creation function
struct slist_node {
   void *data;
   slist_node *next;
};

slist_node *create_stack_node(void *theData) {
   slist_node *nodePointer = (slist_node *) malloc(sizeof(slist_node));
   nodePointer->data = theData;
   nodePointer->next = NULL;
   return nodePointer;
}

// Stack and the correspoding operations
struct stack {
   slist_node *top;
   int numberOfItems;
};

/**************************************************
 * Function create_stack creates an empty stack.  *
 **************************************************/
stack *create_stack() {
   stack* theStack = (stack *)malloc(sizeof(stack));
   theStack->numberOfItems = 0;
   theStack->top = NULL;
   
   return theStack;
}

/**********************************************
 * Function isEmpty returns true if the stack *
 * is empty, or false otherwise.              *
 **********************************************/
bool is_empty(stack *theStack) {
   return (theStack->numberOfItems == 0);
};

/*****************************************************
 * Function push pushes the argument onto the stack. *
 *****************************************************/
void push(stack *theStack, void *theData) {
   slist_node *theNode = create_stack_node(theData);
   theNode->next = theStack->top;
   theStack->top = theNode;
   theStack->numberOfItems++;
};

/************************************************
 * Function pop removes the value at the top of *
 * of the stack.                                *
 ***********************************************/
void pop(stack *theStack) {
   if (is_empty(theStack)) {
      fprintf(stderr, "stack is empty\n");
   }
   else {
      slist_node *theNode = theStack->top;
      theStack->top = theNode->next;
      theStack->numberOfItems--;
      free(theNode);
   }
}

/***************************************************
 * Function top returns the top node in the stack. *
 **************************************************/
slist_node *top(stack *theStack) {
   slist_node *theNode = NULL;
   if (is_empty(theStack)) {
      fprintf(stderr, "stack is empty\n");
   }
   else {
      theNode = theStack->top;
   }
   return theNode;
}

/*********************************************************
 * Function printAll prints the address of all elements. *
 ********************************************************/
void printAll(stack *theStack) {
   if (is_empty(theStack)) {
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
