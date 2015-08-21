
#include <iostream>
#include <iomanip>

int main()//make more thread calc
{
	const size_t max{ 10000 };
	long primes[max] {2L, 3L, 5L};
	size_t count{ 3 };
	long trial{ 5 };
	bool isprime{ true };

	do{
		trial += 2;
		size_t i{};
		do
		{
			isprime = trial% *(primes + i) > 0;


		} while (++i < count && isprime);

		if(isprime)
		{
			*(primes + count++) = trial;
		}
	} while (count < max);

	std::cout << " The first " << max << " primes are:" << std::endl;

	for (size_t i{}; i < max; ++i)
	{
		std::cout << std::setw(8) << *(primes + i);
		if ((i + 1) % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}