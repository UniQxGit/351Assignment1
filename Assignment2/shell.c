//
// Assignment 2 Modified Project 1 from
// Operating System Concepts - Ninth Edition
// John Lee 893003137
// Chloe Ho 890712797
// Long Nguyen 893548198

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE  80 /* no more than 80 chars per line */

// forward declaration
long read_command(char commandBuffer[]);
void parse_command(char commandBuffer[], char *args[], long length);
void clean_input(char commandBuffer[], long length);

int main() {
    char commandBuffer[MAX_LINE]; // command buffer
    // Max of 40 arguments for 80 char command line
    char *args[MAX_LINE/2 + 1];
    long length;
    pid_t child;  // child process id
    int status;   // status from execvp system call
    
    int notExit = 1; // flag indicating to exit
    
    /* Keep running until the user has typed "exit" or "quit" */
    do {
        
        length = read_command(commandBuffer);
        
        if (length == 0) {
            exit(0); // ^d was entered, exit
        }
        
        /**
         * the <control><d> signal interrupted the read system call
         * if the process is in the read() system call, read returns -1
         * However, if this occurs, errno is set to EINTR. Check this value
         * and disregard the -1 value
         */
        if ( (length < 0) && (errno != EINTR) ) {
            perror("error reading the command\n");
            exit(-1); /* terminate with error code of -1 */
        }
        
        parse_command(commandBuffer, args, length);
        if ( (strncmp(commandBuffer, "exit", 4) == 0) ||
            (strncmp(commandBuffer, "quit", 4) == 0) ){
            notExit = 0;
        }
        
        if (notExit) {
            child = fork();
            switch (child){
                case -1:
                    perror("Could not fork the process");
                    break;
                case 0: //child process
                    printf("Child running(%d): command = %s. args = %s.\n",child,commandBuffer,*args);
                    status = execlp(commandBuffer,commandBuffer,*args,NULL);
                    if(status != 0)
                    {
                        perror ("error");
                        exit(-2);
                    }
                    break;
                default:
                    wait(NULL);
                    printf("Child Done. PARENT(%d): value = %s\n",child,commandBuffer);
                    break;
            //    default: //parent process
            }
        
            // TODO: Create a child process
            
            /* TODO: Error check to make sure the child was successfully created */
            
            /*** TODO: If I am child, I will do this: ****/
            /* Call execlp() to replace my program with that specified at the command
             * line.
             *
             * Also, please do not forget to error check your exelp() system call.
             */
            
            /*** TODO: If I am a parent, I will do the following ***?
             /* Wait for the child process to terminate */
            
        } // if notExit
        printf("\n");
    } while (notExit);
    
    return 0;
}

// TODO: implement read_command to read in user's input
long read_command(char commandBuffer[]) {
    long len = 0; // # of characters in the command line
    int start;
    do{
        printf("cmd> ");
        fflush(stdout);
        len = read(STDIN_FILENO, commandBuffer, MAX_LINE);
    }
    while (commandBuffer[0] == '\n');
    
    start = -1;
    if(len == 0)
        exit(0);
    
    if((len < 0) && (errno != EINTR)){
        perror("error");
        exit(-1);
    }
  
    return len;
}


//Cleans the input so that spaces can be put in before and after, in order to circumvent the "invalid path" error.
void clean_input(char commandBuffer[], long length)
{
    long leftIndex = 0;
    long rightIndex = length-2;

    int canLeft = 1;
    int canRight = 1;
    
    char cmp = ' ';
    
    for(int i = 0; i < length-1; i++)
    {
        if(commandBuffer[leftIndex] == ' ')
        {
            leftIndex++;
        }

        if(commandBuffer[rightIndex] == ' ')
        {
            rightIndex--;   
        }
    }

    int cIndex;
    for(int i = leftIndex; i <= rightIndex; i++)
    {
        commandBuffer[cIndex] = commandBuffer[i];
        cIndex++;
    }

    commandBuffer[cIndex] = NULL;
}

// TODO: Complete this function to set up the arguments, args, to pass
//       to the execvp system call
void parse_command(char commandBuffer[], char *args[], long length) {
    /* index where beginning of next command parameter is */
    int start = -1;
    /* index of where to place the next parameter into args[] */
    int ct = 0;
    
    int ix;


    clean_input(commandBuffer,length);

    for (ix = 0; ix < length; ix++) { // parse command buffer
        /* examine every character in the commandBuffer */
        switch (commandBuffer[ix]) {
            case ' ': case '\t':
                // TODO: Setup the pointer for the arguments
                // insert your code here
                if(start == -1)
                {
                    start = ix;
                    commandBuffer[ix] = '\0';    
                }else if(start = ix-1){
                    start = ix;
                }
                
                break;
                
            case '\n':
                // TODO: Setup the pointer for the arguments
                // insert your code here

                commandBuffer[ix] = '\0';
                args[ct] = NULL;
                break;
                
            default :     // some other character
                // TODO: Set up the 'start' index
                // insert your code here
                
                if(start > 0)
                {
                    args[ct] = &commandBuffer[ix];
                    ct++;
                }
                // Stop the process if the user enters a background task
                if (commandBuffer[ix] == '&') {
                    perror("Background task is not supported\n");
                    exit(-1); // terminate with error code of -1
                }
        }
    }
    
    args[ct] = NULL; // just in case the command was > 80 characters
}
