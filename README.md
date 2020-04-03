
# SoalShiftSISOP20_modul3_B01
### Soal Shift Modul 2
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)
4. [Soal 4](#4-soal-4)
---
## Soal 3

Pada soal nomo 3 diminta untuk membuat program C yang memindahkan file ke suatu folder berdasarkan ekstensi yang dimiliki. Terdapat 3 mode input yakni -f, -d, dan \*. Dimana pada mode -f user dapat menambahkan argumen yang berupa full path file sebanyak yang user inginkan, pada mode -d user hanya bisa input 1 directory saja, lalu pada mode \* user akan memindahkan seluruh file berdasarkan ekstensinya.

Kesulitan : masih belum bisa membuat 1 folder saja

---
## Soal 4
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
