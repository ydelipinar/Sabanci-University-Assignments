#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int turn = 0;


bool check_diagonals(char *** t, int n)
{
    bool test = true;
    char * prev ;
    for (int i = 0; i<n && test; i++)
    {
        if(i == 0)
        {
            prev = t[i][i];
        }
        else
        {
            if(prev == " " || t[i][i] != prev)
            {
                test = false;
            }
            prev = t[i][i];
        }
    }
    bool test1 = true;
    for (int i = 0; i<n && test1; i++)
    {
        if(i == 0)
        {
            prev = t[i][n-1];
        }
        else
        {
            if(prev == " " || t[i][n-1-i] != prev)
            {
                test1 = false;
            }
            prev = t[i][n-1-i];
        }
    }
    return test || test1;
}
bool check_rows(char *** t, int n)
{   
    char * prev;
    bool test = false;
    for (int i = 0; i<n && !test; i++)
    {
        bool test1 = true;
        for (int j = 0; j<n && test1; j++)
        {
            if(j == 0)
            {
                prev = t[i][j];
            }
            else
            {
                if(prev == " " || t[i][j] != prev)
                {
                    test1 = false;
                }
                prev = t[i][j];
             }  
        }
        test = test1;
    }
    return test;
}

bool check_columns(char *** t, int n)
{
    bool test = false;
    char * prev;
    for (int i = 0; i<n && !test; i++)
    {
        bool test1 = true;
        for (int j = 0; j<n && test1; j++)
        {
            if(j == 0)
            {
                prev = t[j][i];
            }
            else
            {
                if(prev == " " || t[j][i] != prev)
                {
                    test1 = false;
                }
                prev = t[j][i];
             }  
        }
        test = test1;
    }
    return test;
}
bool check_win(char *** t, int n)
{
    bool test = check_diagonals(t, n);
    return test || (check_columns(t,n) || check_rows(t, n));
}
struct thread_args
{
    int size;
    char * mark;
    char *** matrix;
};

void * insert(void * arg)
{
    struct thread_args * args = (struct thread_args*) arg;

    int n = args->size;
    while (turn <n*n && !check_win(args->matrix, n))
    {
	int row = rand() % n;
	int column = rand() % n;
	
	pthread_mutex_lock(&lock);
	while(args->mark =="0" && turn % 2 == 0)
        {
           //printf("0 is wating\n");
           pthread_cond_wait(&cond1, &lock);
        }
	while(args->mark =="x" && turn % 2 == 1)
        {
            //printf("X is wating\n");
            pthread_cond_wait(&cond1, &lock);
	}
	if (turn <n*n && !check_win(args->matrix, n))
	{
	    while (args->matrix[row][column] != " ")
	    {
                 row = rand() % n;
	         column = rand() % n;
	    }
    	    //if(args->mark =="x" && args->turn%2 = 0)
    	    //printf("Thread id: %ld| Arguments: %s\n", pthread_self(), args->mark);
           args->matrix[row][column] = args->mark;
           printf("Player %s played on: (%d,%d)\n", args->mark, row,column);
           turn++;
          // printf("%s: is done\n",args->mark);
           pthread_mutex_unlock(&lock);
           pthread_cond_signal(&cond1);
        }
   }
   
    
   return NULL;
}

int main(int args, char *argv[])
{
    char *** matrix;
    srand(time(NULL));
    int n;
 
    n = atoi(argv[1]);
    
    printf("Board size: %dx%d\n",n,n);
    matrix = (char ***) malloc(n * sizeof(char**));
    for(int i = 0; i< n; i++)
    {
       matrix[i] = (char **) malloc(n * sizeof(char *));
    }
    for (int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            matrix[i][j] = " ";
        }
     }
    
    pthread_t thread1, thread2;
    
    struct thread_args s1 = {n, "x", matrix};
    struct thread_args s2 = {n, "0", matrix};
    
    pthread_create(&thread1, NULL, insert, &s1);
    pthread_create(&thread2, NULL, insert, &s2);   
    
    	
    
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Game end\n");
    
    if(check_win(matrix,n))
    {
        if (turn % 2 == 1)
        {
            printf("Winner is x\n");
        }
        else
        {
            printf("Winner is 0\n");
        }
    }
    else 
    {
    	printf("It is a tie\n");
    }
    
    for(int y = 0; y<n; y++)
    {
	for(int x =0; x<n ; x++)
	{
    	    printf("[%s]",matrix[y][x]);
    	}
    	printf("\n");
    }
    return 0; 
}
