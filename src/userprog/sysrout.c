#include <stdbool.h>
#include "userprog/sysrout.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
void halt_routine (void) {
	// Please implement me.
}

void exit_routine (int status) {
	// Please implement me.
}

pid_t exec_routine (const char *file) {
	// Please implement me.
}

int wait_routine (pid_t id) {
	// Please implement me.
}

bool create_routine (const char *file, unsigned initial_size) {
	return filesys_create(file, initial_size);
}

bool remove_routine (const char *file) {
	return filesys_remove(file);
}

int open_routine (const char *file) {
	// Please implement me.
}

int filesize_routine (int fd) {
	// Please implement me.
}

int read_routine (int fd, void *buffer, unsigned length) {
	// Please implement me.
}

int write_routine (int fd, const void *buffer, unsigned length) {
	// Please implement me.
}

void seek_routine (int fd, unsigned position) {
	if (position == 0) {
		// TODO
	}
	file_seek ( (struct file *) fd , (off_t) position);
}

unsigned tell_routine (int fd) {
	return (unsigned) file_tell ((struct file *) fd );
}

void close_routine (int fd) {
	// Please implement me.
}
