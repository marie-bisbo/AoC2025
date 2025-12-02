#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int Power(long value, int power)
{
	int result = 1;

	while (power--)
	{
		result *= value;
	}

	return result;
}

int GetNumDigitsInNumber(unsigned long long number)
{
	int result = 0;
	while (number != 0)
	{
		number /= 10;
		++result;
	}

	return result;
}

void ResetArray(char* array, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = '\0';
	}
}

unsigned long long GetInvalidIds(unsigned long long rangeStart, unsigned long long rangeEnd)
{
	unsigned long long invalidIds = 0;
	for (unsigned long long i = rangeStart; i <= rangeEnd; i++)
	{
		// printf("i: %llu\n", i);
		int numDigits = GetNumDigitsInNumber(i);
		if (numDigits % 2 != 0)
		{
			continue;
		}

		unsigned long long firstHalf = i / Power(10, numDigits / 2);
		unsigned long long secondHalf = i - (firstHalf * Power(10, numDigits / 2));

		if (firstHalf == secondHalf)
		{
			invalidIds += i;
		}
	}

	return invalidIds;
}

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	char currentChar;
	int currentIndex = 0;
	char rangeStart[50] = { '\0' };
	char rangeEnd[50] = { '\0' };
	bool beforeDash = true;
	int rangeIndex = 0;

	unsigned long long totalInvalidIds = 0;

	while ((currentChar = fgetc(file)) != EOF)
	{
		if ((char)currentChar == '-')
		{
			beforeDash = false;
			rangeIndex = 0;
			continue;
		}
		if ((char)currentChar == ',' || (char)currentChar == '\n')
		{
			beforeDash = true;
			long long rangeA = atoll(rangeStart);
			long long rangeB = atoll(rangeEnd);
			printf("RangeA: %lld\n", rangeA);
			printf("RangeB: %lld\n", rangeB);
			totalInvalidIds += GetInvalidIds(rangeA, rangeB);
			ResetArray(rangeStart, 50);
			ResetArray(rangeEnd, 50);
			rangeIndex = 0;
			continue;
		}
		if (beforeDash)
		{
			rangeStart[rangeIndex++] = (char)currentChar;
		}
		else
		{
			rangeEnd[rangeIndex++] = (char)currentChar;
		}
	}

	printf("Invalid ids: %llu\n", totalInvalidIds);

	return 0;
}
