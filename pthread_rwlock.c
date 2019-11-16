#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
 
#define MAXDATA     1024
#define MAXREDER    100
#define MAXWRITER   100

struct
{
    pthread_rwlock_t   rwlock;
    char datas[MAXDATA];   
} shared = {
    PTHREAD_RWLOCK_INITIALIZER
};
 
void *reader(void *arg);
void *writer(void *arg);
 
int main(int argc,char *argv[]) {
  int i,readercount,writercount;
  pthread_t tid_reader[MAXREDER],tid_writer[MAXWRITER];
  if(argc != 3) {  
    printf("usage : <reader_writer> #<readercount> #<writercount>\n");
    exit(0);
  }

  readercount = atoi(argv[1]); 
  writercount = atoi(argv[2]);
  pthread_setconcurrency(readercount+writercount);

  for(i=0;i<writercount;++i) {
    pthread_create(&tid_writer[i],NULL,writer,NULL);
  }
      
  sleep(1);
  for(i=0;i<readercount;++i) {
    pthread_create(&tid_reader[i],NULL,reader,NULL);
  }

  for(i=0;i<writercount;++i) {
    pthread_join(tid_writer[i],NULL);
  }

  for(i=0;i<readercount;++i) {
    pthread_join(tid_reader[i],NULL);
  }

  exit(0);
}

void *reader(void *arg){
  pthread_rwlock_rdlock(&shared.rwlock);
  printf("Reader begins read message.\n");
  sleep(1);
  printf("Read message is: %s\n",shared.datas);
  pthread_rwlock_unlock(&shared.rwlock);
  return NULL;
}
 
void *writer(void *arg) {
  char datas[MAXDATA];
  pthread_rwlock_wrlock(&shared.rwlock);
  printf("Writers begings write message.\n");
  printf("Enter the write message: \n");
  gets(datas);
  strcat(shared.datas,datas);
  pthread_rwlock_unlock(&shared.rwlock);
  return NULL;
}