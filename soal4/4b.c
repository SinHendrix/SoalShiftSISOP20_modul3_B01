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
