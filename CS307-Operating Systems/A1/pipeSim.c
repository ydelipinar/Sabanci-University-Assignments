#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {

  
  printf("I'm SHELL process, with PID: %d - Main command is: man top | grep -c \n", (int) getpid());
  int file = open("output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  int rc = fork();
  if (rc < 0) { // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } 
  else if (rc == 0) 
  { // child (new process)
    printf("I'm MAN process, with PID: %d - My command is: top \n", (int) getpid());
    int fd[2];
    pipe(fd);
    int rc1 = fork();
    if (rc1 < 0)  // fork failed; exit
    {
    	fprintf(stderr, "fork failed\n");
    	exit(1);
    }
    else if (rc1 == 0)  //grandchild
    {
        close(fd[1]);
        printf("I'm GREP process, with PID: %d - My command is: -c \n", (int) getpid());
        dup2(fd[0], STDIN_FILENO);
        dup2(file, STDOUT_FILENO);
        execlp("grep", "grep", "\\-c", "-w", "-A 4", NULL);
        
    }
    else //firstchild
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
    	execlp("man", "man", "top" , NULL);
    
    }  
   // close(STDOUT_FILENO);
    //open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    
   
  }
  else 
  { // parent goes down this path (main)
    int rc_wait = wait(NULL);
    printf("I'm SHELL process, with PID: %d - execution is completed, you can find the results in output.txt \n", (int) getpid());
    close(file);
  }
  return 0;
}
