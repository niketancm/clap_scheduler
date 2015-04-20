#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_PIDS 3

volatile pid_t *pid_array;

int main()
{
   pid_array = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   if(!pid_array)
   {
      perror("Failed to assign shared memory");
      exit(1);
   }
   //set the shared memory variables to zero
   memset((void *)pid_array, 0, MAX_PIDS*sizeof(pid_t));

   pid_t fork_pid;
   int /* pid_array[MAX_PIDS] = {0, 0, 0} ,*/ i;

   pid_array[0] = (int) getpid();
   for (i = 1; i < MAX_PIDS; i++)
   {
      fork_pid = fork();
      if(fork_pid == 0) //child process
      {
         pid_array[i] = (int) getpid();
         printf("-----CHILD%d => %d---- \n", i, pid_array[i]);
         printf("CHILD%d => %d has finished work \n",i , pid_array[i]);
         exit(0);
      }
      
      else if(fork_pid < 0) 
      {
         printf("fork faild \n");
      }
      
      else //parent process
      {
         sleep(10);
         printf(" I am PARENT => %d \n", (int)getpid());
      }
   }
   if((int) getpid() == pid_array[0])
   {
      printf("I am %d \n", (int)getpid());
      printf("My children are as shown below :: \n");
      for (i = 1; i < MAX_PIDS; i++)
      {

         printf("CHILD %d ID:: %d\n", i, pid_array[i]);   
      }

    
   }
   printf("Parent finished\n");
   exit(0);     /* return 0; */
}
