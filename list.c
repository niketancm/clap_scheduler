#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

void init_ele(struct ele *head)
{
   head->pid = 0;
   head->next = NULL;
}

struct ele *add_ele(int pid, struct ele *head, struct ele *addthis)
{
   struct ele *here;
   here = head;
   while (here->next != NULL) {
      here = here->next;
   }
   /* addthis->pid = pid; */
   here->next = addthis;
      
}
struct ele *search_ele(int pid, struct ele *head)
{
   struct ele *here;
   here = head;
   while (here->next != NULL) {
      here = here->next;
      if(here->pid == pid)
      {
         /* return_this = here; */
         break;
      }
   }
   return here;
}
bool delete_ele(int pid, struct ele *head)
{
   struct ele *here, *prev;
   bool return_result;
   here = head;
   while (here->next != NULL) {
      prev = here;
      here = here->next;
      if(here->pid == pid)
      {
         prev->next = here->next;
         return_result = true;
         /* munmap(addr, pagesize); */
         free(here);
         break;
      }
      else
         return_result = false;
   }
   return return_result;
}
