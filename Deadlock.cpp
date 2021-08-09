#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

std::mutex mu1;
std::mutex mu2;

/**
Avoiding deadlock
1. Prefer locking single mutex
2. Avoid locking a mutex and then calling a user provided funciton => user function might have already applied some locks => deadlock
3. use std:lock() to lock more than one mutex
4. lock the mutex in the same order everywhere

Locking Granularity
- Fine-grained lock: protects small amount of data
- Coarse-grained lock: protects big amount of data
**/

void shared_print_1(string msg, int id)
{	
	std::lock(mu1, mu2); // this applies both the locks simultanueosly
	std::lock_guard <std::mutex> guard_1(mu1, std::adopt_lock); // adopt_lock says that if a lock is already applies, I'll adopt it and release when goes out of scope
	std::lock_guard<std::mutex> guard_2(mu2, std::adopt_lock);
	cout<<msg<<" "<<id<<endl;
}

void shared_print_2(string msg, int id)
{
	std::lock(mu1, mu2);
	std::lock_guard <std::mutex> guard_1(mu1, std::adopt_lock);
	std::lock_guard <std::mutex> guard_2(mu2, std::adopt_lock);
	cout<<msg<<" "<<id<<endl;
}

void function_1(string msg)
{
	for(int i=0;i<100;i++)
	{
		shared_print_1(msg, i);
	}
}

void function_2(string msg)
{
	for(int i=0;i<100;i++)
	{
		shared_print_2(msg, i);
	}
}

int main()
{
	std::thread t1(function_1, "child thread");
	
	// main thread
	function_2("main thread");
	
	t1.join();
	
	return 0;
}
//https://www.youtube.com/watch?v=_N0B5ua7oN8&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=4
