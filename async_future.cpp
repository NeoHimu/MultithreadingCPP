#include<iostream>
#include<future>
#include<chrono>

using namespace std;

int factorial(int n)
{
	int res=1;
	for(int i=1;i<=n;i++)
	{
		res *= i;
	}
	return res;
}

int factorial_parent_to_child(future<int>& fu)
{
	int n = fu.get(); // if the parent does not supply a value i.e. fu1.set_value(5) is not there then it'll cause broken_promise exception
	int res=1;
	for(int i=1;i<=n;i++)
		res *= i;
	
	return res;
}

int main()
{
	/* USE OF FUTURE TO PASS VALUES FROM CHILD THREAD TO PARENT THREAD */
	
//	future<int> fu = std::async(std::launch::deferred, factorial, 5); if launch::deferred parameter is passed then factorial function won't be
//executed till get() function is called. when the get() function is called then the execution happens in the same thread
//future<int> fu = std::async(std::launch::async, factorial, 5); => the execution of fu happens in a different thread
// the default value of the std::launch parameter is (std::launch::deferred | std::launch:async) => so if a new thread is created or not depends on
//the implementation
	future<int> fu = std::async(factorial, 5);
	int ans = fu.get(); // wait unitl the child thread finishes and then return the returned valur from the child thread
//	fu.get(); if get() is called again, it'll crash the program
	
	cout<<ans<<endl;
	
	
	/* USE OF FUTURE TO PASS VALUES FROM PARENT THREAD TO CHILD THREAD */
	std::promise<int> p;
	std::future<int> fu1 = p.get_future(); // promise is made that in future an int value would be supplied
	std::future<int> fu2 = std::async(factorial_parent_to_child, std::ref(fu1));
	
	// do something else
	std::this_thread::sleep_for(chrono::seconds(1));
	// if we are sure that we can not provide the value to the promise then we should add the following line:
	// p.set_exception(std::make_exception_ptr(std::runtime_error("To error is human!")));
	p.set_value(5); // here, the promise of passing an integer to the child is fulfilled
	
	cout<<fu2.get()<<endl; // this value is computed and passed by child to the parent thread
	
	
	// promise and future can only be moved using std::move() function.. they can never be copied.
	
	// what if we need to call the factorial function over 10 different threads => this would require passing the future to the 10 different threads.
//	We can not pass the same future to all the threads because in each thread, factorial function will be calling get() function. And get() function
//	can not be called more than once. Other method can be to use 10 different promises and 10 different corresponding futures. But that's clumsy.
//	standard library provides shared_future<int> which can be used by many different async() functions. It can be passed by value.

//	std::promise<int> p;
//	std::future<int> f = p.get_future();
//	std::shared_future<int> sf = f.share();
//	
//	pass this sf into all the async functions by value
// std::future<int> fu1 = std::async(factorial_parent_to_child, sf);
// std::future<int> fu2 = std::async(factorial_parent_to_child, sf);
// std::future<int> fu3 = std::async(factorial_parent_to_child, sf);
// .. 10 threads
	
	
	
	return 0;
}


// https://www.youtube.com/watch?v=SZQ6-pf-5Us
