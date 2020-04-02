#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main (int argc, char **argv){// .3/ == 1    ./3 -f argv[1] == -f
  char* point;
  int status;


  if (argc > 2){
    // printf("%s\n", argv[1]);
    if (strcmp(argv[1], "-f") == 0){
      for (int i = 2; i < argc; i++){
        char ext[100] = {0};
        if((point = strrchr(argv[i],'.')) != NULL ) {
          // printf("%s\n", point+1);
          strcpy(ext, point+1);
          char dir[1000], filename[1000];
          sprintf(filename, "%s", argv[i]);
          sprintf(dir, "/home/sin/modul3/%s", ext);
          // printf("filename : %s\ndir : %s\n",filename, dir);
          // printf("%s\n", ext);
          // if(strcmp(point,".csv") == 0) {
          //
          // }
          if ((fork()) == 0){
            // output to pipe1
            // dup2(pipe1[1], 1);
            // // close fds
            // close(pipe1[0]);
            // close(pipe1[1]);
            // exec
            char *argv1[] = {"mkdir", ext, NULL};
        		execv("/bin/mkdir", argv1);
          }
          else{
            sprintf(dir, "%s/", dir);
            while ((wait(&status)) > 0);
            // input from pipe1
            // dup2(pipe1[0], 0);
            // // output to pipe2
            // // dup2(pipe2[1], 1);
            // // close fds
            // close(pipe1[0]);
            // close(pipe1[1]);
            // exec
            char *argv1[] = {"mv", filename, dir, NULL};
        		execv("/bin/mv", argv1);
          }
        }
      }
    }
  }
  else {
    printf("invalid input\n");
  }
}
// .txt
// TXT
// .jpg
// JPG
// JPEG
// ZIP
// PNG
// png
// zip
// gz
// bin
// hex
// js
// JS
// c
// GIF
// sh
// pdf
