// reference : https://austingwalters.com/multithreading-semaphores

#include <iostream>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

mutex mtx;             // mutex for critical section
condition_variable cv; // condition variable for critical section  
bool ready = false;         // Tell threads to run
int balance = 0; 
int num = 0;

void depo(int cnt) {
	unique_lock<mutex> lck(mtx);
	while (num != cnt || !ready) cv.wait(lck);
	num++;
	balance += 1000;
	cout << cnt << " 번째 1000원 입금\n";
	cv.notify_all();
}

void draw(int cnt) {
	unique_lock<mutex> lck(mtx);
	while (num != cnt || !ready) cv.wait(lck);
	num++;
	if (balance >= 1000) {
		balance -= 1000;
		cout << cnt << " 번째 1000원 출금\n";
	}
	else {
		cout << cnt << " 잔액이 없습니다.\n";
	}
	cv.notify_all();
}

void run() {
	unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

int main() {

	int threadnum = 20;
	std::thread threads[20];

	for (int id = 0; id < threadnum; id++) {
		if(id < 8) threads[id] = thread(depo, id);
		else threads[id] = thread(draw, id);
	}

	run();

	for (int id = 0; id < threadnum; id++)
		threads[id].join();

	
	cout << balance << endl;
}
