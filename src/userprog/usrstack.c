#include "userprog/usrstack.h"
#include <string.h>

void push_int32_t (void ** esp, int32_t value) {
	*esp -= sizeof(int32_t);
	*((int *)*esp) = value;
}

int32_t pop_int32_t (void ** esp) {
	int32_t value = *((int32_t *)*esp);
	*esp += sizeof(int32_t);
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

void push_str (void ** esp, const char *s) {
	size_t len = strlen(s) + 1;
	*esp -= (len * sizeof(char));
	memcpy(*esp, s, len);
}

void push_word_align (void ** esp) {
	int offset = (((int)*esp) % 4);
	if (offset < 0) {
		offset *= -1;
	}
	*esp -= offset;
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
