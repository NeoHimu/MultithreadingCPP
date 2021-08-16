#include<iostream>

using namespace std;

class A
{
	public:
		void f(int x, char c) { }
		long g(double x) { return 0; }
		int operator() (int N) { return 0; } // functor
};


int main()
{
	A a;
//	Four ways to callable object => 'a' is callable object, 6 is parameter passed to the callable object
//	std::thread t1(a, 6);
//	std::async(std::launch::asyc, a, 6);
//	std::bind(a, 6);
//	std::call_once(once_flag, a, 6);

	std::thread t1(a, 6);// copy_of_a() in a different thread
	std::thread t2(std::ref(a), 6)// a() in a different thread
	std::thread t3(std::move(a), 6); // a is no longer used in main thread
	std::thread t4(A(), 6); // temp A
	std::thread t5([](int x){ return x*x; }, 6); // lambda fun
	std::thread t6(foo, 7);
	
	std::thread t7(&A::f, a , 8, 'w'); // copy_of_a.f(8, 'w') in a different thread
	std::thread t8(&A::f, &a, 8, 'w'); // a.f(8, 'w') in a different thread
	
	
	return 0;
}

// https://www.youtube.com/watch?v=nU18p75u1oQ
