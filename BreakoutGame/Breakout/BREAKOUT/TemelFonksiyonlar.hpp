#pragma once
#include <random>

namespace TemelFonksiyonlar
{
	static int getRandomNumber(int min, int max)
	{
		std::random_device seed;
		std::mt19937 randomNumberGenerator(seed());
		std::uniform_int_distribution<int> idist(min, max);
		return idist(randomNumberGenerator);
	}
}
