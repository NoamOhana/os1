#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <unistd.h> // sleep()
#include <time.h>
//---------------------------------------------------
struct Data
{
    pid_t _id;
    int _num;
};
struct my_msgbuf
{
    long mtype;
    struct Data _data;
};
//---------------------------------------------------
int main(void)
{
    struct my_msgbuf my_msg;
    int msqid;
    int i;
    key_t key;
    srand(time(NULL));
    if ((key = ftok("/tmp", 'y')) == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    if ((msqid = msgget(key, 0)) == -1)
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 5; i++)
    {
        sleep(rand() % 3);
        my_msg.mtype = 1;
        my_msg._data._id = getpid();
        my_msg._data._num = rand() % 100;
        printf("%d send %d to server\n", (int)getpid(),
               my_msg._data._num);
        if (msgsnd(msqid, &my_msg,
                   sizeof(struct Data), 0) == -1)
        {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }
        sleep(rand() % 3);
        if (msgrcv(msqid, &my_msg,
                   sizeof(struct Data), (int)getpid(), 0) == -1)
        {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("%d get %d from server\n", (int)getpid(),
               my_msg._data._num);
    }
    return EXIT_SUCCESS;
}