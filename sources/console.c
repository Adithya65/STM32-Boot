#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include "stm_uart.h"

extern char _end;
extern char _heap_end;
static char *heap_end = 0;

int __io_putchar(int ch)
{
    uart_write((uint8_t)ch);
    return ch;
}

int _write(int file, char *ptr, int len)
{
    (void)file;
    for (int volatile i = 0; i < len; i++) 
    {
        uart_write(ptr[i]);
    }
    return len;
}

int _close(int file)
{ 
    (void)file;
    return -1; 
}

int _fstat(int file, struct stat *st)
{
    (void)file;
    (void)st;
    return 0;
}

int _isatty(int file) 
{ 
    (void)file;
    return 1; 
}

int _lseek(int file, int ptr, int dir) 
{ 
    (void)file;
    (void)ptr;
    (void)dir;
    return 0; 
}

int _read(int file, char *ptr, int len)
{
    if (file == 0)  
    {
        for (int volatile i = 0; i < len; i++)
        {
            int c = uart_read();  
            if (c < 0)
                return i;  
            ptr[i] = (char)c;
        }
        return len;
    }
    return -1; 
}

int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

int _getpid(void) 
{ 
    return 1; 
}

void _exit(int status)
{
    (void)status;
    while (1); 
}

void* _sbrk(ptrdiff_t incr)
{
    char *prev_heap_end =NULL;
    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

    if ((heap_end + incr) > &_heap_end) 
    {
        errno = ENOMEM;
        return (void *) -1;
    }

    heap_end += incr;
    return (void *)prev_heap_end;
}
