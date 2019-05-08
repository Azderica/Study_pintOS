#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include <stdio.h>

void syscall_init (void);
typedef int pid_t;

/* Stanford pdf page 29~32, System call */
void halt (void);
void exit (int status);
pid_t exec (const char *cmd_line);
int wait (pid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);

/* Other function for system call*/
void is_user_addr_valid(const void *vaddr);
struct file* find_file_by_its_fd(int fd);
char *get_real_file_name(const char *cmd_line);
#endif /* userprog/syscall.h */
