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
volatile pid_t *pids;

int main()
{

  //------------- Shared Memory ----------------- //
  pids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
	      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if(!pids)
    {
      perror("Failed to assign shared memory");
      exit(1);
    }
  //set the shared memory variables to zero
  memset((void *)pids, 0, MAX_PIDS*sizeof(pid_t));
  
  //------------- Shared Memory ----------------- //

  pids[0] = (int) getpid();  //store the parent process id.
  int i;
  pid_t fork_pid;
  
  //Parent creating child processes
  for (i = 1; i < MAX_PIDS; i++) 
    {
      fork_pid = fork();
 
      if(fork_pid == 0) //child process code!!
	{
	  pids[i] = (int) getpid();
	  printf("Child process, my id is: %d \n", pids[i]);
	  printf("Child %d going to sleep \n",pids[i]);
	  kill((int) getpid(), SIGSTOP);
	  printf("Parent woke me up \n");
	  exit(0);
	}

      else if( fork_pid < 0)
	{
	  printf("Fork failed!!\n");
	}

      else //parent process code
	{
	  int status;
	  printf("In the parent process, my id is %d \n", (int)getpid());
	  //wait till the child processes update their pids
	  waitpid(pids[i], &status, WUNTRACED);
	  printf("*************status is %d************\n",status);
	  if(WIFSTOPPED(status))
	    {
	      printf("Parent has detected the process %d has stopped \n", pids[i]);
	      /* printf("Awakening the process \n"); */
	      /* kill(pids[i], SIGCONT); */
	    }
	  else if(WIFEXITED(status))
	    {
	      printf("Child finished execution!! \n");
	    }
	  
	}      
    }
 
  //to schedule the threads!!
  if((int) getpid() == pids[0])  
    {
      int status;
      bool schedule = true;
      //yet to be implemented!!
      printf("\n Scheduling the threads!! \n");
      /* for (i = 1; i < MAX_PIDS; i++) */
      /* 	{ */
      /* 	  printf("Awakening the process:%d \n", pids[i]); */
      /* 	  kill(pids[i], SIGCONT); */
      
      /* 	  waitpid(pids[i], &status, WUNTRACED); */
      /* 	  printf("*************status is %d************\n",status); */
      /* 	  if(WIFEXITED(status)) */
      /* 	    { */
      /* 	      printf("Child %d finished execution!! \n",pids[i]); */
      /* 	    } */
      /* 	} */
      while(schedule)
	{
	  schedule_a_thread();
	  if(exited_p == MAX_PIDS)
	    {
	      printf("All the threads have been scheduled!! \n");
	    }
	}
    }

  return 0;
}
