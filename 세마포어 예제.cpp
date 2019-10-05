// reference : https://austingwalters.com/multithreading-semaphores
// 그냥 mtx.lock, mtx.unlock 으로 구현...
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

mutex mtx;

bool ready = false;
int balance = 0;

void depo(int cnt) {
	mtx.lock();
	balance += 1000;
	cout << cnt << " 번째 1000원 입금, 잔액 : " << balance << endl;
	ready = true;
	mtx.unlock();
}

void draw(int cnt) {
	mtx.lock();
	if (balance >= 1000) {
		balance -= 1000;
		cout << cnt << " 번째 1000원 출금, 잔액 : " << balance << endl;
	}
	else cout << cnt << " 잔액이 없습니다.\n";
	mtx.unlock();
}

int main() {
	thread threads[20];
	for (int id = 0; id < 20; id++) {
		if (id < 10) threads[id] = thread(depo, id);
		else threads[id] = thread(draw, id);
	}

	for (int id = 0; id < 20; id++)	threads[id].join();
	cout << "잔액 : " << balance << endl;
}
