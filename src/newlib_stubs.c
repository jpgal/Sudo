/* Define caddr_t as char* */
#include <sys/types.h>

/* Define abort() */
#include <stdlib.h>

/* Needed for fstat */
#include <sys/stat.h>

/******************************************************
 * System call reference with suggested stubs:
 * http://sourceware.org/newlib/libc.html#Syscalls
 *****************************************************/

void _exit(int status)
{
  while(1);
}

caddr_t _sbrk(int incr)
{
  extern char _end; /* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;

  /* From http://sourceware.org/ml/newlib/2006/msg00099.html */
  register char *stack_ptr asm("sp"); 

  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    abort();
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}

/* Bare metal, no processes, so error */
int _kill(int pid, int sig)
{
  return -1;
}

/* Bare metal, no processes, so always process id 1 */
int _getpid(void)
{
  return 1;
}

void *__dso_handle = 0;
