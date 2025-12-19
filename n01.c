#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void son_func(char *s) {
  key_t key1 = ftok(s, 1);
  semget(key1, 2, 0666); // массив семафоров
  shmget(key1, 1024, 0666); // разделяемая память
  msgget(key1, 0666); // очередь сообщений

  exit(0);
}
/*
union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};
*/
int semid, shmid, msqid;
//union semun dummy;
void sig(int s) {
  semctl(semid, 2, IPC_RMID, 0);
  shmctl(shmid, IPC_RMID, 0);
  msgctl(msqid, IPC_RMID, 0);
}

int main (int argc, char*argv[]) {
	
	signal(SIGINT, sig);

  key_t key = ftok(argv[0], 1);

  semid = semget(key, 2, IPC_CREAT|0666); // массив семафоров
  shmid = shmget(key, 1024, IPC_CREAT|0666); // разделяемая память
  msqid = msgget(key, IPC_CREAT|0666); // очередь сообщений

  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 0);


  if (fork()==0) {
    son_func(argv[0]);
  }
  
  //sleep(5);

  while(wait(0)!=-1);
 
  raise(SIGINT);

  
  return 0;

}