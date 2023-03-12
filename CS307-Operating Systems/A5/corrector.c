#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>

void correct(const char* pathname);
void findDirectory(const char* dirname) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    //printf("Reading files in: %s\n", dirname);

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {

        char path[100] = { 0 };
        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, entity->d_name);
        const char * t = &path[strlen(path)-4];
        if(strcmp(t,".txt") == 0 && strcmp(path, "./database.txt") != 0)
        {
            correct(path);
        }

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            findDirectory(path);
        }
        entity = readdir(dir);
    }

    closedir(dir);
}
typedef struct Data {
    char gender[20];
    char name [30];
    char  lastname[30];
}Data;

Data datas[100];
int n;
void correct(const char* pathname)
{
    FILE * fptr;
    char  test[1000];
    fptr = fopen(pathname, "r+");
    while(fscanf(fptr,"%1000s", test)== 1)
    {
        int index = -1;
        for(int i = 0; i < n; i++)
        {
            if(strcmp(test,datas[i].name) == 0)
            {
                index = i;
            }
        }   
        if(index != -1)
        {
            int back =0;
            int forward=0;
            back-= strlen(test)+4;
            fseek(fptr,back, SEEK_CUR);
            if(strcmp(datas[index].gender, "m") == 0)  //if male
            {
                fputs("Mr.",fptr);
            }
            else
            {
                fputs("Ms.",fptr);
            }        
            forward += strlen(test) +2;    //move cursor to begining of the lastname
            fseek(fptr,forward, SEEK_CUR);
            fputs(datas[index].lastname,fptr);  //change it with the correct one
        }
    }
}
int main(int argc, char* argv[]) 
{
    FILE * file = fopen("database.txt", "r");
    if(file == NULL)
    {
         return 1;
    }
    char buffer[200];
    fgets(buffer, 200, file);

   
    int i = 0;
    while(!feof(file))
    {
        Data * d = datas + i;
        sscanf(buffer, "%s %s %s",d->gender, d->name, d->lastname );
        fgets(buffer, 200, file);
        i++;
    }
    n = i;
    fclose(file);

   findDirectory(".");
    return 0;
    
}
