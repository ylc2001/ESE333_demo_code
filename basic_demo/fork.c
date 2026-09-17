// demo code, fork 3 times

#include <stdio.h>
#include <unistd.h>

int main()
{
  int pid;
  pid = fork();
  printf("fork() returned %d\n", pid);

  if(pid == 0){
    printf("child\n");
  } else {
    printf("parent\n");
  }
  return 0;
}