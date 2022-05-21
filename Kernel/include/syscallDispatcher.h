#ifndef SYSCALL_DISPATCHER_H

#define SYSCALL_DISPATCHER_H

static int sys_write(unsigned int fd, const char * buf, unsigned int count);
int sys_read(unsigned int fd, char * buf, unsigned int count);

#endif
