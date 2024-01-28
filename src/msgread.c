#include <stdio.h>
#include <stdlib.h> // for exit(), EXIT_SUCCESS
#include <string.h>
#include <sys/msg.h>
#define MAX_MSG_LEN 200
// define this instead of the standard msgbuf,
// as the latter does not compile
struct my_msgbuf {
    long mtype;
    char mtext[MAX_MSG_LEN];
};
int main() {
    int i;
    long int allowed_type;
    int queue_id;
    key_t key;
    const char *home = getenv("HOME");
    if ((key = ftok(home, 'y')) == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    queue_id = msgget(key, 0); // open the existing queue
    if (queue_id == -1) {
        perror("msgget failed in reader");
        exit(EXIT_FAILURE);
    }
    printf("Enter type of messages to get from queue: ");
    scanf(" %ld", &allowed_type);
    for (i = 0; i < 10; i++) {
        struct my_msgbuf my_msg;
        int status;
        status = msgrcv(queue_id,
                        (struct msgbuf *)&my_msg,
                        MAX_MSG_LEN,
                        allowed_type,
                        0);
        if (status == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Got %s from queue\n", my_msg.mtext);
    }
    return (EXIT_SUCCESS);
}