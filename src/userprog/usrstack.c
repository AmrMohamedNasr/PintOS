#include "userprog/usrstack.h"

void push_int (void ** esp, int value) {
	*esp -= sizeof(int);
	*((int *)*esp) = value;
}

int pop_int (void ** esp) {
	int value = *((int *)*esp);
	*esp += sizeof(int);
	return value;
}

void push_char (void ** esp, char c) {
	*esp -= sizeof(char);
	*((char *)*esp) = c;
}

char pop_char (void ** esp) {
	char c = *((char *)*esp);
	*esp += sizeof(char);
	return c;
}

void push_word_align (void ** esp) {
	*esp -= (((int)*esp) % 4);
}

void push_void_pointer (void ** esp, void *pointer) {
	*esp -= sizeof(void *);
	*((void **)*esp) = pointer;
}

void * pop_void_pointer (void ** esp) {
	void * pointer = *((void **)*esp);
	*esp += sizeof(void *);
	return pointer;
}

void push_char_pointer_pointer (void ** esp, char ** pointer) {
	*esp -= sizeof(char **);
	*((char ***)*esp) = pointer;
}
