// This program is an example of how to run a command such as
// ps aux | grep root | grep sbin
// using C and Unix.

#include <stdlib.h>
#include <unistd.h>
#define READ_END 0
#define WRITE_END 1

int main(){
  char firstcmd[100] = "ls", frsarg[100] = "-l", scmd[100] = "wc", secarg[100] = "-l";
  pid_t pid;
  int fd[2];

  pipe(fd);
  pid = fork();

  if(pid==0){
    dup2(fd[WRITE_END], STDOUT_FILENO);
    close(fd[READ_END]);
    close(fd[WRITE_END]);
    execlp(firstcmd, firstcmd, (char*) NULL);
    printf("Failed to execute '%s'\n", firstcmd);
    exit(1);
  }
  else{
    pid=fork();

    if(pid==0)
    {
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[WRITE_END]);
        close(fd[READ_END]);
        execlp(scmd, scmd, secarg,(char*) NULL);
        printf("Failed to execute '%s'\n", scmd);
        exit(1);
    }
    else
    {
        int status;
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        waitpid(pid, &status, 0);
    }
  }
}
