#ifndef __LIB_USER_STACK_H
#define __LIB_USER_STACK_H

void push_int (void ** esp, int value);
int pop_int (void ** esp);

void push_char (void ** esp, char c);
char pop_char (void ** esp);

void push_word_align (void ** esp);

void push_void_pointer (void ** esp, void *pointer);
char * pop_void_pointer (void ** esp);

void push_char_pointer_pointer (void ** esp, char ** pointer);
void push_ret_address (void ** esp, void (*) ());
#endif