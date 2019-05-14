#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/vaddr.h"
#include "filesys/off_t.h"

static void syscall_handler (struct intr_frame *);

/* ----------------------------------------------------------------- */
typedef int pid_t;

struct file{
  struct inode *inode;
  off_t pos;
  bool deny_write;
};

void syscall_init (void);
void halt (void);
void exit (int status);
pid_t exec (const char *cmd_lime);
int wait (pid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);
int open (const char *file); int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);

void is_user_addr_valid(const void *vaddr);

/* ----------------------------------------------------------------- */

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //printf ("system call!\n");
  //thread_exit ();
  is_user_addr_valid(f->esp);  
  is_user_addr_valid(f->esp + 20);

  switch (*(int *)(f->esp)) {
    case SYS_HALT:
      halt();
      break;
    case SYS_EXIT:
      is_user_addr_valid(f->esp + 4);
      exit(*(int *)(f->esp + 4));
      break;
    case SYS_EXEC:
      is_user_addr_valid(f->esp + 4);
      f->eax = exec(*(int *)(f->esp + 4));
      break;
    case SYS_WAIT:
      is_user_addr_valid(f->esp + 4);
      f->eax = wait(*(pid_t *)(f->esp + 4));
      break;
    case SYS_CREATE:
      is_user_addr_valid(f->esp + 4);
      is_user_addr_valid(f->esp + 8);
      f->eax = create(*(int *)(f->esp + 4), *(unsigned *)(f->esp + 8));
      break;
    case SYS_REMOVE:
      is_user_addr_valid(f->esp + 4);
      f->eax = remove(*(int *)(f->esp + 4));
      break;
    case SYS_OPEN:
      is_user_addr_valid(*(int *)(f->esp + 4));
      f->eax = open(*(int *)(f->esp + 4));
      break;
    case SYS_FILESIZE:
      is_user_addr_valid(*(int *)(f->esp + 4));
      f->eax = filesize(*(int *)(f->esp + 4));
      break;
    case SYS_READ:
      is_user_addr_valid(f->esp + 4);
      is_user_addr_valid(f->esp + 8);
      is_user_addr_valid(f->esp + 12);
      f->eax = read((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp + 8), (unsigned)*((uint32_t *)(f->esp + 12)));
      break;
    case SYS_WRITE:
      is_user_addr_valid(f->esp + 4);
      is_user_addr_valid(f->esp + 8);
      is_user_addr_valid(f->esp + 12);
      f->eax = write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp + 8), (unsigned)*((uint32_t *)(f->esp + 12)));
      break;
    case SYS_SEEK:
      is_user_addr_valid(f->esp + 4);
      is_user_addr_valid(f->esp + 8);
      seek(*(int *)(f->esp + 16), *(int *)(f->esp + 20));
      break;
    case SYS_TELL:
      is_user_addr_valid(f->esp + 4);
      f->eax = tell(*(int *)(f->esp +4));
      break;
    case SYS_CLOSE:
      is_user_addr_valid(f->esp + 4);
      close(*(int *)(f->esp + 4));
      break;
  }
}

void halt (void){
  shutdown_power_off();
}

void exit (int status){
  int i;
  printf("%s: exit(%d)\n", thread_name(), status);
  thread_current()->exit_status = status;
  for (i = 3; i < 128; i++){
    if (thread_current()->fd[i] != NULL)
      close(i);
  }
  thread_exit();
}

pid_t exec (const char *cmd_line){
  return process_execute(cmd_line);
}

int wait (pid_t pid){
  return process_wait(pid);
}

bool create (const char *file, unsigned initial_size){
  if (file == NULL)
    exit(-1);
  is_user_addr_valid(file);
  return filesys_create(file, initial_size);
}

bool remove (const char *file){
  if (file == NULL)
    exit(-1);
  is_user_addr_valid(file);
  return filesys_remove(file);
}

int open (const char *file){
  int i;
  struct file* file_ptr;
  if (file == NULL)
    exit(-1);
  is_user_addr_valid(file);
  file_ptr = filesys_open(file);
  if(file_ptr != NULL) {
    for (i = 3; i < 128; i++) {
      if(thread_current()->fd[i] == NULL) {
        if (strcmp(thread_current()->name, file) == 0) {
          file_deny_write(file_ptr);
        }
        thread_current()->fd[i] = file_ptr;
        return i;
      }
    }
  } else {
    return -1;
  }
  return -1;
}

int filesize (int fd){
  if (thread_current()->fd[fd] == NULL)
    exit(-1);
  return file_length(thread_current()->fd[fd]);
}

int read (int fd, void* buffer, unsigned size){
  int i;
  is_user_addr_valid(buffer);
  if (fd == 0) {
    for (i = 0; i < size; i++){
      if (((char *)buffer)[i] == '\0') {
        break;
      }
    }
  } else if (fd > 2) {
    if (thread_current()->fd[fd] == NULL)
      exit(-1);
    if (thread_current()->fd[fd]->deny_write != 0) {
      file_deny_write(thread_current()->fd[fd]);
    }
    return file_read(thread_current()->fd[fd], buffer, size);
  }
  return i;
}

int write (int fd, const void *buffer, unsigned size){
  is_user_addr_valid(buffer);
  if (fd == 1){
    putbuf(buffer, size);
    return size;
  } else if (fd > 2) {
    if (thread_current()->fd[fd] == NULL)
      exit(-1);
    return file_write(thread_current()->fd[fd], buffer, size);
  }
  return -1;
}

void seek (int fd, unsigned position){
  if (thread_current()->fd[fd] == NULL)
    exit(-1);
  file_seek(thread_current()->fd[fd], position);
}

unsigned tell (int fd){
  if (thread_current()->fd[fd] == NULL)
    exit(-1);
  return file_tell(thread_current()->fd[fd]);
}

void close (int fd){
  struct file* file_ptr;
  if (thread_current()->fd[fd] == NULL)
    exit(-1);
  file_ptr = thread_current()->fd[fd];
  thread_current()->fd[fd] = NULL;
  return file_close(thread_current()->fd[fd]);
}

/**/
void is_user_addr_valid(const void *vaddr){
  if(!is_user_vaddr(vaddr)){
    exit(-1);
  }
}
