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
   pid_t pid = fork();
   int fd[2];
   // TODO: Create two pipes
   //       Terminate the program if fail to create the pipes

   if (pipe(fd) == -1) {
      fprintf(stderr, "Pipe failed.\n");
      return 1;
   }


   // TODO: Create a child process
   //       Terminate the program if fail to fork a child process

   // TODO: parent process invokes request_rating
   //       child process invokes respond_to_the_rating
   if(pid == 0)
   {
      request_rating(fd[READ_END],fd[WRITE_END]);  
   }else if(pid >0)
   {
      wait(NULL);
      respond_to_the_rating(fd[READ_END],fd[WRITE_END]);
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
   
   
   // TODO: write the student's response to the first pipe

   // TODO: read the message from the second pipe
}

/**********************************************************
 *             respond_to_the_rating                      *
 * Reads the message from the first process and returns   *
 * the new message with the student's response to the     *
 * first process.                                         *
 *********************************************************/
void respond_to_the_rating(int *first_pipe, int *second_pipe) {
   // TODO: read the student's response from the first pipe
   
   // TODO: write the new message to the second pipe
}
