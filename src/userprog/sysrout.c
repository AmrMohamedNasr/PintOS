#include <stdbool.h>
#include "userprog/sysrout.h"

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
	// Please implement me.
}

bool remove_routine (const char *file) {
	// Please implement me.
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
	// Please implement me.
}

unsigned tell_routine (int fd) {
	// Please implement me.
}

void close_routine (int fd) {
	// Please implement me.
}