#ifndef _LIST_H
#define _LIST_H


struct ele
{
   int pid;
   struct ele *next;
};

void init_ele(struct ele *head);

struct ele *add_ele(int pid, struct ele *head, struct ele * addthis);

struct ele *search_ele(int pid, struct ele *head);

bool delete_ele(int pid, struct ele *head);

#endif
