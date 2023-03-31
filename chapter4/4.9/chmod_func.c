#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

crt(void);
crt(void){
    umask(0);
    if (creat("foo.test",RWRWRW) < 0) err_sys("create error for foo.test");
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (creat("bar.test",RWRWRW) < 0) err_sys("creat error for bar");
}

int main(void) {
    // create file
    crt();
    struct stat statbuf;
    /* turn on set-group-id and turn off group-execute */ 
    if (stat("foo.test",&statbuf) < 0) err_sys("stat error for foo.test");
    if (chmod("foo.test",(statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) err_sys("chmod error for foo");
    /* set absolute mode to "rw-r--r--" */
    if (chmod("bar.test",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0 ) err_sys(" chmod error for bar");
    exit(0);
}