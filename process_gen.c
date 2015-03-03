#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
int main ()
{
  pid_t child_pid1,
        child_pid2
        /* child_pid3 */;
  int i = 0;
  printf ("the main program process ID is %d\n", (int) getpid ());
  child_pid1 = fork ();
  /* child_pid2 = fork (); */
  if (child_pid1 != 0) 
    {
      printf ("CALLED BY MAIN!!! the FIRST child’s process ID is %d\n", (int) child_pid1);

      kill(child_pid1,SIGSTOP);
      child_pid2 = fork ();
      if(child_pid2 != 0)
	{
	  printf ("CALLED BY MAIN!!! the SECOND child’s process ID is %d\n", (int) child_pid2);
	  kill(child_pid2,SIGSTOP);
	  /* sleep(2); */
	  /* kill(child_pid1,SIGCONT); */
	  kill(child_pid2,SIGCONT);
	  kill(child_pid1,SIGCONT);
	  /* kill(child_pid[3],SIGSTOP); */
	  /* kill(child_pid[3],SIGCONT); */
	  /* kill(child_pid[4],SIGSTOP); */
	  /* kill(child_pid[4],SIGCONT); */
	  /* kill(child_pid,SIGCONT); */
	  /* } */
	  /* child_pid3 = fork (); */
	  /* child_pid[3] = fork (); */
	  /* child_pid[4] = fork (); */
	}
      else
	{
	  sleep(10);
	  printf ("CHILD PROCESS\n");
	  printf ("this is the child process, with id %d\n", (int) getpid ());
	  return 0;
	}
    }
  else
    {
     sleep(10);
      printf ("CHILD PROCESS\n");
      printf ("this is the child process, with id %d\n", (int) getpid ());
      return 0;
    }
  return 0;
}
