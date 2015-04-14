#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_PIDS 3

int main()
{
   int i = 1, loop_count = 1;
   int pids[3] = {0,145,231};

   while(1)
   {

      printf("The value of pid is %d and loop count is %d and i is %d \n" ,pids[i], loop_count, i);
      i = i + 1;
      if(i == MAX_PIDS)
         i = 1;
      loop_count = loop_count + 1;
      if(loop_count == 11)
         break;
   }
   return 0;
}
