#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
std::shared_ptr<vector<string>> find_words(const string& str, const string& separators);
void list_words(const std::shared_ptr<vector<string>> pWords);
double average(double array[], size_t count); // Function prototype
double averageA(const double* array, size_t count);
double yield(const double values[][4], size_t n);

using Words = vector<string>; // Type for a vector of words
using PWords = std::shared_ptr<Words>; // Type for a smart point to a Words object

int main()
{
	double values[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	std::cout << "Average = " << average(values, (sizeof values) / (sizeof values[0])) << std::endl;
	std::cout << "AverageA = " << averageA(values, (sizeof values) / (sizeof values[0])) << std::endl;
	double beans[3][4] {
		{ 1.0, 2.0, 3.0, 4.0},
		{ 5.0, 6.0, 7.0, 8.0 },
		{ 9.0, 10.0, 11.0, 12.0 }
	};
	std::cout << "Yield = " << yield(beans, sizeof(beans) / sizeof(beans[0]))
		<< std::endl;
	string text; // The string to be searched
	std::cout << "Enter some text terminated by *:\n";
	std::getline(std::cin, text, '*');
	const string separators{ " ,;:.\"!?'\n" }; // Word delimiters
	
	list_words(find_words(text, separators));

}

// Function to compute an average
double average(double array[], size_t count)
{
	double sum{}; // Accumulate total in here
	for (size_t i{}; i < count; ++i)
		sum += array[i]; // Sum array elements
	return sum / count; // Return average
}

double averageA(const double* array, size_t count)
{
	double sum{}; // Accumulate total in here
	for (size_t i{}; i < count; ++i)
		sum += *array++; // Sum array elements
	return sum / count; // Return average
}
// Function to compute total yield
double yield(const double array[][4], size_t size)
{
	double sum{};
	for (size_t i{}; i < size; ++i) // Loop through rows
	{
		for (size_t j{}; j < 4; ++j) // Loop through elements in a row
		{
			sum += array[i][j];
		}
	}
	return sum;
}
PWords find_words(const string& str, const string& separators)
{
	auto pWords = std::make_shared<Words>(); // Vector of words
	size_t start{ str.find_first_not_of(separators) }; // First word start index
	size_t end{}; // Index for end of a word
	while (start != string::npos) // Find the words
	{
		end = str.find_first_of(separators, start + 1); // Find end of word
		if (end == string::npos) // Found a separator?
			end = str.length(); // No, so set to last + 1
		pWords->push_back(str.substr(start, end - start)); // Store the word
		start = str.find_first_not_of(separators, end + 1); // Find 1st character of next word
	}
	return pWords;
}


void list_words(const PWords pWords)
{
	std::cout << "Your string contains the following " << pWords->size() << " words:\n";
	size_t count{}; // Number output
	for (const auto& word : *pWords)
	{
		std::cout << std::setw(15) << word;
		if (!(++count % 5))
			std::cout << std::endl;
	}
	std::cout << std::endl;
}