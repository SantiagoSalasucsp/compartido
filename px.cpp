#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstdlib>

#define SHMSZ 27
#define KEY 0x1111

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Uso: " << argv[0] << " <texto> <numero>" << std::endl;
        exit(1);
    }

    
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (id < 0) {
        perror("semget");
        exit(11);
    }

    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0, +1, SEM_UNDO};

    
    int shmid;
    key_t key = 5678;
    char *shm, *s;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    char d[10];
    std::string txt = argv[1];
    int V = std::atoi(argv[2]);
    s = shm + 3;
    std::cout << txt << std::endl;

    while(true) {
        
        if (semop(id, &p, 1) < 0) {
            perror("semop p");
            exit(13);
        }

        
        strncpy(d, shm, 3);
        int shmv = atoi(d);

        
        if(shmv == (V-1)) {
            sprintf(shm, "%03d", V);
            std::string mensaje = txt + " HOLA SOY C++";
            strcpy(s, mensaje.c_str());
            V = V + 3;  
        }

        sleep(1);

        
        if (semop(id, &v, 1) < 0) {
            perror("semop v");
            exit(13);
        }
    }

    return 0;
}
