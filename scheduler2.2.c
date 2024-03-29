#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
//------------waitpid branch----------------
#define MAX_PIDS 2
/* //remember to use pthread mutex for pid_set!! */
/* int pid_set;  */

volatile pid_t *pids;
int main ()
{
   pid_t fork_pid, wait_pid;/* parent_pid, child_pid, child_pid2 *//* , gchild_pid1, gchild_pid2 */;
   /* int i = 0; */
   /* int status[MAX_PIDS]; */

   //For scheduling
   /* int process_array[3] = {0,0,0}; */
   /* process_array[0] = (int) getpid(); */

   //This is to stored the pid and the count for number of pids set in the pids array
   pids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   if(!pids)
   {
      perror("Failed to assign shared memory");
      exit(1);
   }
   //set the shared memory variables to zero
   memset((void *)pids, 0, MAX_PIDS*sizeof(pid_t));

  pids[0] = (int) getpid();
  int i;
  for(i = 1; i < MAX_PIDS; i++)
    {
      /* pids[0] = (int) getpid(); */
      fork_pid = fork();
      if(fork_pid == 0)
	{
	  //Child process
	  pids[i] = (int) getpid();
	  /* sleep(3); */
	  printf("%d child process, my id is: %d, going to sleep\n", i, pids[i]);
	  /* kill((int) getpid(), SIGSTOP); */
	  /* printf("woken up from sleeping for First Time by parent \n"); */
          
	  printf("Thread %d Finished work! \n", i);

	  exit(2);
	}
      else if( fork_pid < 0)
      {
         printf("Fork failed. \n");
      }
      
      else // Parent Process
	{
	  int status; 
	  /* printf("The child id is: %d \n", fork_pid); */
	  sleep(4); // wait till the child processes update their pids.

	  printf("Parent!!, my id: %d \n", (int) getpid());
	  /* sleep(4); */
	  printf("I am Parent, my %d child is:%d \n", i, pids[i]);	      
	}
    }
  
   //This is to make sure the parent thread executes this below code.
  if((int) getpid() == pids[0])
   {
      //Schedule the threads.
      printf("In the scheduling part \n", pids[0]);
      int exited_childs = 0;
      int count = 1, status1,pids_count = 1, i=1;
      /* while(1) */
      /* printf("Entering for \n"); */
      /* for(i = 1; i < 20; i++) */
      {
         /* printf("-----while------\n"); */
         fork_pid = pids[pids_count];
         wait_pid = waitpid(fork_pid, &status1, WUNTRACED | WNOHANG);
         
         printf("*************WIFEXITED is %d************\n",WIFEXITED(status1));
         printf("*************WIFSTOPPED is %d************\n",WIFSTOPPED(status1));
         printf("*************WEXITSTATUS is %d************\n",WEXITSTATUS(status1));
         printf("*************WIFSIGNALED is %d************\n",WIFSIGNALED(status1));
         printf("*************************************\n");
         
         printf("*************wait_pid is %d************\n",wait_pid);
         //signal the process to continue
         if(WIFSTOPPED(status1))
         {
            printf("Parent is awakeing the thread %d\n ", pids[pids_count]);
            kill(pids[pids_count], SIGCONT);
            /* pids_count += 1; */
         }

         //keep the count of childs that are finished.
         else if(status1 == 0)
         {
            exited_childs += 1;
            printf("The exited childs are %d\n" ,exited_childs);
            printf("------CHILD DEAD %d------\n" ,pids[pids_count]);
         }
            
         //signal the process to continue
         /* else */
         /* { */
         /*    kill(pids[pids_count], SIGCONT); */
         /* } */

         //check if all the childs are finished.
         /* if( exited_childs == (MAX_PIDS-1))  */
         /* { */
         /*    break; */
         /* } */
         
         pids_count += 1; // Increment the pid counter.
         //reset the pid counter
         if(pids_count == MAX_PIDS)
         {
            pids_count = 1;
         }
         /* break; */
      }
      printf("Finished scheduling \n");
   }

  /* return 0; */
  exit(0);
}
