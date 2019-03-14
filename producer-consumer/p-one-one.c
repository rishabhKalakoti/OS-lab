include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#define SIZE 10
#define KEY 1234
int *Memory;
int i, j;
sem_t *sem;
char *name = "Hello";
int main(int argc, const char *argv[])
{
    int shmid;
    if ((shmid = shmget(KEY, sizeof(int) * SIZE, IPC_CREAT | S_IRWXU)) < 0)
    {
        perror("Error while creating shmget");
        return 1;
    }
    pid_t pid;
    sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, 1);
    if ((pid = fork()) != 0)
    {
        if ((shmid = shmget(KEY, sizeof(int) * SIZE, S_IRWXU)) < 0)
        {
            perror("error in shmget");
            return 1;
        }
        Memory = (int *)shmat(shmid, NULL, 0);
        if (Memory == NULL)
        {
            perror("error in shmat");
            return 1;
        }
        for (i = 0; i < 10; i++)
        {
            sem_wait(sem);
            Memory[j] = i;
            printf("Produced %i in box %i\n", i + 1, i + 1);
            sem_post(sem);
            sleep(1);
        }
        int status;
        wait(&status);
        sem_unlink(name);
        sem_destroy(sem);
        struct shmid_ds shmid_ds1;
        if (shmctl(shmid, IPC_RMID, &shmid_ds1) < 0)
        {
            perror(
                "Error in the father while executing shmctl when it was "
                "elimnating the segment of shared memory");
        }
    }
    else
    {
        if ((shmid = shmget(KEY, sizeof(int) * SIZE, S_IRWXU)) < 0)
        {
            perror("error in the producer with the shmget");
            return 1;
        }
        Memory = (int *)shmat(shmid, NULL, 0);
        if (Memory == NULL)
        {
            perror("error in the producer with the  shmat");
            return 1;
        }
        for (i = 0; i < 10; i++)
        {
            sem_wait(sem);
            Memory[i] = -1;
            printf("Consume and now it is %i in box %i\n", Memory[i], i + 1);
            sem_post(sem);
        }
    }
    return 0;
}
