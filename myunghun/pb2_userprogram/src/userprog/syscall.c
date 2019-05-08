#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "list.h"
#include "process.h"
#include "threads/synch.h"

static void syscall_handler (struct intr_frame *);
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/

static struct semaphore sema_;
static int fd = 2;

struct file_fd_map {
  struct file* file_;
  int fd;
  struct list_elem elem;
};

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/


void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  sema_init(&sema_, 1);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  is_user_addr_valid(f->esp);

  switch(*(int *)(f->esp)){
    case SYS_HALT:     
      halt(); 
      break;
    case SYS_EXIT:
      is_user_addr_valid(f->esp);
      exit(*(int *)(f->esp + 4));
      break;
    case SYS_EXEC:
      is_user_addr_valid(*(int *)(f->esp+4));
      sema_down(&sema_);
      f->eax = exec(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
    case SYS_WAIT:
      is_user_addr_valid(f->esp+4);
      f->eax = wait(*(pid_t *)(f->esp + 4));
      break;
    case SYS_CREATE:
      is_user_addr_valid(f->esp+16);
      is_user_addr_valid(f->esp+20);
      is_user_addr_valid(*(int *)(f->esp+16));
      sema_down(&sema_);
      f->eax = create(*(int *)(f->esp + 16),*(unsigned *)(f->esp + 20));
      sema_up(&sema_);
      break;
    case SYS_REMOVE:
      is_user_addr_valid(f->esp+4);
      sema_down(&sema_);
      f->eax = remove(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
    case SYS_OPEN:
      is_user_addr_valid(*(int *)(f->esp+4));
      sema_down(&sema_);
      f->eax = open(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
    case SYS_FILESIZE:
      is_user_addr_valid(f->esp+4);
      sema_down(&sema_);
      f->eax = filesize(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
    case SYS_READ:
      is_user_addr_valid(f->esp+16);
      is_user_addr_valid(f->esp+20);
      is_user_addr_valid(f->esp+24);
      is_user_addr_valid(*(int *)(f->esp+24));
      sema_down(&sema_);
      f->eax = read(*(int *)(f->esp+20), *(int *)(f->esp+24), *(unsigned *)(f->esp+28));
      sema_up(&sema_);
      break;
    case SYS_WRITE:
      is_user_addr_valid(f->esp+16);
      is_user_addr_valid(f->esp+20);
      is_user_addr_valid(f->esp+24);
      is_user_addr_valid(*(int *)(f->esp+24));
      sema_down(&sema_);
      f->eax = write(*(int *)(f->esp+20), *(int *)(f->esp+24), *(unsigned *)(f->esp+28));
      sema_up(&sema_);
      break;
    case SYS_SEEK:
      is_user_addr_valid(f->esp+16);
      is_user_addr_valid(f->esp+20);
      sema_down(&sema_);
      seek(*(int *)(f->esp+16), *(int *)(f->esp+20));
      sema_up(&sema_);
      break;
    case SYS_TELL:
      is_user_addr_valid(f->esp+4);
      sema_down(&sema_);
      f->eax = tell(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
    case SYS_CLOSE:
      is_user_addr_valid(f->esp+4);
      sema_down(&sema_);
      close(*(int *)(f->esp+4));
      sema_up(&sema_);
      break;
  }
}

void halt(void){
  shutdown_power_off();
}

void exit(int status){
  struct list_elem *e1 = NULL;
  e1 = findsChildbyId(thread_current()->tid, &thread_current()->parent->children);
  if(e1 != NULL){
    struct child *ch = list_entry(e1, struct child, elem);
    if(ch == NULL){
      thread_exit();
      return;
    }
    ch->alive = false;
    ch->exit_status = status;
    ch->hold_lock_or_not = false;

    thread_current()->killed_notby_kernel = false;
    thread_current()->exit_status = status;

    thread_exit();
  } else {
    thread_exit();
    return;
  }
}

pid_t exec(const char *cmd_line){
  struct file* file_ = filesys_open(get_real_file_name(cmd_line));
  if(file_ != NULL){
    file_close(file_);
    return process_execute(cmd_line);
  } else
    return -1;
}

int wait(pid_t pid){
  return process_wait(pid);
}

bool create(const char *file, unsigned initial_size){
  return filesys_create(file, initial_size);
}

bool remove(const char *file){
  return filesys_remove(file);
}

int open (const char *file){
  struct file *file_ = filesys_open(file);
  if(file_ != NULL){
    struct file_fd_map *ffd_map = malloc(sizeof(struct file_fd_map));
    ffd_map->file_ = file_;
    ffd_map->fd = ++fd;
    list_push_back(&thread_current()->files, &ffd_map->elem);
    return fd;
  }
  else
    return -1;
}

int filesize (int fd){
  if(find_file_by_its_fd(fd) != NULL){
    struct file *file_ = find_file_by_its_fd(fd);
    return file_length(file_);
  } else
    exit(-1);
}

int read(int fd, void* buffer, unsigned size){
  if(fd == STDIN_FILENO){
    uint8_t *buffer_ = (uint8_t *)buffer;
    int i;
    for(i = 0; i<size; i++)
      buffer_[i] = input_getc();
    return size;
  } else {
    if(find_file_by_its_fd(fd) != NULL){
      struct file *file_ = find_file_by_its_fd(fd);
      return file_read(file_, buffer, size);
    }
  }
  return -1;
}

int write(int fd, const void *buffer, unsigned size){
  if(fd == STDOUT_FILENO){
    putbuf(buffer, size);
    return size;
  } else {
    if(find_file_by_its_fd(fd) != NULL){
      struct file *file_ = find_file_by_its_fd(fd);
      return file_write(file_, buffer, size);
    }
  }
  return -1;
}

void seek (int fd, unsigned position){
  if(find_file_by_its_fd(fd) != NULL){
    struct file *file_ = find_file_by_its_fd(fd);
    file_seek(file_, position);
  } else
    return;
}

unsigned tell(int fd){
  if(find_file_by_its_fd(fd) != NULL){
    struct file *file_ = find_file_by_its_fd(fd);
    return file_tell(file_);
  } else
    exit(-1);
}

void close(int fd){
  if(!list_empty(&thread_current()->files)){
    struct list_elem *e;
    for(e = list_begin(&thread_current()->files); e!= list_end(&thread_current()->files); e=list_next(e)){
      struct file_fd_map *ffd_map = list_entry(e, struct file_fd_map, elem);
      if(ffd_map->fd == fd){
        file_close(ffd_map->file_);
        list_remove(e);
      }
    }
  }
}

/*---------------------------------------------------------------------*/
void is_user_addr_valid(const void *vaddr)
{
  if(!is_user_vaddr(vaddr) || !pagedir_get_page(thread_current()->pagedir, vaddr)){
    exit(-1);
  }
}

struct file* find_file_by_its_fd(int fd){
  if(!list_empty(&thread_current()->files)){
    struct list_elem *e;
    for(e = list_begin(&thread_current()->files); e != list_end(&thread_current()->files); e = list_next(e)){
      struct file_fd_map *ffd_map = list_entry(e, struct file_fd_map, elem);
      if(ffd_map->fd == fd){
        return ffd_map->file_;
      }
    }
  }
  return NULL;
}

char *get_real_file_name(const char *cmd_line){
  char *fn_copy = malloc(strlen(cmd_line)+1);
  strlcpy(fn_copy, cmd_line, strlen(cmd_line) + 1);
  char *saveptr;
  return strtok_r(fn_copy, " ", &saveptr);
}
