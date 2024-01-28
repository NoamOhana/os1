#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
int main() {
	pid_t my_pid = getpid() ;
	int i, j ;
	for (i = 0; i< 10; i++) {
		for (j = 0; j < 10; j++)
			printf("(%d*%d = %d) ", i, j, i*j) ;
		putchar('\n') ;
		kill(my_pid, SIGSTOP) ;
	}
	return EXIT_SUCCESS ;
}
