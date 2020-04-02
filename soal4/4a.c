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
