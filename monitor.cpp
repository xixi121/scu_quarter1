class my_monitor(){
private:
#include <unistd.h>
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
//Condition variable. Only when the slots are not all full, producer can pruduce more products.
std::condition_variable notfull;
//Condition Variable. Only when the slots are not all empty, consumer can consume more products.
std::condition_variable notempty;
int count=0;
//Set the total slots for products to 10.
int total_products=10; 
std::mutex mtx;
void producer(){
	while(1){
		//Set the lock to avoid corruption.
		std::unique_lock<std::mutex> my_lock(mtx); 
		while(count==total_products){
			cout<<"producer is waiting for an empty slot."<<endl;
			//When all slots are full, the producer stops producing and waits.
			notfull.wait(mylock); 
		}
		count++;
		cout<<"Product "<<count<<" is produced;"<<endl;
		//Notify consumer that he can consume.
		notempty.notify_all(); 
		//lock is released with RAII.
	}
}
void consumer(){
	while(1){
		std::unique_lock<std::mutex> mylock(mtx);
		while(count==0){
			cout<<"consumer is waiting for an available product."<<endl;
			//When all slots are empty, consumer stops cusuming and waits.
			notempty.wait(my_lock); 
		}
		cout<<"Product "<<count<<" is consumed;"<<endl;		
		count--;
		//Notify producer that he can produce.
		notfull.notify_all();
		//lock is released with RAII.
	}
}
public:
void RunMultiThreads(){
std::thread p(producer);
std::thread c(consumer);
p.join();
c.join();
}
};
int main(){
	my_monitor test;
	test.RunMultiThreads();
	return 0;
}
