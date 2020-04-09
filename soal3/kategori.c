#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <limits.h>

// typedef struct arg_struct {
//     char asal[1000];
// }arg_struct;
    
char cwd[1000];

int is_regular_file(const char *path) //jika 0 bukan file
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void pindahFile(char *argv){
//   printf("stringvoid = %s\n", argv);
//   printf("stringvoid = %s\n", cwd);
  
  char string[1000];
  strcpy(string, argv);
  puts(string);
  int isFile = is_regular_file(string);
  char dot = '.'; 
  char slash = '/';
  char* tipe = strrchr(string, dot); 
  char* nama = strrchr(string, slash);
  
  char tipeLow[100];
  if(tipe)
  {
    if((tipe[strlen(tipe)-1] >= 'a' && tipe[strlen(tipe)-1] <= 'z') || (tipe[strlen(tipe)-1] >= 'A' && tipe[strlen(tipe)-1] <= 'Z'))
    {
      strcpy(tipeLow, tipe);
      for(int i = 0; tipeLow[i]; i++){
        tipeLow[i] = tolower(tipeLow[i]);
      }
    }
    else {
      strcpy(tipeLow, tipe);
    }
  }
  else
  {
    if(!isFile){
      printf("ini adalah folder, salah argumen\n");
    //   mkdir(nama, 0777);
      return;
    }
    else
    {
      strcpy(tipeLow, " Unknown"); //tanpa ekstensi
    }
  }
    mkdir((tipeLow + 1), 0777); //bikin folder ekstensi

    size_t len = 0 ;
    // strcpy
    char a[1000] ; //res
    strcpy(a, argv);
    char b[1000] ; //des
    strcpy(b, cwd);
    strcat(b, "/");
    strcat(b, tipeLow+1);
    strcat(b, nama);
    printf("a = %s\n", a);

    printf("b = %s\n", b);

    rename(a, b);
    remove(a);
}

void *pindahf(void* arg){
  char* asal = (char*) arg;
  printf("asal = %s\n", asal);
  // printf("stringthr = %s\n", args.cwd);
  // puts(asal);
  pindahFile(asal);
  pthread_exit(0);
}

void sortHere(char *asal){
  // arg_struct args;
  // args.cwd = "/home/sin/modul3";
  strcpy(cwd,"/home/sin/modul3/soal3/soal3");
  DIR *dirp;
  char files[240][240];
    struct dirent *entry;
    dirp = opendir(asal);
    int index = 0;
    // pthread_t tid[1000]; //max 1000 thread
    // if (d)
    // {
      while ((entry = readdir(dirp)) != NULL)
      {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
          continue;
          
        if(entry->d_type == DT_REG)
        {
          char namafile[105];
          strcpy(namafile, entry->d_name);
          // sprintf(namafile, "%s/%s", asal, entry->d_name);
          sprintf(files[index], "%s/%s", asal, entry->d_name);
          index++;
        }
        else
        {
          printf("%s is a directory\n", entry->d_name);
        }
      }
      closedir(dirp);
    // }

    // chdir(cwd);
    pthread_t threads[index]; 
    for (int i = 0; i < index; i++)
      pthread_create(&threads[i], NULL, pindahf, files[i]);

    for (int i = 0; i < index; i++)
      pthread_join(threads[i], NULL);
}
int main(int argc, char* argv[]) 
{ 

  // char cwd[1000];
  // arg_struct args;
  getcwd(cwd, sizeof(cwd));

  
  if(strcmp(argv[1],"-f")==0)//command -f--------------------------------------------------------------
  {
    pthread_t tid[1000]; //max 1000 thread
    int index = 0;
    for (int i = 2; i < argc; i++)
    {
      // strcpy(args.asal, argv[i]);
      pthread_create(&tid[index], NULL, pindahf, argv[i]);
      sleep(0.5);
      index++;
    }
    for (int i = 0; i < index; i++) {
        pthread_join(tid[i], NULL);
    }
  }
  else if(strcmp(argv[1],"*")==0)
  {
    char asal[] = "/home/sin/modul3/soal3/soal3";
    
    sortHere(asal);
  }
  else if(strcmp(argv[1],"-d")==0){
      char asal[1000];
      strcpy(asal, argv[2]);
      sortHere(asal);
    //   rename(asal, args.cwd);
    //   sortHere(asal);
  }
  else
  {
      printf("salah argumen bos\n");
      return 0;
  }
  
	return 0; 
} 
