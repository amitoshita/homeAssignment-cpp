// Question 5
//
	//we want to implement a logic class named MyBool to use in our logic
	//we would like to be able to use the logical and (&&) with instances of this class 
 // i.e. to be able to write in the form of myBool1 && myBool2
	//we have also implemented some function using this class
	//"notNull" checks if a pointer is null and return a corresponding MyBool
 // "greaterThanZero" checks if an int pointer points to a positive int and return a corresponding MyBool

	//1. Implement this addition in the MyBool class
	// 2. Did it compile successfully?
	// answer: Yes.
	//3. Did it run successfully?
	// answer: No. 
	// I should have added a check in the "greater than zero" function if the pointer is not nullptr.
	//4. Explain the result, explain what happened and why
	// Explanation:
	// When one of the "notNull" and "greaterThanZero" functions was called, in line 65 and line 72, temporary objects of type myBool were created. 
	// They used the myBool constructor which received the boolean value of m_val from each of the conditions in the functions.
	//The && operator that I implemented received the 2 objects of type myBool created in line 72 and line 65 and did a test on the boolean value m_val in each of the objects, 
	// and returned a value of type bool that was used to test in each of the lines.
//
// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading

#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {};

	bool operator&&(const MyBool& other) const {
		return m_val && other.m_val;
	}

private:
	bool m_val;
};

MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	if (intPtr != nullptr) {
		return *intPtr > 0;
	}
}

int main(int argc, char* argv[])
{
	int* a = nullptr;
	int val = 5;
	int* b = &val;


	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++* b;
		std::cout << "*b is " << *b << std::endl;
	}

	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	return 0;
}

