#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

using MyArray = std::array<uint32_t, 9>;
using MyVector = std::vector<MyArray::value_type>;
void PrintArray(MyArray myArray, const std::function<void(MyArray::value_type)>& myFunction)
{
	//MyArray myArray{ 1, 2, 3, 4, 5 };
	std::for_each(myArray.begin(),
		myArray.end(),
		myFunction);
}
int main()
{

	auto startTimePoint = system_clock::now();

	MyArray myArray{ 1, 2, 3, 4, 5, 7, 8, 9, 10 };
	MyVector myCopy;
	auto myClosure = [&myCopy](auto&& number) {
		std::cout << number << std::endl;
		myCopy.push_back(number); //copy all the back up copy
	};
	auto myClosure0 =
		[](auto&& number){
		std::cout << number << std::endl;
	};

	std::cout << typeid(myClosure).name() << std::endl;
	PrintArray(myArray, myClosure);
	std::cout << std::endl << "My Copy: " << std::endl;
	std::for_each(myCopy.cbegin(),
		myCopy.cend(), myClosure0);

	std::string stringTest{ "111kni", 2 };
	string sleeping{ 6, 'z' };


	auto endTimePoint = system_clock::now();
	auto timeTaken = duration_cast<microseconds>(endTimePoint - startTimePoint);
	cout << "Time Taken: " << timeTaken.count() << endl;
	return 0;

	return 0;
}