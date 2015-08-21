// Ex8_09.cpp
// Using multiple default parameter values
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <vector>

using std::string;
void show_data(const double data[], size_t count = 1, const string& title = "Data Values",
	size_t width = 10, size_t perLine = 5);
const double& largest(const double data[], size_t count);
const double* smallest(const double data[], size_t count);
double* shift_range(double data[], size_t count, double delta);
double* scale_range(double data[], size_t count, double divisor);
double* normalize_range(double data[], size_t count);
// The function prototype including defaults for parameters
void show_data(const int data[], size_t count = 1, const string& title = "Data Values",	size_t width = 10, size_t perLine = 5);
int* larger(int* a, int* b);
string& larger(string& s1, string& s2);
long next_Fibonacci();
double larger(double a, double b); // Non-reference parameters
long larger(const long& a, const  long& b); // lvalue reference parameters
template <typename T> T larger_t(T a, T b); // Function template prototype
template<> long* larger_t<long*>(long* a, long* b)
{
	std::cout << typeid(long*).name() << ": ";
	return *a > *b ? a : b; //the specialization would need to be placed after the prototype for the template, and before main().
}
template <typename T> T larger_t(const T data[], size_t count);
template <typename T> T larger_t(const std::vector<T>& data);
template <typename TReturn, typename TArg>
TReturn larger_t_mt(TArg a, TArg b);

int main()
{
	int samples[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int dataItem{ -99 };
	show_data(&dataItem);
	dataItem = 13;
	show_data(&dataItem, 1, "Lucky for some!");
	show_data(samples, sizeof(samples) / sizeof(samples[0]));
	show_data(samples, sizeof(samples) / sizeof(samples[0]), "Samples");
	show_data(samples, sizeof(samples) / sizeof(samples[0]), "Samples", 3);
	show_data(samples, sizeof(samples) / sizeof(samples[0]), "Samples", 8, 4);

	int value1{ 20 }, value2{ 30 };
	*larger(&value1, &value2) = 100;
	//auto less = [&value1, &value2](int a, int b){return a > b};
	std::cout <<value1 <<std::endl;
	std::cout << value2 << std::endl;
	string str1{ "abcx" };
	string str2{ "adcf" };
	larger(str1, str2) = "defg";
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
	double samplesD[] {
		11.0, 23.0, 13.0, 4.0,
			57.0, 36.0, 317.0, 88.0,
			9.0, 100.0, 121.0, 12.0
	};

	const size_t count{ sizeof(samplesD) / sizeof(samplesD[0]) }; // Number of samples
	show_data(samplesD, count, "Original Values"); // Output original values
	normalize_range(samplesD, count); // Normalize the values
	show_data(samplesD, count, "Normalized Values", 12); // Output normalized values
	size_t countp{};
	std::cout << "Enter the number of Fibonacci values to be generated: ";
	std::cin >> countp;
	std::cout << "The Fibonacci Series:\n";
	for (size_t i{}; i < countp; ++i)
	{
		std::cout << std::setw(10) << next_Fibonacci();
		if (!((i + 1) % 8)) // After every 8th output...
			std::cout << std::endl; // ...start a new line
	}
	std::cout << std::endl;

	double a_double{ 1.5 }, b_double{ 2.5 };
	std::cout << "The larger of double values "
		<< a_double << " and " << b_double << " is "
		<< typeid(larger(a_double, b_double)).name() << " " << larger(a_double, b_double) << std::endl;
	int a_int{ 15 }, b_int{ 25 };
	std::cout << "The larger of int values "
		<< a_int << " and " << b_int << " is "
		<< typeid(larger(static_cast<long>(a_int), static_cast<long>(b_int))).name() << " " << larger(static_cast<long>(a_int), static_cast<long>(b_int))
		<< std::endl;

	std::cout << "Larger of 1.5 and 2.5 is " << larger_t(1.5, 2.5) << std::endl;
	std::cout << "Larger of 3.5 and 4.5 is " << larger_t(3.5, 4.5) << std::endl;
	int a_int_T{ 35 }, b_int_T{ 45 };
	std::cout << "Larger of " << a_int_T << " and " << b_int_T << " is "
		<< larger_t(a_int_T, b_int_T) << std::endl;

	long a_long{ 9L }, b_long{ 18L };
	std::cout << "Larger of " << a_long << " and " << b_long << " is "
		<< larger_t(a_long, b_long) << std::endl;

	std::cout << "Larger of " << a_long << " and 9.5 is "
		<< larger_t<double>(a_long, 9.5) << std::endl;

	std::cout << "Larger of " << a_long << " and " << b_long << " is "
		<< *larger_t(&a_long, &b_long) << std::endl; // Outputs 8
	int a_int_T_O{ 35 }, b_int_O{ 45 };
	std::cout << "Larger of " << a_int_T_O << " and " << b_int_O << " is "
		<< larger_t(a_int_T_O, b_int_O) << std::endl;
	const char text[] {"A nod is as good as a wink to a blind horse."};
	std::cout << "Largest character in \"" << text << "\" is '"
		<< larger_t(text, sizeof(text)) << "'" << std::endl;
	std::vector<std::string> words{ "The", "higher", "the", "fewer" };
	std::cout << "The largest word in words is \"" << larger_t(words)
		<< "\"" << std::endl;
	std::vector<double> data{ -1.4, 7.3, -100.0, 54.1, 16.3 };
	std::cout << "The largest value in data is " << larger_t(data) << std::endl;

	std::cout << "Larger of 1.5 and 2.5 is " << larger_t_mt<int>(1.5, 2.5) << std::endl;
	std::cout << "Larger of 1.5 and 2.5 is " << larger_t_mt<double, double>(1.5, 2.5) << std::endl;
}
template <typename TReturn, typename TArg>
TReturn larger_t_mt(TArg a, TArg b)
{
	std::cout <<"return type" << typeid(TReturn).name() << ", arg type " << typeid(TArg).name() << ": ";
	return a > b ? a : b;
}
template <typename T>
T larger_t(const std::vector<T>& data)
{
	T result{ data[0] };
	for (auto& value : data)
		if (value > result) result = value;
	return result;
}

template <typename T>
T larger_t(const T data[], size_t count)
{
	T result{ data[0] };
	for (size_t i{ 1 }; i < count; ++i)
		if (data[i] > result) result = data[i];
	return result;
}
// Template for functions to return the larger of two values
template <typename T>
T larger_t(T a, T b)
{
	std::cout << typeid(T).name()<<": ";
	return a > b ? a : b;
}

// Returns the larger of two floating point values
double larger(double a, double b)
{
	std::cout << "double larger() called." << std::endl;
	return a > b ? a : b;
}
// Returns the larger of two long references
long larger(const long& a, const long& b)
{
	std::cout << "long ref larger() called" << std::endl;
	return a>b ? a : b;
}
// Generate the next number in the Fibonacci series
long next_Fibonacci()
{
	static long last; // Last number in sequence
	static long last_but_one{ 1L }; // Last but one in sequence
	long next{ last + last_but_one }; // Next is sum of the last two
	last_but_one = last; // Update last but one
	last = next; // Last is new one
	return last; // Return the new value
}
void show_data(const int data[], size_t count, const std::string& title, size_t width, size_t perLine)
{
	std::cout << title << std::endl; // Display the title
	// Output the data values
	for (size_t i{}; i < count; ++i)
	{
		std::cout << std::setw(width) << data[i]; // Display a data item
		if (!((i + 1) % perLine)) // Newline after perline values
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

int* larger(int* a, int* b)
{
	if (*a > *b)
		return a; // OK
	else
		return b; // OK
}
// Finds the largest of an array of double values
const double& largest(const double data[], size_t count)
{
	size_t index_max{};
	for (size_t i{ 1 }; i < count; ++i)
		if (data[index_max] < data[i])
			index_max = i;
	return data[index_max];
}
// Finds the smallest of an array of double values
const double* smallest(const double data[], size_t count)
{
	size_t index_min{};
	for (size_t i{ 1 }; i < count; ++i)
		if (data[index_min] > data[i])
			index_min = i;
	return &data[index_min];
}
// Modify a range of value by delta
double* shift_range(double data[], size_t count, double delta)
{
	for (size_t i{}; i < count; ++i)
		data[i] += delta;
	return data;
}
// Scale an array of values by divisor
double* scale_range(double data[], size_t count, double divisor)
{
	if (!divisor) return data; // Do nothing for a zero divisor
	for (size_t i{}; i < count; ++i)
		data[i] /= divisor;
	return data;
}
// Normalize an array of values to the range 0 to 1
double* normalize_range(double data[], size_t count)
{
	return scale_range(shift_range(data, count, -(*smallest(data, count))),
		count, largest(data, count));
}
// Outputs an array of double values
void show_data(const double data[], size_t count, const string& title, size_t width, size_t perLine)
{
	std::cout << title << std::endl; // Display the title
	// Output the data values
	for (size_t i{}; i < count; ++i)
	{
		std::cout << std::setw(width) << data[i]; // Display a data item
		if ((i + 1) % perLine == 0) // Newline after perline values
			std::cout << std::endl;
	}
	std::cout << std::endl;
}
string& larger(string& s1, string& s2)
{
	return s1 > s2 ? s1 : s2; // Return a reference to the larger string
}