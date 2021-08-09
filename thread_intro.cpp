#include<iostream>
#include<thread>

using namespace std;

void function_1(){
	std::cout<<"Beauty is only skin-deep"<<std::endl;
}

int main()
{
	std::thread t1(function_1);   //t1 starts running
	//t1.join();  // main thread waits for the thread to finish
	t1.detach(); // t1 is free from main thread.. and it has become the daemon process => main thread is no longer connected to the child thread
    // in this particular program, main thread finishes execution faster than the child thread.. and hence no ouput will be printed
    
    
    // a thread can be joined or detached only once
    //t1.detach();  // this line will cause system error => crash
    
    //once a thread is detached it can not be joined again
    //t1.join(); // this will cause system error
    
    
    if(t1.joinable()) //check if the thread is joinable or not
    	t1.join();
    	
	return 0;
}
//https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=1
