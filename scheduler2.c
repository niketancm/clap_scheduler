#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main ()
{
  pid_t parent_pid, child_pid, child_pid2/* , gchild_pid1, gchild_pid2 */;
  int i = 0;

  //For scheduling
  int process_array[3] = {0,0,0};
  process_array[0] = (int) getpid();

  /* parent_pid = (int) getpid(); //Store the pid of the parent. */
  printf("The parent process id: %d \n", process_array[0]);
  child_pid = fork ();

  //Parent Process
  if (child_pid != 0)
    {
      printf ("Parent, My Child’s process ID is: %d \n", (int) child_pid);

      //Stop the child 1 and put parent1 to sleep
      printf("Hello!!, Just put child %d to sleep \n",child_pid);
      printf("Parent now waking up above thread\n");
      kill(child_pid,SIGCONT);

      printf("Parent now going to sleep!\n");
      kill((int)getpid(),SIGSTOP);
      printf("Parent now waking from sleep\n");
      
      //Parent woken up  by its children and wake up the next process in the queue
      printf("Parent now waking child %d from sleep\n", child_pid);
      kill(child_pid,SIGCONT);
      printf("Parent now waking from sleep\n");

      printf("Parent now exiting");


      /* printf("Hello!!, child executing for the frist time"); */
      /* //fork another child */
      /* child_pid2 = fork(); */
      /* if(child_pid2 != 0) */
      /* 	{ */
      /* 	  //Parent code */
      /* 	  printf ("Parent, My Second Child’s process ID is: %d \n", (int) child_pid2); */
      /* 	} */

      /* //Child2 code. */
      /* else */
      /* 	{ */
      /* 	  process_array[2] = (int) getpid(); */
      /* 	  printf ("This is the Second child process, with id: %d \n",process_array[2]); */

	/* } */
    }

 //This is for the 1st child process
  else
    {
      process_array[1] = (int) getpid();
      printf ("This is the child process, with id: %d \n",process_array[1]);
      printf ("\n This is the child process, with id: %d and the parent process is: %d \n",(int) getpid(), process_array[0]);

      printf("Hello!!, child executing for the first time\n");

      printf("Waking the parent thread \n");
      printf("My PID is %d \n", process_array[1]);
      kill(process_array[0],SIGCONT);
      printf("Process with id %d,Going to sleep \n", (int)getpid());
      kill((int)getpid(),SIGSTOP);

      printf("Child %d, woken up by parent",(int)getpid());


      /* kill(child_pid1,SIGCONT); */

      /* printf("Hello!!, child executing for the frist time \n"); */
      /* printf("Hello!!, child executing for the frist time \n"); */

      /* printf("Hello!!, child executing for the frist time \n"); */
      /* printf("Hello!!, child executing for the frist time \n"); */
      /* printf("Hello!!, child executing for the frist time \n"); */

    }
  return 0;
}
