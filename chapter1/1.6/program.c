#include "apue.h"

int main(void){
	printf("hello word from process ID %ld\n",(long)getpid());
	exit(0);
}
