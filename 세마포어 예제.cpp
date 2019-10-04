// reference : https://austingwalters.com/multithreading-semaphores
// 입출금 요청이 여러개 들어올 때, 입금-출금-입금-출금-... 순서로 Ordering
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
int value = 1;

void depo(int cnt) {
	unique_lock<mutex> lck(mtx);
	while (ready) cv.wait(lck);
	balance += 1000;
	cout << cnt << " 번째 1000원 입금, 잔액 : " << balance << endl;
	ready = true;
	cv.notify_all();
}

void draw(int cnt) {
	unique_lock<mutex> lck(mtx);
	while (!ready) cv.wait(lck);
	if (balance >= 1000) {
		balance -= 1000;
		cout << cnt << " 번째 1000원 출금, 잔액 : " << balance << endl;
	}
	else cout << cnt << " 잔액이 없습니다.\n";
	ready = false;
	cv.notify_all();
}

void run() {
	unique_lock<mutex> lck(mtx);
	ready = false;
	cv.notify_all();
}

int main() {

	int threadnum = 20;
	std::thread threads[20];

	for (int id = 0; id < threadnum; id++) {
		if (id < 10) threads[id] = thread(depo, id);
		else threads[id] = thread(draw, id);
	}

	run();

	for (int id = 0; id < threadnum; id++)
		threads[id].join();


	cout << "잔액 : " << balance << endl;
}
