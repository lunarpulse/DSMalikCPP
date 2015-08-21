#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <climits>

using std::string;
using PWord = std::shared_ptr<string>;
using PWords = std::vector<PWord>;
void swap(PWords& pwords, size_t first, size_t second);
void sort(PWords& pwords, size_t start, size_t end);
void extract_words(PWords& pwords, const string& text, const string& separators);
void show_words(const PWords& pwords);
size_t max_word_length(const PWords& pwords);

template <typename T> void extractNumbers(std::vector<std::shared_ptr<T>>& numericalVector, const string& text, const string& separators);
template <typename T> void showNumbers(std::vector<std::shared_ptr<T>>& numericalVector);
template <typename T, size_t start, size_t end> void numberSort(std::vector<std::shared_ptr<T>>& numericalVector);
template <typename T, typename N> void numberSort(std::vector<std::shared_ptr<T>>& numericalVector, N  start, N end);
template <class T> int numDigits(T number);
template <> int numDigits(int32_t x);
template <> int numDigits(char n);
template <class T> size_t max_digit(const std::vector<std::shared_ptr<T>>& numericalVector);

int main()
{
	PWords pwords;
	string text; // The string to be sorted
	const string separators{ " ,.!?\"\n" }; // Word delimiters
	// Read the string to be searched from the keyboard
	std::cout << "Enter a string terminated by *:" << std::endl;
	getline(std::cin, text, '*');
	extract_words(pwords, text, separators);
	if (pwords.size() == 0)
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}
	sort(pwords, 0, pwords.size() - 1); // Sort the words
	show_words(pwords); // Output the words

	std::vector<std::shared_ptr<double>> numberVector;
	const string numSeparators{ " ,!?\"\n" }; // Word delimiters

	string text1; // The string to be sorted
	// Read the string to be searched from the keyboard
	std::cout << "Enter a string terminated by *:" << std::endl;
	getline(std::cin, text, '*');
	extractNumbers(numberVector, text, numSeparators);
	if (numberVector.size() == 0)
	{
		std::cout << "No words in text." << std::endl;
		return 0;
	}
	numberSort(numberVector, 0u, numberVector.size() - 1); // Sort the words
	showNumbers(numberVector); // Output the words
}


void extract_words(PWords& pwords, const string& text, const string& separators)
{
	size_t start{ text.find_first_not_of(separators) }; // Start 1st word
	size_t end{}; // Index for the end of a word
	while (start != string::npos)
	{
		end = text.find_first_of(separators, start + 1); // Find end separator
		if (end == string::npos) // End of text?
			end = text.length(); // Yes, so set to last+1
		pwords.push_back(std::make_shared<string>(text.substr(start, end - start)));
		start = text.find_first_not_of(separators, end + 1); // Find next word
	}
}

template <typename T> void extractNumbers(std::vector<std::shared_ptr<T>>& numericalVector, const string& text, const string& separators)
{
	size_t start{ text.find_first_not_of(separators) }; // Start 1st word
	size_t end{}; // Index for the end of a word
	while (start != string::npos)
	{
		end = text.find_first_of(separators, start + 1); // Find end separator
		if (end == string::npos) // End of text?
			end = text.length(); // Yes, so set to last+1
		numericalVector.emplace_back(std::make_shared<T>(std::stod(text.substr(start, end - start))));
		start = text.find_first_not_of(separators, end + 1); // Find next word
	}
}


void swap(PWords& pwords, size_t first, size_t second)
{
	PWord temp{ pwords[first] };
	pwords[first] = pwords[second];
	pwords[second] = temp;
}

template <typename T> void swap(std::vector<std::shared_ptr<T>>& numericalVector, size_t  first, size_t second)
{
	//using PWord = std::shared_ptr<string>;
	//using PWords = std::vector<PWord>;
	std::shared_ptr<T> temp{ numericalVector[first] };
	numericalVector[first] = numericalVector[second];
	numericalVector[second] = temp;
}

template <typename T, size_t start, size_t end> void numberSort(std::vector<std::shared_ptr<T>>& numericalVector)
{
	// start index must be less than end index for 2 or more elements
	if (!(start < end))
		return;
	// Choose middle address to partition set
	swap(numericalVector, start, (start + end) / 2); // Swap middle address with start
	// Check words against chosen word
	size_t current{ start };
	for (size_t i{ start + 1 }; i <= end; i++)
	{
		if (*(numericalVector[i]) < *(numericalVector[start])) // Is word less than chosen word?
			swap(numericalVector, ++current, i); // Yes, so swap to the left
	}
	swap(numericalVector, start, current); // Swap the chosen word with last in
	if (current > start) sort(numericalVector, start, current - 1); // Sort left subset if exists
	if (end > current + 1) sort(numericalVector, current + 1, end); // Sort right subset if exists
}

template <typename T, typename N> void numberSort(std::vector<std::shared_ptr<T>>& numericalVector, N  start, N end)
{
	// start index must be less than end index for 2 or more elements
	if (!(start < end))
		return;
	// Choose middle address to partition set
	swap(numericalVector, start, (start + end) / 2); // Swap middle address with start
	// Check words against chosen word
	size_t current{ start };
	for (size_t i{ start + 1 }; i <= end; i++)
	{
		if (*numericalVector[i] < *numericalVector[start]) // Is word less than chosen word?
			swap(numericalVector, ++current, i); // Yes, so swap to the left
	}
	swap(numericalVector, start, current); // Swap the chosen word with last in
	if (current > start) numberSort(numericalVector, start, current - 1); // Sort left subset if exists
	if (end > current + 1) numberSort(numericalVector, current + 1, end); // Sort right subset if exists
}

void sort(PWords& pwords, size_t start, size_t end)
{
	// start index must be less than end index for 2 or more elements
	if (!(start < end))
		return;
	// Choose middle address to partition set
	swap(pwords, start, (start + end) / 2); // Swap middle address with start
	// Check words against chosen word
	size_t current{ start };
	for (size_t i{ start + 1 }; i <= end; i++)
	{
		if (*(pwords[i]) < *(pwords[start])) // Is word less than chosen word?
			swap(pwords, ++current, i); // Yes, so swap to the left
	}
	swap(pwords, start, current); // Swap the chosen word with last in
	if (current > start) sort(pwords, start, current - 1); // Sort left subset if exists
	if (end > current + 1) sort(pwords, current + 1, end); // Sort right subset if exists
}

size_t max_word_length(const PWords& pwords)
{
	size_t max{};
	for (auto& pword : pwords)
		if (max < pword->length()) max = pword->length();
	return max;
}
template <class T> size_t max_digit(const std::vector<std::shared_ptr<T>>& numericalVector)
{
	size_t max{};
	for (auto& number : numericalVector)
		if (max < numDigits(*number.get())) max = numDigits(*number.get());
	return max;
}

template <class T>
int numDigits(T number)
{
	int digits = 0;
	if (number < 0) digits = 1; // remove this line if '-' counts as a digit
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

// partial specialization optimization for 32-bit numbers
template<>
int numDigits(int32_t x)
{
	if (x == INT_MIN) return 10 + 1;
	if (x < 0) return numDigits(-x) + 1;

	if (x >= 10000) {
		if (x >= 10000000) {
			if (x >= 100000000) {
				if (x >= 1000000000)
					return 10;
				return 9;
			}
			return 8;
		}
		if (x >= 100000) {
			if (x >= 1000000)
				return 7;
			return 6;
		}
		return 5;
	}
	if (x >= 100) {
		if (x >= 1000)
			return 4;
		return 3;
	}
	if (x >= 10)
		return 2;
	return 1;
}

// partial-specialization optimization for 8-bit numbers
template <>
int numDigits(char n)
{
	// if you have the time, replace this with a static initialization to avoid
	// the initial overhead & unnecessary branch
	static char x[256] = { 0 };
	if (x[0] == 0) {
		for (char c = 1; c != 0; c++)
			x[c] = numDigits((int32_t)c);
		x[0] = 1;
	}
	return x[n];
}
void show_words(const PWords& pwords)
{
	std::cout << std::endl;
	std::cout <<"The input is consist of a sorted set of words below"<< std::endl;
	const size_t field_width{ max_word_length(pwords) + 2 };
	const size_t words_per_line{ 8 }; // Word_per_line
	std::cout << std::left << std::setw(field_width) << *pwords[0]; // Output the first word
	size_t words_in_line{}; // Words in current line
	for (size_t i{ 1 }; i < pwords.size(); ++i)
	{ // Output - words newline when initial letter changes or after 10 per line
		if ((*pwords[i])[0] != (*pwords[i - 1])[0] || ++words_in_line == words_per_line)
		{
			words_in_line = 0;
			std::cout << std::endl;
		}
		std::cout << std::setw(field_width) << *pwords[i]; // Output a word
	}
	std::cout << std::endl;
}


template <typename T> void showNumbers(std::vector<std::shared_ptr<T>>& numericalVector)
{
	std::cout << std::endl;
	std::cout << "The input is consist of a sorted set of numerical values below" << std::endl;
	const size_t field_width{ max_digit(numericalVector) + 2 };
	const size_t words_per_line{ 20 }; // Word_per_line
	std::cout << std::left << std::setw(field_width) << *numericalVector[0]; // Output the first word
	size_t words_in_line{}; // Words in current line
	for (size_t i{ 1 }; i < numericalVector.size(); ++i)
	{ // Output - words newline when initial letter changes or after 10 per line
		if (numericalVector[i] != numericalVector[i - 1] || ++words_in_line == words_per_line)
		{
			words_in_line = 0;
			std::cout << std::endl;
		}
		std::cout << std::setw(field_width) << *numericalVector[i]; // Output a word
	}
	std::cout << std::endl;
}