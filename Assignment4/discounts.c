//
//  discounts.c
//  Assignment4_SharedMemory
//

// TODO: Include additional header files
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SIZE 5

// Function prototypes
void compute_lowest_highest(int numItems, float numbers[], float *highest, float *lowest);
void compute_sum_average(int numItems, float numbers[], float *sum, float *average);
void compute_discounts(float price[], float discount[]);
void display_discounts(void);

int main()
{
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
   float discounts[SIZE] = {5, 10, 15, 20, 25};
   float total_sale, average_price, highest_price, lowest_price;


   /* TODO: Error check to make sure the child was successfully created */
   
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("Failed to fork\n");
        return -1;
    }
   /*** TODO: If I am child, I will do this: ****/
   /* Compute the total sale, the average, lowest and highest prices
    * for the five items for each discount rate
    */
    else if (pid == 00)
    {
        
    }
   /*** TODO: If I am a parent, I will do the following ***/
   /* Wait for my child process to compute and share the computed data, then
    * display the data
    */
    else if (pid > 0)
    {
        wait(NULL);
    }
   return 0;
}

/*******************************************************************
 * Calculate the highest and lowest numbers in the given array.    *
 ******************************************************************/
void compute_lowest_highest(int numItems, float numbers[], float *highest, float *lowest)
{
   int ix;
   if (numItems < 0)
   {
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

void compute_sum_average(int numItems, float numbers[], float *sum, float *average)
{
    int i;
    *sum = 0.0;
    for (i = 0; i < numItems; i++)
    {
        *sum += numbers[i];
    }
    *average = *sum / numItems;
}

/*******************************************************************
 * Calculate the total sale and the average, lowest and highest    *
 * prices for each item.                                           *
 * Establish the shared-memory object and share the computed data. *
 ******************************************************************/
void compute_discounts(float price[], float discount[])
{

   /* TODO:
    * Create the write shared memory segment.
    * Terminate the program if error.
    */
    int shm_fd
    void *ptr;
    
    shm_fd = shm_open(name, O_CREATE | O_RDWR, 0666);
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
    ptr = map(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Map failed\n");
        return -1;
    }
   /**
    * TODO:
    * Calculate the total sale, the average, lowest and highest prices for each
    * item for each discount: 5%, 10%, 15%, 20%, 25%
    */
    int i;
    
    switch (discount[SIZE])
    {
        case 5:
            for (i = 0; i < SIZE; i++)
                prices[i] = prices[i] * 0.95;
            
            compute_sum_average(SIZE, prices, &total_sale, &average_price);
            compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
            break;
            
        case 10:
            for (i = 0; i < SIZE; i++)
                prices[i] = prices[i] * 0.9;
            
            compute_sum_average(SIZE, prices, &total_sale, &average_price);
            compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
            break;
            
        case 15:
            for (i = 0; i < SIZE; i++)
                prices[i] = prices[i] * 0.85;
            
            compute_sum_average(SIZE, prices, &total_sale, &average_price);
            compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
            break;
            
        case 20:
            for (i = 0; i < SIZE; i++)
                prices[i] = prices[i] * 0.8;
            
            compute_sum_average(SIZE, prices, &total_sale, &average_price);
            compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
            break;
            
        case 25:
            for (i = 0; i < SIZE; i++)
                prices[i] = prices[i] * 0.75;
            
            compute_sum_average(SIZE, prices, &total_sale, &average_price);
            compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
            break;
            
        default:
            break;
            
    }
    
    
    
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
