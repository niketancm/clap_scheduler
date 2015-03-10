#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIDS 3

volatile pid_t *pids;
int main ()
{
  pid_t parent_pid, child_pid, child_pid2/* , gchild_pid1, gchild_pid2 */;
  int i = 0;


  //For scheduling
  int process_array[3] = {0,0,0};
  process_array[0] = (int) getpid();

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

  /* parent_pid = (int) getpid(); //Store the pid of the parent. */
  printf("The parent process id: %d \n", process_array[0]);
  child_pid = fork ();

  //Parent Process
  if (child_pid != 0)
    {
      printf ("Parent, My Child’s process ID is: %d \n", (int) child_pid);

      //Stop the child 1 and put parent1 to sleep
      /* printf("Hello!!, Just put child %d to sleep \n",child_pid); */
      /* printf("Parent now waking up above thread\n"); */

      //CHECK
      /* kill(child_pid,SIGCONT); */
      /* printf("Parent now going to sleep!\n"); */
      /* kill(process_array[0],SIGSTOP); */

      /* printf("Parent now waking from sleep\n"); */
      
      //Parent woken up  by its children and wake up the next process in the queue
      /* printf("Parent now waking child %d from sleep\n",child_pid); */

      //fork another child
      child_pid2 = fork();

      if(child_pid2 != 0)
      	{
      	  //Parent code
      	  printf ("Parent, My Second Child’s process ID is: %d \n", (int) child_pid2);
	  
      	}

      //Child2 code.
      else
      	{
      	  process_array[2] = (int) getpid();
      	  printf ("This is the Second child, with id: %d \n",(int) getpid());
	  /* printf ("This is the Second child, with id: %d \n",process_array[1]); */
	  /* printf ("\n This is the child, with id: %d and the parent process is: %d \n",(int) getpid(), process_array[0]); */
	  /* printf("Waking the parent thread \n"); */
	  /* printf("My PID is %d \n", process_array[1]); */
	  /* printf("Process with id %d,Going to sleep \n", (int)getpid()); */
	  kill((int)getpid(),SIGSTOP);

	  /* printf("Child %d, woken up by parent \n",(int)getpid()); */


	  printf(" \n \n \n Hello!!, child2 executing for the first time\n \n \n");

	  /* kill(process_array[0],SIGCONT); */
	  /* printf("Process with id %d,Going to sleep \n", (int)getpid()); */
	  kill((int)getpid(),SIGSTOP);


	  printf("\nHello!!, child2 executing for the second time \n");
	  printf("Hello!!, child2 executing for the second time \n");
	  /* kill(process_array[0],SIGCONT); */
	  kill((int)getpid(),SIGSTOP);

	  /* printf("\nHello!!, child executing for the third time \n"); */
	  /* printf("Hello!!, child executing for the third time \n"); */
	  /* printf("Hello!!, child executing for the third time \n"); */

	  /* kill(process_array[0],SIGCONT); */
	  /* kill((int)getpid(),SIGSTOP); */

	  printf("This is the end of child 2 process \n");

      	}
      //Child1
      kill(child_pid,SIGCONT);
      /* kill(process_array[0],SIGSTOP); */

      printf("Starting the child2 \n");
      //Child2
      kill(child_pid2,SIGCONT);
      /* kill(process_array[0],SIGSTOP); */

      //Child1
      printf("Starting the child2 TWICE \n");
      kill(child_pid,SIGCONT);
      /* kill(process_array[0],SIGSTOP); */

      //Child2
      /* printf("Starting the child2 \n"); */
      /* printf("child2 id is: %d \n", child_pid2); */
      kill(child_pid2,SIGCONT);
      /* kill(process_array[0],SIGSTOP); */

      //For Child1
      /* kill(child_pid,SIGCONT); */
      /* kill(process_array[0],SIGSTOP); */
      /* printf("Parent now waking from sleep\n"); */

      /* /\* printf("Parent now exiting\n "); *\/ */
      /* kill(child_pid,SIGCONT); */
      /* kill(process_array[0],SIGSTOP); */

      /* kill(child_pid,SIGCONT); */
      /* printf("Parent now exiting\n "); */

      //For Child2
      /* kill(child_pid2,SIGCONT); */
      /* kill(process_array[0],SIGSTOP); */
      /* printf("Parent now waking from sleep\n"); */

      /* /\* printf("Parent now exiting\n "); *\/ */
      /* kill(child_pid,SIGCONT); */
      /* kill(process_array[0],SIGSTOP); */

      kill(child_pid,SIGCONT);
      kill(child_pid2,SIGCONT);
      printf("Parent now exiting\n ");

    }

 //This is for the 1st child process
  else
    {
      process_array[1] = (int) getpid();
      printf ("This is the child process, with id: %d \n",process_array[1]);

      printf ("\n This is the child process, with id: %d and the parent process is: %d \n",(int) getpid(), process_array[0]);

      printf(" \n \n \n Hello!!, child1 executing for the first time\n \n \n");

      /* printf("Waking the parent thread \n"); */
      /* printf("My PID is %d \n", process_array[1]); */
      /* printf("Process with id %d,Going to sleep \n", (int)getpid()); */
      kill((int)getpid(),SIGSTOP);
      /* kill(process_array[0],SIGCONT); */
      /* printf("Child %d, woken up by parent \n",(int)getpid()); */


      printf("\nHello!!, child1 executing for the second time \n");
      printf("Hello!!, child1 executing for the second time \n");
      /* kill(process_array[0],SIGCONT); */
      kill((int)getpid(),SIGSTOP);

      /* printf("\nHello!!, child1 executing for the third time \n"); */
      /* printf("Hello!!, child1 executing for the third time \n"); */
      /* printf("Hello!!, child1 executing for the third time \n"); */

      /* kill(process_array[0],SIGCONT); */
      /* kill((int)getpid(),SIGSTOP); */

      printf("This is the end of child1 process \n");

    }
  return 0;
}
