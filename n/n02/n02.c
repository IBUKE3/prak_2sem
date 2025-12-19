#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

char flag;
int N;

void son_func(char *s) {
  key_t key1 = ftok(s, 1);
  int semid1 = semget(key1, 2, 0666); // массив семафоров
  //shmget(key1, 1024, 0666); // разделяемая память
  //msgget(key1, 0666); // очередь сообщений
  
  struct sembuf opup;
  opup.sem_num = 0;
  opup.sem_flg = 0;
  opup.sem_op = 1;

  struct sembuf opdown;
  opdown.sem_num = 0;
  opdown.sem_flg = 0;
  opdown.sem_op = -1;

  struct sembuf opup1;
  opup1.sem_num = 1;
  opup1.sem_flg = 0;
  opup1.sem_op = 1;

  struct sembuf opdown1;
  opdown1.sem_num = 1;
  opdown1.sem_flg = 0;
  opdown1.sem_op = -1;

  
  if (!flag) {
    // четный сын
    for (int i = 0; i < N; i+=2) {
      semop(semid1, &opdown, 1);
      printf("%d\n", i);
      semop(semid1, &opup1, 1);
    }
  }

  if (flag) {
    // нечетный сын
    for (int i = 1; i < N; i+=2) {
      semop(semid1, &opdown1, 1);
      printf("%d\n", i);
      semop(semid1, &opup, 1);
    }
  }

  exit(0);
}

int semid, shmid, msqid;

void sig(int s) {
  semctl(semid, 2, IPC_RMID, 0);
  //shmctl(shmid, IPC_RMID, 0);
  //msgctl(msqid, IPC_RMID, 0);
}

int main (int argc, char*argv[]) {
	
  signal(SIGINT, sig);

  key_t key = ftok(argv[0], 1);

  semid = semget(key, 2, IPC_CREAT|0666); // массив семафоров
  //shmid = shmget(key, 1024, IPC_CREAT|0666); // разделяемая память
  //msqid = msgget(key, IPC_CREAT|0666); // очередь сообщений

  semctl(semid, 0, SETVAL, 1); // в нулевом единица
  semctl(semid, 1, SETVAL, 0);

  N;
  scanf("%d", &N);

  flag = 0;
  if (fork()==0) {
    son_func(argv[0]);
  }

  flag = 1;
  if (fork()==0) {
    son_func(argv[0]);
  }

  while(wait(0)!=-1);
 
  raise(SIGINT);

  
  return 0;
}

