//Question 2 - threads & synchronization
//
//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 
//
// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

//I used std::thread class that represents a single thread in C++.
//I created 2  new thread objects and pass the executing code to be called (operation1 and operation2) into the constructor of the object.
//Once the object is created a new thread is launched which will execute the code specified in callable.
//I also used std::lock_guard<std::mutex> to avoid data races, and to lock shared data in threads.
//Some aspects to consider when using parllel execution:
//1.Data synchronization: when both threads trying to access shared data, it's important to ensure proper synchronization to avoid data races.
//2.Parallel execution can cause challenges in debugging due to the increased complexity of interactions between threads.
//3.If one thread is depend in other thread, it is important to enforce the correct order of execution.
//4.Handling load balancing- If one thread finishes its work earlier than others, it may result in idle threads and underutilization of system resources.
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>



constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

std::mutex myLock;
size_t gSum = 0;

void operation1(size_t arg) {
	std::lock_guard<std::mutex> lock(myLock);
	std::cout << "Performing operation1" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum += (arg + i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::lock_guard<std::mutex> lock(myLock);
	std::cout << "Performing operation2" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum += (arg * i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto startParllel = std::chrono::steady_clock::now();
	std::thread thread1(operation1, OP1_PARAM);
	std::thread thread2(operation2, OP2_PARAM);
	thread1.join();
	thread2.join();
	auto endParllel = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds using threads: " << std::chrono::duration_cast<std::chrono::milliseconds>(endParllel - startParllel).count() << std::endl;
	std::cout << "Result:  " << gSum << ", " << (gSum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;

	getchar();
	return 0;
}