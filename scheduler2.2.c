#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#inlcude <sys/wait.h>

#define MAX_PIDS 2

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
      fork_pid = fork();
      if(fork_pid == 0)
	{
	  //Child process
	  pids[i] = (int) getpid();
	  /* sleep(3); */
	  printf("%d child process, my id is: %d\n", i, pids[i]);
	  kill((int) getpid(), SIGSTOP);
	  printf("Sleeping \n");
	  exit(0);
	}
      else if( fork_pid < 0)
	{
	  printf("Fork failed. \n");
	}
      else // Parent Process
	{
	  waitpid();
	  printf("Parent!!, my id: %d \n", (int) getpid());
	  sleep(4);
	  printf("I am Parent, my %d child is:%d \n", i, pids[i]);	      
	}
    }
}
