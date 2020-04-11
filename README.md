
# SoalShiftSISOP20_modul3_B01
### Soal Shift Modul 3
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)
4. [Soal 4](#4-soal-4)
---

## 1. Soal 1
Belum sempat mengerjakan karena kekurangan waktu
## 2. Soal 2
Belum sempat mengerjakan karena kekurangan waktu
## 3. Soal 3

Pada soal nomo 3 diminta untuk membuat program C yang memindahkan file ke suatu folder berdasarkan ekstensi yang dimiliki. Terdapat 3 mode input yakni -f, -d, dan \*. Dimana pada mode -f user dapat menambahkan argumen yang berupa full path file sebanyak yang user inginkan, pada mode -d user hanya bisa input 1 directory saja, lalu pada mode \* user akan memindahkan seluruh file berdasarkan ekstensinya.

```c
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

    
char cwd[1000];

int is_regular_file(const char *path) //fungsi untuk cek apakah file atau bukan
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void pindahFile(char *argv){// fungsi untuk memindahkan sebuah file
  
  char string[1000];
  strcpy(string, argv);
  puts(string);
  int isFile = is_regular_file(string);
  char dot = '.'; 
  char slash = '/';
  char* tipe = strrchr(string, dot); //tipe berisi ekstensi include dengan .
  char* nama = strrchr(string, slash); // nama berisi nama file beserta ekstensi dan /
  
  char tipeLow[100];
  if(tipe)
  {
    if((tipe[strlen(tipe)-1] >= 'a' && tipe[strlen(tipe)-1] <= 'z') || (tipe[strlen(tipe)-1] >= 'A' && tipe[strlen(tipe)-1] <= 'Z')) // cek apakah terdapat huruf besar atau kecil
    {
      strcpy(tipeLow, tipe);
      for(int i = 0; tipeLow[i]; i++){
        tipeLow[i] = tolower(tipeLow[i]);// mengubah semua huruf menjadi lowercase
      }
    }
    else {
      strcpy(tipeLow, tipe);// copy string tipe ke string tipelow
    }
  }
  else
  {
    if(!isFile){// cek apakah file atau bukan
      printf("ini adalah folder, salah argumen\n");// print bila bukan file
      return;
    }
    else
    {
      strcpy(tipeLow, " Unknown"); //apabila tidak memiliki ekstensi, maka tipelow menjadi unknown
    }
  }
    mkdir((tipeLow + 1), 0777); //membuat folder ekstensi

    size_t len = 0 ;
    char a[1000] ; //string a adalah full path file awal
    strcpy(a, argv);
    char b[1000] ; //string b adalah full path file ke directory tujuan
    strcpy(b, cwd);
    strcat(b, "/");
    strcat(b, tipeLow+1);// mengambil ekstensinya saja, karena tipelow masih mengandung . maka dari itu +1 agar didapatkan ekstensi saja
    strcat(b, nama);
    printf("a = %s\n", a);

    printf("b = %s\n", b);

    rename(a, b);
    remove(a);
}

void *pindahf(void* arg){// fungsi untuk memanggil fungsi pindahFile
  char* asal = (char*) arg;
  printf("asal = %s\n", asal);
  pindahFile(asal);
  pthread_exit(0);
}

void sortHere(char *asal){
  DIR *dirp;
  char files[240][240];
    struct dirent *entry;
    dirp = opendir(asal);
    int index = 0;

      while ((entry = readdir(dirp)) != NULL)
      {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
          continue;
          
        if(entry->d_type == DT_REG)// cek apakah merupakan file atau bukan
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

    pthread_t threads[index]; 
    for (int i = 0; i < index; i++)
      pthread_create(&threads[i], NULL, pindahf, files[i]);// membuat thread untuk memindahkan file

    for (int i = 0; i < index; i++)
      pthread_join(threads[i], NULL);
}
int main(int argc, char* argv[]) 
{ 
  getcwd(cwd, sizeof(cwd));
  char asal[120];
  strcpy(asal, cwd);

  
  if(strcmp(argv[1],"-f")==0)//command -f--------------------------------------------------------------
  {
    pthread_t tid[1000]; //max 1000 thread
    int index = 0;
    for (int i = 2; i < argc; i++)// loop sebanyak argumen yang dimasukkan
    {
      pthread_create(&tid[index], NULL, pindahf, argv[i]);// membuat thread untuk memindahkan file
      sleep(0.8);
      index++;
    }
    for (int i = 0; i < index; i++) {
        pthread_join(tid[i], NULL);
    }
  }
  else if(strcmp(argv[1],"*")==0)
  {    
    sortHere(asal);
  }
  else if(strcmp(argv[1],"-d")==0){
      char asal[1000];
      strcpy(asal, argv[2]);
      sortHere(asal);
  }
  else
  {
      printf("salah argumen bos\n");// handle apabila argumen selain yang diharapkan
      return 0;
  }
  
	return 0; 
} 


```

---
## 4. Soal 4
Pada soal 4a diminta untuk membuat program C yang menampilkan hasil perkalian matriks 4x2 dan 2x5. isi matrix adalah angka dengan range 1-20 (tidak perlu dibuat filter angka). Lalu hasil perkalian matriksnya akan digunakan pada soal 4b.
```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void *worker(void* args){
  int *data = (int *)args;
  int *result = (int *)malloc(sizeof(int));
  int value = 0, arrLen = data[0], i;

  for (i = 0; i < arrLen; i++){
  	value += data[i+1]*data[arrLen + i + 1];
  }

  *result = value;
  pthread_exit(result);
}

int main(){
  int rowMatrixA = 4;
  int colMatrixA = 2;
  int rowMatrixB = 2;
  int colMatrixB = 5;

  int matrixA[rowMatrixA][colMatrixA];
  int matrixB[rowMatrixB][colMatrixB];

  int i,j;

  for (i = 0; i < rowMatrixA; i++){
    for (j = 0; j < colMatrixA; j++){
      matrixA[i][j] = rand() % 2 + 1;
	}
  }

  for (i = 0; i < rowMatrixB; i++){
    for (j = 0; j < colMatrixB; j++){
     matrixB[i][j] = rand() % 2 + 1;
	}
  }

  printf("First Matrix:\n");
  for (i = 0; i < rowMatrixA; i++){
    for(j = 0; j < colMatrixA; j++){
     printf("%d ", matrixA[i][j]);
    }
    printf("\n");
  }

  printf("\nSecond Matrix:\n");
  for (i = 0; i < rowMatrixB; i++){
    for(j = 0; j < colMatrixB; j++){
      printf("%d ", matrixB[i][j]);
    }
    printf("\n");
  }

  int resultCount = rowMatrixA*colMatrixB;
  pthread_t *threads;
  threads = (pthread_t*)malloc(sizeof(pthread_t)*resultCount);

  int counter = 0, k;

  for (i = 0; i < rowMatrixA; i++){
    for (j = 0; j < colMatrixB; j++) {
      int* args = (int *)malloc((10)*sizeof(int));
      args[0] = colMatrixA;

      for (k = 0; k < colMatrixA; k++){
      	args[k+1] = matrixA[i][k];
	  }

      for (k = 0; k < rowMatrixB; k++){
      	args[colMatrixA+k+1] = matrixB[k][j];
	  }

      pthread_create(&threads[counter++], NULL,
        worker, (void*)(args));
    }
  }


  int *sharedMatrix;
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  sharedMatrix = (int *)shmat(shmid, NULL, 0);

  sharedMatrix[0] = resultCount;
  sharedMatrix[1] = colMatrixB;
  printf("\nResult:\n");
  for (i = 0; i < resultCount; i++){
    void *k;
    pthread_join(threads[i], &k);
    int *value = (int *)k;
    printf("%d\t",*value);
    sharedMatrix[i+2] = *value;
    if ((i + 1) % colMatrixB == 0){
    	printf("\n");
	}
  }
  return 0;
}

```

Pada soal 4b, porgram diminta untuk menghitung baris bilangan yang dimulai dari 1 dengan batas atasnya yaitu setiap elemen pada matriks hasil perkalian pada soal 4a.
```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int factorial(int number){
    if(number == 1)return 1;
    else return number + factorial(number-1);
}

void *worker(void *args){
  int *data = (int *)args;
  int *result = (int *)malloc(sizeof(int));
  int value = factorial(data[0]);
  *result = value;
  pthread_exit(result);
}

int main(){
  int* sharedMatrix;
  key_t key = 1234;
  int counter = 0;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  sharedMatrix = (int *)shmat(shmid, NULL, 0);

  pthread_t *threads;
  threads = (pthread_t*)malloc(sizeof(pthread_t)*sharedMatrix[0]);

  for(int i = 2; i<sharedMatrix[0] + 2; i++){
    int* args = (int *)malloc(sizeof(int));
    args[0] = sharedMatrix[i];
    pthread_create(&threads[counter++], NULL, worker, (void*)(args));
  }
  for(int i = 0; i<counter;i++){
    void *k;
    pthread_join(threads[i], &k);
    int *value = (int *)k;
    printf("%d\t",*value);
    if((i+1) % sharedMatrix[1] == 0)printf("\n");
  }

  printf("\n");
return 0;
}

```
Pada soal 4c program diminta untuk menunjukkan jumlah file dan folder pada directory saat ini.
```c
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

```
