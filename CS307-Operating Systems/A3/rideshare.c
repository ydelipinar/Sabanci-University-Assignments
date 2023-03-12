#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

pthread_barrier_t barrier1;
pthread_barrier_t barrier2;
pthread_barrier_t barrier3;
pthread_barrier_t barrier4;
sem_t group;
sem_t wait;
sem_t control;
sem_t four;
sem_t pair;
sem_t final;
sem_t release;

int fans[5] = {0};
int Index = 0;
int countA = 0;
int countB = 0;
int groupcount= 1;
bool first = false;
bool check = false;
bool check1 = false;
bool driver = true;

bool isPlaced(int fans[])
{
    int test = fans[0] +fans[1]+ fans[2] + fans[3];
    if(fans[3] == 0)
    {
        return false;
    }
    else if (fans[2] == 0)
    {
        return false;
    }
    else if (test%2 == 1 && fans[4] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void * routine (void * args)
{
    int x = *(int*)args;
    char  * team = "A";
    int local = 0;
    if(x == 2)
    {
        team = "B";
    }
    sem_wait(&group);
    fans[Index] = x;
    Index++;
    if(Index < 5)
    {
        local = 1;
    }
    if(!isPlaced(fans))
    {
        if(Index == 4)
        {
            first = true;
        }
        sem_post(&group);
    }
    printf("Thread ID: %ld, Team: %s, I am looking for a car\n",pthread_self(),team);
    
    if(local == 1)
    {
        pthread_barrier_wait(&barrier3);
    }

    

    if (first)
    { 
        pthread_barrier_wait(&barrier4);
        check1 = true;
        int sum = fans[0] +fans[1]+ fans[2] + fans[3] + fans[4];
        if(sum == 6)
        {
            if (x == 2)
            {
                sem_wait(&four);
            }
        }
        else if (sum == 9)
        {
            if (x == 1)
            {
                sem_wait(&four);
            }
        }
        
        else if(sum == 7)
        {
            sem_wait(&pair);
            if( x == 1 && countA <2)
            {
                countA++;
                sem_post(&pair);
            }
            else if (x ==1)
            {
                sem_post(&pair);
                sem_wait(&four);

            }
            else
            {
                 sem_post(&pair);
            }
        }
        else
        {
            sem_wait(&pair);
            if( x == 2 && countB <2)
            {
                countB++;
                sem_post(&pair);
            }
            else if (x ==2)
            {
                sem_post(&pair);
                sem_wait(&four);
            }
            else
            {
                sem_post(&pair);
            }
        }
    }
    Index = 0;
    fans[0] = 0;
    fans[1] = 0;
    fans[3] = 0;
    fans[2] = 0;
    fans[4] = 0;
    countA = 0;
    countB = 0;
    groupcount = 1;
    driver = true;
    if(check)
    {
        fans[3] = x;
        check = false;
    }
    

    pthread_barrier_wait(&barrier1);
    sem_wait(&control);
    if(check1)
    {
        check = true;
        check1 = false;
        sem_post(&four);
    }
    sem_post(&control);
    printf("Thread ID: %ld, Team: %s, I have found a spot in a car\n",pthread_self(),team);

    pthread_barrier_wait(&barrier2);
    sem_wait(&final);
    if(driver)
    {
        driver = false;
        printf("Thread ID: %ld, Team: %s, I am the captain and driving the car\n",pthread_self(),team);
    }
    sem_post(&final);
    
    sem_wait(&release);
    if(groupcount >0)
    {
        groupcount--;
        sem_post(&group);
    }
    sem_post(&release);
    
}
int main(int argc, char*argv[])
{
    int fan1, fan2;
    fan1 = atoi(argv[1]);
    fan2 = atoi(argv[2]);
    int test = fan1 + fan2;
    if ((fan1 % 2 == 0 || fan2 % 2 == 0) && test % 4 == 0)
    {
        sem_init(&group ,0, 1);
        sem_init(&control ,0, 1);
        sem_init(&four ,0, 0);
        sem_init(&pair ,0, 1);
        sem_init(&final ,0, 1);
        sem_init(&release ,0, 1);
        sem_init(&wait ,0, 0);
        pthread_barrier_init(&barrier1, NULL, 4);
        pthread_barrier_init(&barrier2, NULL, 4);
         pthread_barrier_init(&barrier3, NULL, 4);
         pthread_barrier_init(&barrier4, NULL, 5);
        pthread_t fan_list[test];
        int * a = malloc(sizeof(int));
        *a = 1;
         int * b = malloc(sizeof(int));
        *b = 2;
        for (int i = 0; i < test; i++)
        {
            if(i < fan1)
            {
                pthread_create(&fan_list[i], NULL, &routine, a);
            }
            else
            {
                pthread_create(&fan_list[i], NULL, &routine, b);
            }      
        }
        for (int i = 0; i < test; i++)
        {
            pthread_join(fan_list[i], NULL);
        }
        printf("main terminates\n");
    }
    else
    {
        printf("main terminates\n");
    }

}
