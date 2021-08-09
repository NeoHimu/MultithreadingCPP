#include<iostream>
#include<thread>

using namespace std;

class FunctorClass
{
	public:
		void operator()(string& msg) //just putting the & won't be pass by reference => because thread always works pass-by-value
		{
			std::cout<<"from thread: "<<msg<<std::endl;
			msg = "hello";
		}
};

int main()
{
	cout<<std::thread::hardware_concurrency()<<endl; //optimal number of thread on should create on a system
	
	string msg="hello world!";
//	std::thread t1((FunctorClass()), std::ref(msg));  // ref() is used for pass-by-reference in thread
	std::thread t1((FunctorClass()), std::ref(msg)); // string is moved from main thread to child thread.. this might be required when 
	//main thread does not use the object 
	
	cout<<"main thread id: "<<std::this_thread::get_id()<<endl;  // main thread id
	cout<<"child process id: "<<t1.get_id()<<endl; // child thread id
	
	
	//also thread object can only be assigned through move() function
//	thread t2 = t1; // this won't work

	std::thread t2 = std::move(t1);
	
	t2.join();
//	std::cout<<msg<<endl;
	
	return 0;
}

//https://www.youtube.com/watch?v=f2nMqNj7vxE&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=2