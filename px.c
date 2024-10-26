#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>


#define SHMSZ     27
#define KEY 0x1111

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, SEM_UNDO};
struct sembuf v = {0, +1, SEM_UNDO};

int main(int argc, char* argv[])
{
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (id < 0)
    {
        perror("semget");
        exit(11);
    }

    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    char d[10];
    char *txt = argv[1];
    int V = atoi(argv[2]);
    s = shm+3;
    printf("%s",txt);

    while(1){
        if (semop(id, &p, 1) < 0){
            perror("semop p");
            exit(13);
        }
        strncpy(d,shm,3);
        int shmv = atoi(d);
        if(shmv == (V-1)){
            sprintf(shm,"%03d",V);
            strcpy(s,txt);
            V=V+3;
        }
        sleep(1);
        if (semop(id, &v, 1) < 0){
            perror("semop p");
            exit(13);
        }
    }

    exit(0);
}
