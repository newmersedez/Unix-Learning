#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>

std::mutex	mutex;

void func()
{
	mutex.lock();
	std::cout << "Start" << std::endl;
	sleep(2);
	std::cout << "End" << std::endl;
	mutex.unlock();
}

int main()
{
	std::thread	thread1(func);
	std::thread	thread2(func);

	thread1.join();
	sleep(1);
	thread2.join();
	return 0;
}