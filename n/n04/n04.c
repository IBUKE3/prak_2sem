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


int msqid_c2s, msqid_s2c;

struct {
  long mtype;
} Message;


void sig(int s) {
  msgctl(msqid_c2s, IPC_RMID, 0);
  msgctl(msqid_s2c, IPC_RMID, 0);
}

int main (int argc, char*argv[]) {
	
  signal(SIGINT, sig);

  key_t key = ftok(argv[0], 1);
  key_t key2 = ftok(argv[0], 2);

  //semid = semget(key, 2, IPC_CREAT|0666); // массив семафоров
  //shmid = shmget(key, 1024, IPC_CREAT|0666); // разделяемая память
  msqid_c2s = msgget(key, IPC_CREAT|0666); // очередь сообщений
  msqid_s2c = msgget(key2, IPC_CREAT|0666);


  if (fork()==0) {
    int m = 0;
    while(1) {
      msgrcv(msqid_c2s, (&Message), 0, 0, 0); // любой тип получаем
      if (Message.mtype == 1) {
        m++;
      }
      else if (Message.mtype == 2) {
        Message.mtype = m;
        msgsnd(msqid_s2c, (&Message), 0, 0);
      }
      else if (Message.mtype == 3) {
        exit(0);
      }
    }
  }
  int N;
  if(scanf("%d", &N)==0) return 1;
  if (fork()==0) {
    // client
    Message.mtype = 1;
    for (int i = 0; i < N; i++) {
      msgsnd(msqid_c2s, (&Message), 0, 0);
    }
    Message.mtype = 2;
    msgsnd(msqid_c2s, (&Message), 0, 0);
    msgrcv(msqid_s2c, (&Message), 0, 0, 0);
    printf("%ld\n", Message.mtype);
    Message.mtype = 3;
    msgsnd(msqid_c2s, (&Message), 0, 0);
    exit(0);
  }

  while(wait(0)!=-1);
 
  raise(SIGINT);

  
  return 0;


}
