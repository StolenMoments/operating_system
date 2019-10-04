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
int value = 1;

void depo(int cnt) {
	unique_lock<mutex> lck(mtx);
	balance += 1000;
	cout << cnt << " 번째 1000원 입금, 잔액 : " << balance << endl;
}

void draw(int cnt) {
	unique_lock<mutex> lck(mtx);
	if (balance >= 1000) {
		balance -= 1000;
		cout << cnt << " 번째 1000원 출금, 잔액 : " << balance << endl;
	}
	else cout << cnt << " 잔액이 없습니다.\n";
}

void run() {
	unique_lock<mutex> lck(mtx);
}

int main() {

	int threadnum = 20;
	std::thread threads[20];

	for (int id = 0; id < threadnum; id++) {
		if (id == 1 || id == 3 || id == 5 || (id >= 14 && id <= 17)) threads[id] = thread(depo, id);
		else threads[id] = thread(draw, id);
	}

	run();

	for (int id = 0; id < threadnum; id++)
		threads[id].join();


	cout << "잔액 : " << balance << endl;
}
