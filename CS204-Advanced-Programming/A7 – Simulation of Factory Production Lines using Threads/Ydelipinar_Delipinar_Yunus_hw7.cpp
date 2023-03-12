
//created by Yunus Delipinar

#include <iostream>
#include "Ydelipinar_Delipinar_Yunus_hw7_DynIntQueue.h"
#include <mutex>
#include <chrono>
#include <random>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <thread>

using namespace std;

mutex Mutex1, Mutex2, coutMutex;
HW7DynIntQueue filling_Queue;
HW7DynIntQueue packaging_Queue;
int counter1 = 0;   //global variables to keep the count of the process
int counter2 = 0;

int random_range(const int & min, const int & max) 
{
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}
/* Begin: code taken and updated from producerConsumer.cpp */
void producer( const int size, int min, int max)   
{
	for(int i = 1; i < size+1; i++)
	{
		int time = random_range(min, max);    //time to sleep
		this_thread::sleep_for(chrono::seconds(time));
		Mutex1.lock();
		filling_Queue.enqueue(i);
		Mutex1.unlock();

		coutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		tm *ptm = new tm; 
		localtime_s(ptm, &tt); 
		cout <<"Producer has enqueued a new box "<< i << " to filling queue (filling queue size is "<< filling_Queue.getCurrentSize()<< "): "<< put_time(ptm,"%X") <<endl;
		coutMutex.unlock();
	}
}
/* End: code taken and updated from producerConsumer.cpp */

/* Begin: code taken and updated from producerConsumer.cpp */
void filler(int consId, int size, int min, int max)
{
	int item;
	while(counter1 < size)
	{	
		Mutex1.lock();
		if (!filling_Queue.isEmpty()) 
		{  
			
			filling_Queue.dequeue(item);
			counter1++;
			Mutex1.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Filler "<< consId <<" filling the box "<< item <<" (filling queue size is " << filling_Queue.getCurrentSize() << "): " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			int time = random_range(min, max);
			this_thread::sleep_for(chrono::seconds(time)); // simulation for filling

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Filler "<< consId <<"  finished filling the box "<< item <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			Mutex2.lock();
			packaging_Queue.enqueue(item);
			Mutex2.unlock();

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout<<"Filler "<< consId <<" put box "<< item <<" into packaging queue (packaging queue size is " << 
			packaging_Queue.getCurrentSize() << "): " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
		{
			Mutex1.unlock();
		}
	}
}
/* End: code taken and updated from producerConsumer.cpp */

/* Begin: code taken and updated from producerConsumer.cpp */
void packager(int consId, int size, int min, int max)
{
	int item;
	while(counter2 < size)
	{
		Mutex2.lock();
		if (!packaging_Queue.isEmpty()) 
		{  
			packaging_Queue.dequeue(item);
			counter2++;    //keep the count of process
			Mutex2.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Packager "<< consId <<" started packaging the box "<< item <<" (packaging queue size is " << packaging_Queue.getCurrentSize() << "): " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
			int time = random_range(min, max);
			this_thread::sleep_for(chrono::seconds(time)); // simulation for filling

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<<"Packager "<< consId <<" finished packaging the box "<< item <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else //unlock mutex to prevent crash
		{
			Mutex2.unlock();
		}
	}
}

/* End: code taken and updated from producerConsumer.cpp */
int main()
{
	int total_box_count, producer_min, producer_max, filler_min, filler_max, packager_min, packager_max;

	cout <<"Please enter the total number of items: ";
	cin >> total_box_count;
	cout << "Please enter the min-max waiting time range of producer:" << endl << "Min: ";
	cin >> producer_min;
	cout << "Max: ";
	cin >> producer_max;
	cout << "Please enter the min-max waiting time range of filler workers:" << endl << "Min: ";
	cin >> filler_min;
	cout << "Max: ";
	cin >> filler_max;
	cout << "Please enter the min-max waiting time range of packager workers:" << endl << "Min: ";
	cin >> packager_min;
	cout << "Max: ";
	cin >> packager_max;
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	 tm *ptm = new tm; 
	localtime_s(ptm, &tt); 

	cout << "Simulation starts " <<put_time(ptm,"%X") <<endl;

	thread thr0(producer, total_box_count, producer_min, producer_max);
	thread thr1(filler, 1, total_box_count, filler_min, filler_max);
	thread thr2(filler, 2, total_box_count, filler_min, filler_max);
	thread thr3(packager, 1, total_box_count, packager_min, packager_max);
	thread thr4(packager, 2, total_box_count, packager_min, packager_max);
	
	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 
	cout << "End of the simulation ends: " <<put_time(ptm,"%X") <<endl;
}