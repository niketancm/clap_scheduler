#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "list.h"
#define MAX_PIDS 3

volatile pid_t *pids;

int main()
{
   struct ele *ptr, *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;
   bool result;
   ptr = (struct ele *)malloc(sizeof(struct ele));
   init_ele(ptr);

   ptr1 = (struct ele *)malloc(sizeof(struct ele));
   ptr1 = add_ele(1, ptr, ptr1);
   
   ptr2 = (struct ele *)malloc(sizeof(struct ele));
   ptr2 = add_ele(2, ptr, ptr2);
   
   ptr3 = (struct ele *)malloc(sizeof(struct ele));
   ptr3 = add_ele(3, ptr,ptr3);
   
   ptr4 = (struct ele *)malloc(sizeof(struct ele));
   ptr4 = add_ele(4, ptr, ptr4);
   
   ptr5 = (struct ele *)malloc(sizeof(struct ele));
   ptr5 =add_ele(5, ptr, ptr5);

   result = delete_ele(4, ptr);
   if(result)
   {
      printf("Pid deleted \n");
   }

   ptr=ptr->next;
   while (ptr != NULL) {
      printf("%d\n",ptr->pid);
      ptr = ptr->next;
   }

   return 0;
}

