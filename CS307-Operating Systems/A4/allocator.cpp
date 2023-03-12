#include <iostream>
#include<unistd.h>
#include <mutex>
using namespace std;

mutex mtx;
mutex mtx1;
mutex mtx2;


struct node
{
    int id;
    int size;
    int index;
    node * next;
    node * prev;
};
class HeapManager
{
private:
    node * head;

public:
    HeapManager(/* args */);
    int initHeap(int size);
    int myMalloc(int ID, int size);
    int myFree(int ID, int index);
    void print();
    ~HeapManager();
};

int HeapManager::initHeap(int size)
{
    head->size = size;
    head->index = 0;
    head->id = -1;
    head->next = NULL;
    head->prev =NULL;
    print();
    return 1;
}
int HeapManager::myMalloc(int ID, int size)
{
    mtx.lock();
    node * temp;
    temp = head;
    while(temp!= NULL)
    {
        if(temp->id != -1)
        {
            temp = temp->next;
        }
        else
        {
            if(temp->size >= size)
            {
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    if(temp == NULL)
    {
        cout<< "Can not allocate, requested size "<<size <<" for thread " << ID <<" is bigger than remaining size" << endl;
        print();
        mtx.unlock();
        return -1;
    }
    else
    {
        if(temp->size == size)
        {
            temp->id = ID;
            cout << "Allocated for thread " << ID << endl;
            print();
            mtx.unlock();
            return temp->index;
        }
        else
        {
            node * toAdd = new node;
            toAdd->size = size;
            toAdd->id = ID;
            toAdd->index = temp->index;
            temp->index = temp->index + size;
            temp->size = temp->size - size;
            if(temp->prev == NULL)
            {
                toAdd->next = temp;
                toAdd->prev = NULL;
                temp->prev = toAdd;
                head = toAdd;
                
            }
            else
            {
                toAdd->next = temp;
                toAdd->prev = temp->prev;
                temp->prev->next = toAdd;
                temp->prev = toAdd;
                
            }
            cout << "Allocated for thread " << ID << endl;
            print();
            mtx.unlock();
            return toAdd->index;
        }
    }
    
}
int HeapManager::myFree(int ID, int index)
{
    mtx1.lock();
    node * temp = head;

    while(temp!= NULL)
    {
        if(temp->id == ID && temp->index == index)
        {
            break;
        }
        else
        {
            temp =  temp->next;
        }
    }
    if(temp == NULL)
    {
        mtx1.unlock();
        return -1;
    }
    else
    {
        temp->id = -1;
        node * PrevT = temp;
        while(PrevT->prev != NULL && PrevT->prev->id == -1)
        {
            node * ptr = PrevT->prev; 
            PrevT->size = PrevT->size + ptr->size;
            PrevT->index = PrevT->index - ptr->size;
            if(ptr->prev !=NULL)
            {
                ptr->prev->next = PrevT;
                PrevT->prev = PrevT->prev->prev;
                delete ptr;
            }
            else
            {
                PrevT->prev = NULL;
                head = PrevT;
                delete ptr;
            }
            
        }
        while(PrevT->next != NULL && PrevT->next->id == -1)
        {
            node * ptr = PrevT->next; 
            PrevT->size = PrevT->size + ptr->size;
            if(ptr->next !=NULL)
            {
                ptr->next->prev = PrevT;
                PrevT->next = PrevT->next->next;
                delete ptr;
            }
            else
            {
                PrevT->next = NULL;
                delete ptr;
            }
            
        }
        cout << "Freed for thread " << ID << endl;
        print();
        mtx1.unlock();
        return 1;
    }
    

}
 void HeapManager::print()
{
    mtx2.lock();
    node * temp = head;
    int count = 0;
    while(temp != NULL)
    {
        if(count == 0)
        {
            cout << "[" << temp->id << "]"<< "[" << temp->size<<"]" << "[" << 
            temp->index << "]";
            count++;
        }
        else
        {
            cout <<"---"<<"[" << temp->id << "]"<< "[" << temp->size<<"]" << "[" << 
            temp->index << "]";
        }
        temp = temp->next;
    }
    cout << endl;
    mtx2.unlock();
}
HeapManager::HeapManager(/* args */)
{
    head = new node;
    head->next = NULL;
    head->prev = NULL;
}

HeapManager::~HeapManager()
{
    
}
