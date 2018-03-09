//
//  discounts.c
//  Assignment4_SharedMemory
//

// TODO: Include additional header files
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SIZE 5

// Function prototypes
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest);
void compute_discounts(float price[], float discount[]);
void display_discounts(void);

int main()
{
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
   float discounts[SIZE] = {5, 10, 15, 20, 25};

   /* TODO: Error check to make sure the child was successfully created */
   int pid = fork();
   switch(pid)
   {
    case -1:
      perror("Could not fork the process");
      exit(-1);
      break;
    case 0:
      compute_discounts(prices,discounts);
      break;
    default:
      wait(NULL);
      display_discounts();
      break;
   }
   /*** TODO: If I am child, I will do this: ****/
   /* Compute the total sale, the average, lowest and highest prices
    * for the five items for each discount rate
    */
   
   /*** TODO: If I am a parent, I will do the following ***/
   /* Wait for my child process to compute and share the computed data, then
    * display the data
    */
   
   return 0;
}

/*******************************************************************
 * Calculate the highest and lowest numbers in the given array.    *
 ******************************************************************/
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest) {
   int ix;
   if (numItems < 0) {
      printf("No scores to calculate highest and lowest\n");
      *highest = 0;
      *lowest = 0;
      return;
   }
   *highest = numbers[0];
   *lowest = numbers[0];
   for (ix = 0; ix < numItems; ix++) {
      if (numbers[ix] > *highest) {
         *highest = numbers[ix];
      }
      else if (numbers[ix] < *lowest) {
         *lowest = numbers[ix];
      }
   }
}

/*******************************************************************
 * Calculate the total sale and the average, lowest and highest    *
 * prices for each item.                                           *
 * Establish the shared-memory object and share the computed data. *
 ******************************************************************/
void compute_discounts(float price[], float discount[]) {

  /* TODO:
     * Create the write shared memory segment.
     * Terminate the program if error.
     */
    int shm_fd;
    void *ptr;
    const char *name = "OS";

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        printf("shared memory failed\n");
        exit(-1);
    }
    /* TODO: Configure the size of the shared memory segment */
    ftruncate(shm_fd, SIZE);
    
    /* TODO: Map the shared memory segment in the address space of the process.
     *       Terminate if fail to map.
     */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Failed to map");
        exit(-1);
    }
    /**
     * TODO:
     * Calculate the total sale, the average, lowest and highest price for each
     * item for each discount: 5%, 10%, 15%, 20%, 25%
     */
    int i,j;
    float average = 0;
    float total = 0;
    float highest_price;
    float lowest_price;

    for (i = 0; i < SIZE; i++)
    {
      price[i] = price[i] * 1.0 - (discount[i] / 100.0);
      total += price[i];
    }
    average = total / (float)SIZE;
    compute_lowest_highest(SIZE, price, &highest_price, &lowest_price);
    
    /**
     * TODO: write the percentage discount, total sale, average price, lowest and
     * highest prices to the shared memory region.
     *
     * Note: must increment the value of ptr after each write.
*/
}

/*******************************************************************
 * Output and display the computed total sale and the average,     *
 * lowest and highest prices for each item.                        *
 * Open the read-only shared-memory object and read data from the  *
 * shared memory region, then remove the shared memory segment.    *
 ******************************************************************/
void display_discounts(void) {
  
   /* TODO: open the read-only shared memory segment.
    * Terminate the program if error.
    */
   
   /* TODO: Map the shared memory segment in the address space of the process
    *       Terminate if fail to map.
    */
   
   /* TODO: Print header */

   /* TODO: read from the shared memory region */
   
   /* TODO: Remove the shared memory segment. Terminate the program if error.
    */
}
