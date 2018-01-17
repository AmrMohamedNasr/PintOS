#ifndef __LIB_USER_STACK_H
#define __LIB_USER_STACK_H

#include <stdint.h>

void push_int32_t (void ** esp, int32_t value);
int32_t pop_int32_t (void ** esp);

void push_char (void ** esp, char c);
char pop_char (void ** esp);

void push_str (void ** esp, const char *s);

void push_word_align (void ** esp);

void push_void_pointer (void ** esp, void *pointer);
void * pop_void_pointer (void ** esp);

void push_char_pointer_pointer (void ** esp, char ** pointer);

#endif