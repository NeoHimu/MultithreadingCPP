#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

std::mutex mu;

//void shared_print(string msg, int id)
//{
//	mu.lock();   // but this will fail if the program between lock and unlock statement causes exception => lock will remain applied and hence deadlock
//	cout<<msg<<" "<<id<<endl;
//	mu.unlock();
//}

void shared_print(string msg, int id)
{
	std::lock_guard <std::mutex> guard(mu); //when the guard goes out of scope the mutex always unlocks with/without exception
	cout<<msg<<" "<<id<<endl;
	// this is still not under full protection because cout is a global variable and can be accessed by other functions without lock
}

void function_1(string msg)
{
	for(int i=0;i<100;i++)
	{
		shared_print(msg, i);
	}
}

int main()
{
	std::thread t1(function_1, "child thread");
	
	// main thread
	function_1("main thread");
	
	t1.join();
	
	return 0;
}
//https://www.youtube.com/watch?v=3ZxZPeXPaM4&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=3
