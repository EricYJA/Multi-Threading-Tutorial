#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_barrier_t barrier;

void* initor(void* args) {
	printf("---------------thread init work(%d)--------------\n", time(NULL));

	sleep(10);

	pthread_barrier_wait(&barrier);
	printf("--------------thread start work(%d)--------------\n", time(NULL));
	sleep(10);
	printf("--------------thread stop work(%d)--------------\n", time(NULL));
	return NULL;
}
int main(int argc, char* argv[]) {
	pthread_barrier_init(&barrier, NULL, 2);
	printf("**************main thread barrier init done****************\n");
	pthread_t pid;
	pthread_create(&pid, NULL, &initor, NULL);
	printf("**************main waiting(%d)********************\n", time(NULL));
  pthread_barrier_wait(&barrier);
	pthread_barrier_destroy(&barrier);
	printf("***************main start to work(%d)****************\n", time(NULL));
	sleep(30);
	pthread_join(pid, NULL);
	printf("***************thread complete(%d)***************\n", time(NULL));
	return 0;
}