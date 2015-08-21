#include <iostream>
#include <locale>

int main(){
	const int maxlength{ 100 };
	char text[maxlength] {};

	std::cout << "Enter a line of text:" << std::endl;

	std::cin.getline(text, maxlength);
	std::cout << "You entered:\n" << text << std::endl;
	size_t vowels {};
	size_t consonants {};

	for (int i {}; text[i] != '\0'; i++)
	{
		if (isalpha(text[i]))
		{
			switch (tolower(text[i]))
			{
			case 'a': case 'e': case 'i': case 'o': case 'u':
				vowels++;
				break;
			default:
				consonants++;
			}
		}
	}
	std::cout << " Your input constained " << vowels << " vowels and " << consonants << " consonants." << std::endl;
}