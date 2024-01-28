#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // strlen
#include <errno.h>
#include <sys/msg.h> // msgget, msgctl, ftok etc.

#define MAX_MSG_LEN 200

struct my_msgbuf {
    long mtype;
    char mtext[MAX_MSG_LEN];
};

int main(void) {
    struct my_msgbuf my_msg;
    int msqid;
    key_t key;
    const char *home = getenv("HOME");
    printf("%s\n", home);
    // get an id for the queue
    if ((key = ftok(home, 'y')) == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    // create the queue, if it exists then fail, prmssins = 0600
    if ((msqid = msgget(key,
                        0600 | IPC_CREAT | IPC_EXCL)) == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    printf("key = %ld, msqid = %d\n", (long)key, msqid);
    puts("Enter lines of text, ^D to quit:");
    my_msg.mtype = 1;
    // repeatedly, read data and send it to the queue
    while (fgets(my_msg.mtext, MAX_MSG_LEN, stdin) != NULL) {
        if (msgsnd(msqid,
                   (struct msgbuf *)&my_msg,
                   strlen(my_msg.mtext) + 1,
                   0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }
        my_msg.mtype++;
        if (my_msg.mtype > 3) {
            my_msg.mtype = 1;
        }
    }
    // remove the queue
    // at this point receiver fails to read from queue
    // (msgrcv fail) so it exits
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
