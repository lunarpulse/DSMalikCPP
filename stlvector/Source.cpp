#include <iostream>
#include <iomanip>
#include <cctype>
#include <cinttypes>
#include <vector>

using namespace std;
int main(int argc, char* argv[])
{
	vector<int32_t> stlVector
	{
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
		10,
		11,
		12,
		13,
		14,
		15,
		16
	};
	cout << "The size is: " << stlVector.size() << endl;
	cout << "The capacity is: " << stlVector.capacity() << endl << endl;
	for (auto&& number : stlVector)
	{
		std::cout << number << ", ";
	}

	stlVector.emplace_back(17);

	unsigned int count{ 0 };
	unsigned int shrink{ 0 };
	while (stlVector.size() > 0)
	{
		count++;
		auto iterator = stlVector.end() - 1;
		stlVector.erase(iterator);

		if ((stlVector.size() * 2) == stlVector.capacity())
		{
			stlVector.shrink_to_fit();
			shrink++;
		}

		cout << "The size is: " << stlVector.size() << endl;
		cout << "The capacity is: " << stlVector.capacity() << endl << endl;
	}

	cout << endl << endl << "The number of element deletion is: " << count << endl;
	cout << endl << endl << "The number of element shrink is: " << shrink << endl;

	cout << endl << endl << "The size is: " << stlVector.size() << endl;
	cout << "The capacity is: " << stlVector.capacity() << endl << endl;
	for (auto&& number : stlVector)
	{
		std::cout << number << ", ";
	}
	std::cout << std::endl;
	return 0;
}