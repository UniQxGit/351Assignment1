
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
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest);
void compute_discounts(float price[], float discount[]);
void display_discounts(void);

int main()
{
    
    float prices[SIZE] = {1000, 1500, 720, 850, 970};
    float discounts[SIZE] = {5, 10, 15, 20, 25};
    
    /* TODO: Error check to make sure the child was successfully created */
    
    /*** TODO: If I am child, I will do this: ****/
    /* Compute the total sale, the average, lowest and highest prices
     * for the five items for each discount rate
     */
    
    /*** TODO: If I am a parent, I will do the following ***/
    /* Wait for my child process to compute and share the computed data, then
     * display the data
     */
    
    
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
    const char *name = "OS";
    
    int shm_fd;
    void *ptr;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        printf("shared memory failed\n");
        exit(-1);
    }
    
    /* configure the size of the shared memory segment */
    ftruncate(shm_fd,4096);
    
    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0,4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        // return -1;
    }
    
    /**
     * TODO:
     * Calculate the total sale, the average, lowest and highest prices for each
     * item for each discount: 5%, 10%, 15%, 20%, 25%
     */
    
    float totalsale;
    float average;
    float highest_price;
    float lowest_price;
    float tmpPrice[SIZE] = {};
    
    printf("%s\t%s\t%s\t%s\t%s\n","DISCOUNT","TOTAL","AVERAGE","LOWEST","HIGHEST");
    printf("%s\n","--------\t-----\t-------\t------\t-------");
    for(int i = 0; i < SIZE; i++){
        totalsale = 0.0;
        average = 0.0;
        for(int j = 0; j < SIZE; j++)
        {
            //printf("tmpPriceA:%f\n",tmpPrice[i]);
            tmpPrice[j] = price[j] * (1.0 - (discount[i] / 100.0));
            totalsale += tmpPrice[j];    
            //printf("tmpPriceB:%f\n",tmpPrice[i]);
        }
        average = totalsale / SIZE;

        compute_lowest_highest(SIZE, tmpPrice, &highest_price, &lowest_price);

        
        sprintf(ptr,"%4.f%%",discount[i],"");
        printf("\nLength %d:%s\n",strlen((char *)ptr),(char *)ptr);
        ptr += strlen((char *)ptr)+1;

        sprintf(ptr,"$%.2f",totalsale);
        printf("Length %d:%s\n",strlen((char *)ptr),(char *)ptr);
        ptr += strlen((char *)ptr)+1;
        
        sprintf(ptr,"$%.2f",average);
        printf("Length %d:%s\n",strlen((char *)ptr),(char *)ptr);
        ptr += strlen((char *)ptr)+1;
        
        sprintf(ptr,"$%.2f",lowest_price);
        printf("Length %d:%s\n",strlen((char *)ptr),(char *)ptr);
        ptr += strlen((char *)ptr)+1;

        sprintf(ptr,"$%.2f\n",highest_price);
        printf("Length %d:%s\n",strlen((char *)ptr),(char *)ptr);
        ptr += strlen((char *)ptr)+1;
        

        //Temporary. Move this into display_discounts
        printf("%4.2f\t",discount[i]);
        printf("%4.2f\t",totalsale);
        printf("%4.2f\t",average);
        printf("%4.2f\t",lowest_price);
        printf("%4.2f\n",highest_price);
        
    }
    
    
    
    //    printf("Total sale with 10 percent off =  %4.2f\n", totalsale);
    //    printf("Average sale with 10 percent off =  %4.2f\n", average);
    
    
    //    printf("lowest = %4.2f\n" , lowest_price);
    //    printf("highest = %4.2f\n" , highest_price);
    
    
    /**
     * TODO: write the percentage discount, total sale, average price, lowest and
     * highest prices to the shared memory region.
     *
     * Note: must increment the value of ptr after each write.
     */
    
    //sprintf(ptr,"%s",name1);
    //ptr += strlen(name1);
    // sprintf(ptr,"\t%s",name2);
    // ptr += strlen(name2);
    // sprintf(ptr,"\t\t%s",name3);
    // ptr += strlen(name3);
    // sprintf(ptr,"\t\t%s",name4);
    // ptr += strlen(name4);
    // sprintf(ptr,"\t%s\n",name5);
    // ptr += strlen(name5);
    
    
}

/*******************************************************************
 * Output and display the computed total sale and the average,     *
 * lowest and highest prices for each item.                        *
 * Open the read-only shared-memory object and read data from the  *
 * shared memory region, then remove the shared memory segment.    *
 ******************************************************************/
void display_discounts(void) {
    
    const char *name = "OS";
    
    int shm_fd;
    void *ptr;
    int i;
    
    /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }
    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0,4096, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }
   
    
    /* now read from the shared memory region */
    printf("\n\n");
    printf("%-8s %-8s %-8s %-8s %-8s\n","DISCOUNT","TOTAL","AVERAGE","LOWEST","HIGHEST");
    printf("%-8s %-8s %-8s %-8s %-8s\n","--------","-----","-------","------","-------");

    char *text;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            text = (char*)ptr;
            printf("%-9s",text);
            //printf("\n%d:%s\n",strlen((char*)ptr),(char*)ptr);
            ptr += strlen(text)+1;
        }
    }
    
    /* remove the shared memory segment */
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n",name);
        exit(-1);
    }
    
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
