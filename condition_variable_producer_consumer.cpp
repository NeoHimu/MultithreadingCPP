#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <deque>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

/*
Producer
1. apply lock
2. write on buffer
3. unlock
4. notify one or more threads waiting on the condition variable
5. sleep for sometime (artifical delay)

Consumer
1. apply lock
2. wait on the condition variable
3. pop the data from buffer
4. unlock 
5. print the data
*/

void producer()
{
	int count=10;
	while(count>0)
	{
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		cond.notify_one(); // Notify one waiting thread, if there is one
		//cond.notify_all(); // Notify all the threads waiting on this cond variable
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1 sec
		count -= 1;
	}
}

void consumer()
{
	while(true)
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){return !q.empty();});// spurious wake: thread wakes by itself without meeting the condition => lambda function is used to rechek if it spurious wake
		int data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout<<"t2 got a value from t1 "<<data<<std::endl;
	}
}

int main()
{
	std::thread t1(producer);
	
	consumer();
	
	t1.join();
	
	return 0;
}

//https://www.youtube.com/watch?v=13dFggo4t_I&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=6
