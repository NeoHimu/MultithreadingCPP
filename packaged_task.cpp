#include<iostream>

using namespace std;

int factorial(int N)
{
	int res=1;
	for(int i=1;i<=N;i++)
		res *= i;
	cout<<res<<endl;
	return res;
}

int main()
{
//	std::packaged_task<int(int)> t(factorial);
//	
//	//// .....
//	
//	t(6); // called in a different context i.e. may be in different function or class
//	
//	// how to get the returned value of the function.. packaged_task returns void
//	int x = t.get_future().get();
//	cout<<c<<endl;
//	

	std::thread t1(factorial, 6); // this additional paramter can't be passed in packaged_task,
	// we need to use bind function to bind the function parameters with the function
	std::packaged_task<int()> t(std::bind(factorial, 6)); // this bind function creates a new funcion object
	// but notice that the new binded function can not take any paramter now
	// so packaged_task should not be accepting any argument now
	// also while calling, no paramters should be passd
	t();
	// do we really need the packaged_task, we can do all these with bind()
	//e.g. auto t = std::bind(factorial, 6);
	
	// The main advantage of a packaged_task is that it can link a callable object with a future... 
	// and that is very important in a threading environment
	return 0;
}

// watch the video for more beautiful example
//https://www.youtube.com/watch?v=FfbZfBk-3rI
