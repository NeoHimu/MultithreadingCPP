#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

class LogFile{
	std::mutex mu;
	ofstream _f;
	public:
		LogFile(){
			_f.open("log.txt");
		}// need destructor to close file
		
		void shared_print(string id, int value){
			// unique_lock is similar to lock_guard in the sense that after scope is finished, it unlocks by default.
			std::unique_lock<std::mutex> locker(mu, std::defer_lock); // defer_lock: will lock later => without defer_lock, it is same as lock_guard
			// do something else
			
			locker.lock();  // lock and unlock can be used multiple times
			_f<<"from "<<id<<": "<<value<<endl;
			locker.unlock();
			
			//...
			
			locker.lock();
			//...
			locker.unlock();
			
			// can not use move() for lock_guard()
			std::unique_lock<std::mutex> locker2 = std::move(locker);
		}
};

//Another example of opening a file.. but different threads would like to open the file at once.. to handle this problem, there is an inbuilt fn
std::once_flag flag;
std::call_once(flag, [&](){f.open("log.txt")}); // this lambda function will take care of opening the file.. only one thread will open it


int main()
{
	
	return 0;
}
//https://www.youtube.com/watch?v=IBu5ka1MQ7w&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=5
