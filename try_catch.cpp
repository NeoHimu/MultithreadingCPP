#include<iostream>
#include<thread>

using namespace std;

void function_1()
{
	std::cout<<"Beauty is only skin-deep"<<std::endl;
}

int main()
{
	std::thread t1(function_1); //the program will crash is no join or detach is used and the main thread finishes the execution before the child thread
	
	// we can use try-catch to catch the exception and join the thread
	try
	{
		for(int i=0;i<10;i++)
		{
			std::cout<<i<<std::endl;
		}
	}
	catch(...)
	{
		t1.join();  // this will make sure that the thread join in case of exception
		throw; // someone else will catch it
	}
	
	t1.join();
	
	return 0;
}

//https://www.youtube.com/watch?v=f2nMqNj7vxE&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=2
