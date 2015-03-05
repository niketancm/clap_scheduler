#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main ()
{
  pid_t parent_pid, child_pid, gchild_pid1, gchild_pid2;
  int i = 0;
  parent_pid = (int) getpid(); //Store the pid of the parent.
  printf("The parent process id: %d \n", parent_pid);
  child_pid = fork ();

  if (child_pid != 0) 
    {
      printf ("Parent, My Child’s process ID is: %d \n", (int) child_pid);

    }
  else //This is for the child process
    {
      printf ("\n CHILD \n");
      child_pid = (int) getpid();
      printf ("This is the child process, with id: %d \n",child_pid);

      gchild_pid1 = fork();

      if(gchild_pid1 != 0) //For grand child process
	{
	  printf("The child of %d process is: %d \n", (int) getpid (), gchild_pid1);
	  printf("This is the child of: %d \n", parent_pid);
	}
      else //Grand Child process code
	{
	  gchild_pid1 = getpid(); //Store the pid of the Grand child 1
	  printf("\n GRAND CHILD 1! \n");
	  printf("I am Grand Child, with id: %d \n", getpid());
	  printf("My parent is: %d \n", child_pid);
	  printf("My Grand Parent is: %d \n", parent_pid);
	}
      /*To be executed by Child process*/
      if((int) getpid() == child_pid)
	{
	  gchild_pid2 = fork();

	  if(gchild_pid2 != 0) //For grand child process
	    {
	      printf("The child of %d process is: %d \n", (int) getpid (), gchild_pid2);
	      printf("This is the child of: %d \n", parent_pid);
	    }
	  else //Grand Child process code
	    {
	      gchild_pid2 = getpid(); //Store the pid of the Grand child 2
	      printf("\n GRAND CHILD 2! \n");
	      printf("I am Grand Child, with id: %d \n", getpid());
	      printf("My parent is: %d \n", child_pid);
	      printf("My Grand Parent is: %d \n", parent_pid);
	    }
	}
    }
  return 0;
}
