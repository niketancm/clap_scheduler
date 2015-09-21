#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_PIDS 3

int main()
{
  pid_t fork_pid;
for (i = 1; i < MAX_PIDS; i++) 
  {
    fork_pid = fork();
  
  }
 
  //to schedule the threads!!
  return 0;
}
