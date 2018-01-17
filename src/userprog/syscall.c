#include "userprog/syscall.h"
#include "userprog/usrstack.h"
#include "userprog/sysrout.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  int32_t * sp = f->esp;
  uint32_t sys_id = *(sp);
  uint32_t arg1, arg2, arg3;
  if (sys_id != SYS_HALT) {
  	if (sys_id == SYS_CREATE || sys_id == SYS_SEEK) {
  		arg1 = *(sp + 4);
  		arg2 = *(sp + 5);
  	} else if (sys_id == SYS_READ || sys_id == SYS_WRITE) {
		arg1 = *(sp + 5);
		arg2 = *(sp + 6);
		arg3 = *(sp + 7);
	} else {
		arg1 = *(sp + 1);
	}
  }
  bool no_ret = false;
  int32_t ret;
  switch (sys_id) {
  	case  SYS_HALT:                   /* Halt the operating system. */
  		halt_routine();
  		no_ret = true;
  		break;
    case SYS_EXIT:                   /* Terminate this process. */
    	exit_routine(arg1);
    	no_ret = true;
    	break;
    case SYS_EXEC:                   /* Start another process. */
    	ret = exec_routine(arg1);
    	break;
    case SYS_WAIT:                   /* Wait for a child process to die. */
    	ret = wait_routine(arg1);
    	break;
    case SYS_CREATE:                 /* Create a file. */
    	ret = create_routine(arg1, arg2);
    	break;
    case SYS_REMOVE:                 /* Delete a file. */
    	ret = remove_routine(arg1);
    	break;
    case SYS_OPEN:                   /* Open a file. */
    	ret = open_routine(arg1);
    	break;
    case SYS_FILESIZE:               /* Obtain a file's size. */
    	ret = filesize_routine(arg1);
    	break;
    case SYS_READ:                   /* Read from a file. */
    	ret = read_routine(arg1, arg2, arg3);
    	break;
    case SYS_WRITE:                  /* Write to a file. */
    	ret = write_routine(arg1, arg2, arg3);
    	break;
    case SYS_SEEK:                   /* Change position in a file. */
    	seek_routine(arg1, arg2);
    	no_ret = true;
    	break;
    case SYS_TELL:                   /* Report current position in a file. */
    	ret = tell_routine(arg1);
    	break;
    case SYS_CLOSE:                  /* Close a file. */
		close_routine(arg1);
		no_ret = true;
		break;  
  }
  if (!no_ret) {
  	f->eax = ret;
  }
}
