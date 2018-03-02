//
//  exam_eval.c
//  Assignment3_OrdinaryPipes
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 100
#define READ_END    0
#define WRITE_END   1

// Function prototypes
char isExamHard(void);
void request_rating(int firstPipe[], int secondPipe[]);
void respond_to_the_rating(int firstPipe[], int secondPipe[]);

int main(int argc, const char * argv[]) {
   
   int fd1[2];
   int fd2[2];
   // TODO: Create two pipes
   //       Terminate the program if fail to create the pipes

   if (pipe(fd1) == -1 || pipe(fd2) == -1) {
      fprintf(stderr, "Pipe failed.\n");
      return 1;
   }

   pid_t pid = fork();

   // TODO: Create a child process
   //       Terminate the program if fail to fork a child process

   // TODO: parent process invokes request_rating
   //       child process invokes respond_to_the_rating
   if(pid == 0)
   {
      respond_to_the_rating(fd1,fd2);
   }else if(pid >0)
   {
      request_rating(fd1,fd2);  
      wait(NULL);

      // close (fd1[READ_END]);
      // close (fd1[WRITE_END]);
      // close (fd2[WRITE_END]);
      
      char read_msg[BUFFER_SIZE];
      read(fd2[READ_END], read_msg,  BUFFER_SIZE);
      printf(">>Exam1 is %s\n",read_msg);
      close (fd2[READ_END]);
   }else{
      perror("Could not fork the process");
      exit(-1);
   }
   
   
   return 0;
}

/*********************************************************
 *                        isExamHard                     *
 * This function asks a question about Exam 1 difficulty *
 ********************************************************/
char isExamHard(void)
{
   char input;
   printf("How would you rate the difficulty of Exam 1?\n");
   printf("Enter E for Easy, O for ok, H for Hard: ");
   scanf("%c", &input);
   
   return input;
}

/******************************************************
 *                    request_rating                  *
 * Asks the student to rate the exam #1, sends the    *
 * student's reponse to the second process and reads  *
 * the message from the child process.                *
 *****************************************************/
void request_rating(int *first_pipe, int *second_pipe) {
   char level;
   char write_msg[BUFFER_SIZE];
   char read_msg[BUFFER_SIZE];
   
   level = isExamHard();
   
   printf("answer: %c\n", level);
   if ((level == 'E') || (level == 'e')) {
      strcpy(write_msg, "easy");
   }
   else if ((level == 'O') || (level == 'o')) {
      strcpy(write_msg, "just right");
   }
   else {
       strcpy(write_msg, "hard");
   }
   printf("easy or hard: %s\n", write_msg);
   
   //printf("Parent is requesting...\n");


   close (first_pipe[READ_END]);
   close (second_pipe[WRITE_END]);
   close (second_pipe[READ_END]);
   // TODO: write the student's response to the first pipe
   write(first_pipe[WRITE_END], write_msg, 
               strlen(write_msg)+1);
   printf("Parent Wrote: %s \n", write_msg);
   close (first_pipe[WRITE_END]);

   // read(second_pipe[READ_END], read_msg,  BUFFER_SIZE);
   // printf("Parent read: %s \n", write_msg);

   // // TODO: read the message from the second pipe
}

/**********************************************************
 *             respond_to_the_rating                      *
 * Reads the message from the first process and returns   *
 * the new message with the student's response to the     *
 * first process.                                         *
 *********************************************************/
void respond_to_the_rating(int *first_pipe, int *second_pipe) {
   char write_msg[BUFFER_SIZE];
   char read_msg[BUFFER_SIZE];

   close (second_pipe[READ_END]);
   close (first_pipe[WRITE_END]);

   //printf("Child is responding...\n");
   read(first_pipe[READ_END], read_msg,  BUFFER_SIZE);
   printf("\tChild Read from pipe: %s \n", read_msg);
   close (first_pipe[READ_END]);
   
   write(second_pipe[WRITE_END], "Hello", 
               strlen(read_msg)+1);
   printf("\tChild wrote...: %s \n", read_msg);
   close (second_pipe[WRITE_END]);
   

   // TODO: read the student's response from the first pipe
   
   // TODO: write the new message to the second pipe
}
