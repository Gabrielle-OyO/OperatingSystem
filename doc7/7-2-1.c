#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define MAXSTACK 100
int stack[MAXSTACK][2];
int size=0;
sem_t S;
pthread_mutex_t mutex;

void RData1(void)
{
    FILE *fp=fopen("file1.dat", "r");
    while(!feof(fp))
    {
        pthread_mutex_lock(&mutex);
        fscanf(fp, "%d %d", &stack[size][0], &stack[size][1]);
        sem_post(&S);
        size++;
        pthread_mutex_unlock(&mutex);
    }
}

void RData2(void){
    FILE *fp=fopen("file2.dat", "r");
    while(!feof(fp))
    {
        pthread_mutex_lock(&mutex);//
        fscanf(fp, "%d %d", &stack[size][0], &stack[size][1]);
        sem_post(&S);
        size++;
        pthread_mutex_unlock(&mutex);//
    }
}

void CData1(void)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);//
        sem_wait(&S);
        printf("Plus:%d+%d=%d\n", stack[size][0],stack[size][1], stack[size][0]+stack[size][1]);
        size--;
        pthread_mutex_unlock(&mutex);//
        sleep(2);
    }
}

void CData2(void)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);//
        sem_wait(&S);
        printf("Mlutiply:%d*%d=%d\n", stack[size][0],stack[size][1], stack[size][0]*stack[size][1]);
        size--;
        pthread_mutex_unlock(&mutex);//
        sleep(2);
    }
}

int main(void)
{
    pthread_t tid1, tid2, tid3, tid4;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&S, 0, 0);
    pthread_create(&tid1, NULL, (void*)RData1, NULL);
    pthread_create(&tid3, NULL, (void*)RData2, NULL);
    pthread_create(&tid2, NULL, (void*)CData1, NULL);
    pthread_create(&tid4, NULL, (void*)CData2, NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
