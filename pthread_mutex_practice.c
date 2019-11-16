#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* add mutex lock to this program for counter */

int counter = 0;

void* child() {
  for(int i = 0;i < 3;++i) {
    counter += 1;
    printf("Counter = %d\n", counter);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, child, NULL);
  pthread_create(&t2, NULL, child, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}