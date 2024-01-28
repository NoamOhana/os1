#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
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
void catch_term(int s);
int is_prime(int n);
//---------------------------------------------------
int end = 0;
//---------------------------------------------------
int main(void)
{
    struct my_msgbuf my_msg;
    int msqid;
    key_t key;
    signal(SIGTERM, catch_term);
    if ((key = ftok("/tmp", 'y')) == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }
    if ((msqid = msgget(key, 0600 | IPC_CREAT | IPC_EXCL)) == -1)
    {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (msgrcv(msqid, &my_msg,
                   sizeof(struct Data), 1, 0) == -1)
        {
            perror("msgrcv failed");
            end = 1;
            // exit(EXIT_FAILURE);
        }
        my_msg.mtype = my_msg._data._id;
        my_msg._data._num = is_prime(my_msg._data._num);
        if (!end && msgsnd(msqid, &my_msg,
                           sizeof(struct Data), 0) == -1)
        {
            perror("msgsnd failed");
            end = 1;
            // exit(EXIT_FAILURE);
        }
        if (end) {
            if (msgctl(msqid, IPC_RMID, NULL) == -1)
            {
                perror("msgctl failed");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}
//---------------------------------------------------
void catch_term(int s)
{
    end = 1;
}
//---------------------------------------------------
int is_prime(int n)
{
    int div;
    for (div = 2; div <= n / 2; div++)
        if (n % div == 0)
            return 0;
    return 1;
}