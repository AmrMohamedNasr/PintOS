#include <stdbool.h>
#include "userprog/sysrout.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
#include "devices/shutdown.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "userprog/process.h"
#include <stdio.h>

static struct lock file_lock;  /* Synchronizes file system access. */

void halt_routine (void) {
    shutdown_power_off();
}

void exit_routine (int status) {
    thread_current ()->ret_status = status;
    thread_exit();
}

pid_t exec_routine (const char *file) {
    return process_execute(file);
}

int wait_routine (pid_t id) {
    return process_wait(id);
}

bool create_routine (const char *file, unsigned initial_size) {
    printf("executing create\n");

    lock_acquire(&file_lock);
    bool create = filesys_create(file, initial_size);
    lock_release(&file_lock);
    return create;
}

bool remove_routine (const char *file) {
    printf("executing remove\n");

    lock_acquire(&file_lock);
	bool remove = filesys_remove(file);
    lock_release(&file_lock);
    return remove;
}

int open_routine (const char *file) {
    printf("executing open\n");
    lock_acquire(&file_lock);
    struct thread *t = thread_current ();
    struct file_elem *e;
    struct file *f = filesys_open(file);
    if (f == NULL)
        return -1;
    e.file = f;
    e.fd = t->fd;
    t->fd = t->fd + 1;
    list_push_front (&t->file_elems, &e.elem);
    lock_release(&file_lock);
    return f.fd;
}

int filesize_routine (int fd) {
    printf("executing filesize\n");

    lock_acquire(&file_lock);

    lock_release(&file_lock);

}

int read_routine (int fd, void *buffer, unsigned length) {
    printf("executing read\n");

	// Please implement me.
}

int write_routine (int fd, const void *buffer, unsigned length) {
    //printf("executing write\n");
	lock_acquire(&file_lock);
	if (fd == STDOUT_FILENO){
        putbuf (buffer, length);
	}
	lock_acquire(&file_lock);
	return length;
}

void seek_routine (int fd, unsigned position) {
    printf("executing seek\n");

	if (position == 0) {
		// TODO
	}
	file_seek ( (struct file *) fd , (off_t) position);
}

unsigned tell_routine (int fd) {
    printf("executing tell\n");

	return (unsigned) file_tell ((struct file *) fd );
}

void close_routine (int fd) {
    printf("executing close\n");

	// Please implement me.
}
