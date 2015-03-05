#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
int main ()
{
  pid_t parent_pid,child_pid,gchild_pid1/* ,gchild_pid2 */;
  int i = 0;
  parent_pid = (int) getpid();
  printf ("the main program process ID is %d\n", (int) getpid ());
  child_pid = fork ();
  /* child_pid2 = fork (); */
  if (child_pid != 0) 
    {
      printf ("MAIN!!! Child’s process ID is %d\n", (int) child_pid);
      /* kill(child_pid,SIGSTOP); */
    }
  else //This is for the child process
    {
      printf ("CHILD \n");
      child_pid = (int) getpid();
      printf ("This is the child process, with id %d\n",child_pid);

      gchild_pid1 = fork();

      if(gchild_pid1 != 0) // grand child process
	{
	  printf("The child of %d process is %d:: \n", (int) getpid (), gchild_pid1);
	  printf("This is the child of %d.\n", parent_pid);
	}
      else // Grand Child process
	{
	  printf("GRAND CHILD 1!\n");
	  printf("I am Grand Child, with id: %d \n", getpid());
	  printf("My parent is: %d \n.", child_pid);
	  printf("My Grand Parent is: %d\n", parent_pid);
	}
    }
  return 0;
}
