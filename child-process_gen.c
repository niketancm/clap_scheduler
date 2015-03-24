#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIDS 4

volatile pid_t *pids;
int main ()
{
  pid_t fork_pid;/* parent_pid, child_pid, child_pid2 *//* , gchild_pid1, gchild_pid2 */;
  /* int i = 0; */


  //For scheduling
  /* int process_array[3] = {0,0,0}; */
  /* process_array[0] = (int) getpid(); */

  //This is to stored the pid
  pids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if(!pids)
    {
      perror("Failed to assign shared memory");
      exit(1);
    }
  //set the shared memory variables to zero
  memset((void *)pids, 0, MAX_PIDS*sizeof(pid_t));

  int i;
  for(i = 1; i < MAX_PIDS; i++)
    {
      pids[0] = (int) getpid();
      printf("Parent, my id is: %d\n", (int) getpid());
      fork_pid = fork();
      /* printf("I am %d,Fork id: %d \n", (int) getpid(),fork_pid); */
      if(fork_pid == 0)
	{
	  //Child process
	  pids[i] = (int) getpid();
	  /* sleep(3); */
	  printf("%d child process, my id is: %d \n", i, pids[i]);
	  /* printf("My Id is: %d \n",pids[1]); */
	  exit(0);
	}
      else if( fork_pid < 0)
	{
	  printf("Fork failed. \n");
	}
      else // Parent Process
	{
	  /* pids[1] = fork_pid; */
	  printf("Parent!! \n");
	  /* printf("parent, fork returned value: %d \n", fork_pid); */
	  /* printf("This is the child process \n"); */
	  /* printf("This is the child process \n"); */
	  /* printf(".....ID is : %d.......\n",pids[1]); */
	  sleep(4);
	  /* for(i = 1; i < MAX_PIDS; i++) */
	  /*   { */
	  printf("I am Parent, my %d child is:%d \n", i, pids[i]);	      
	    /* } */
	}
    }
}
