#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int sec = 0, sec_old = 0, trigger = 10; // 10 ms
  clock_t before = clock();

  do {
    clock_t difference = clock() - before;
    sec = difference / CLOCKS_PER_SEC;
    if (sec != sec_old) {
      printf("%d \n", sec);
      sec_old = sec;
    }
  } while (sec < trigger);
  printf("Time taken %d seconds %d milliseconds", sec, sec * 1000);
}
