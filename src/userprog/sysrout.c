#include <stdbool.h>
#include "userprog/sysrout.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
#include "devices/shutdown.h"
#include "devices/input.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/malloc.h"
#include "userprog/process.h"
#include <stdio.h>

static struct lock file_lock;  /* Synchronizes file system access. */

void init_routine (void) {
	lock_init (&file_lock);
}

void halt_routine (void) {
    shutdown_power_off();
}

void exit_routine (int status) {
    struct thread *t = thread_current ();
    t->ret_status = status;
    thread_exit();
}

pid_t exec_routine (const char *file) {
    return process_execute(file);
}

int wait_routine (pid_t id) {
    return process_wait(id);
}

bool create_routine (const char *file, unsigned initial_size) {
    lock_acquire(&file_lock);
    bool create = filesys_create(file, initial_size);
    lock_release(&file_lock);
    return create;
}

bool remove_routine (const char *file) {
    lock_acquire(&file_lock);
	bool remove = filesys_remove(file);
    lock_release(&file_lock);
    return remove;
}

int open_routine (const char *file) {
    lock_acquire(&file_lock);
    struct thread *t = thread_current ();
    struct file_elem *e = malloc(sizeof(struct file_elem));
    struct file *f = filesys_open(file);
    if (f == NULL) {
        lock_release(&file_lock);
        return -1;
    }
    e->file = f;
    e->fd = t->fd;
    t->fd = t->fd + 1;
    list_push_front (&t->file_elems, &e->elem);
    lock_release(&file_lock);
    return e->fd;
}

int filesize_routine (int fd) {
    lock_acquire(&file_lock);
    struct thread *t = thread_current ();
    struct file_elem * f;
    struct list_elem *e;
    for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        f = list_entry(e, struct file_elem, elem);
        if(f->fd == fd){
          int length = file_length(f->file);
          lock_release(&file_lock);
          return length;
        }
    }
    lock_release(&file_lock);
    return -1;
}

int read_routine (int fd, void *buffer, unsigned length) {
    lock_acquire(&file_lock);
	if (fd == STDIN_FILENO){
        buffer = input_getc();
        return length;
	}
    struct thread *t = thread_current ();
    struct file_elem * f;
    struct list_elem * e;
    for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        f = list_entry(e, struct file_elem, elem);
        if(f->fd == fd){
            int bytes = file_read(f->file, buffer, length);
            lock_release(&file_lock);
            return bytes;
        }
    }
	lock_release(&file_lock);
	return -1;
}

int write_routine (int fd, const void *buffer, unsigned length) {
	lock_acquire(&file_lock);
	if (fd == STDOUT_FILENO){
        putbuf (buffer, length);
        lock_release(&file_lock);
        return length;
	} else {
		struct thread *t = thread_current ();
		struct file_elem * f;
		struct list_elem * e;
		for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        	f = list_entry(e, struct file_elem, elem);
        	if(f->fd == fd){
          		int bytes = file_write(f->file, buffer, length);
          		lock_release(&file_lock);
          		return bytes;
        	}
    	}
	}
	lock_release(&file_lock);
	return 0;
}

void seek_routine (int fd, unsigned position) {
	lock_acquire(&file_lock);
	struct thread *t = thread_current();
    struct file_elem * f;
    struct list_elem * e;
    for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        f = list_entry(e, struct file_elem, elem);
        if(f->fd == fd){
         	file_seek(f->file , position);
          	lock_release(&file_lock);
        }
    }
	lock_release(&file_lock);
}

unsigned tell_routine (int fd) {
    lock_acquire(&file_lock);
    struct thread *t = thread_current();
    struct file_elem * f;
    struct list_elem * e;
    for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        f = list_entry(e, struct file_elem, elem);
        if(f->fd == fd){
         	int offset = file_tell(f->file);
          	lock_release(&file_lock);
         	return offset;
        }
    }
    lock_release(&file_lock);
	return 0;
}
void close_routine (int fd) {
    lock_acquire(&file_lock);
    struct thread *t = thread_current();
    struct file_elem * f;
    struct list_elem * e;
    for (e = list_begin (&t->file_elems); !list_empty (&t->file_elems) && e != list_end (&t->file_elems); e = list_next (e)) {
        f = list_entry(e, struct file_elem, elem);
        if(f->fd == fd){
         	file_close(f->file);
         	list_remove(&(f->elem));
         	free(f);
          	lock_release(&file_lock);
         	return;
        }
    }
    lock_release(&file_lock);
}
