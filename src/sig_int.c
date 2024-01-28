#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sig_int_handler(int);

int main() {

	signal(SIGINT, SIG_IGN);
	puts("into infinite loop");

	while(1);
	return 0;
}

void sig_int_handler(int) {
	puts("In signal handler");
}
