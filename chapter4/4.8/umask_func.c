#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

mode_t read_umask(void);

int main(void){
    umask(0);
    read_umask();
    if (creat("foo.test",RWRWRW) < 0) err_sys("create error for foo.test");
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    read_umask();
    if (creat("bar.test",RWRWRW) < 0) err_sys("creat error for bar");
    exit(0);
}

mode_t read_umask (void)
{
	mode_t mask = umask (0);
	umask (mask);
    printf("current umask is %04o\n",mask);
    return mask;
}
