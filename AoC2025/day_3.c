#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BANK_SIZE 100

uint64_t Power(int value, int power)
{
	uint64_t result = 1;

	while (power--)
	{
		result *= value;
	}

	return result;
}

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	char line[BANK_SIZE + 1];
	uint64_t totalJolts = 0;

	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		if (line[0] == '\n')
		{
			continue;
		}
		int batteries[12] = { 0 };
		int startIndex = 0;
		int currentStartIndex = 0;
		int endIndex = BANK_SIZE - 11;
		for (int i = 0; i < 12; i++)
		{
			startIndex = currentStartIndex;
			for (int j = startIndex; j < endIndex; j++)
			{
				int batteryValue = line[j] - '0';
				if (batteryValue > batteries[i])
				{
					batteries[i] = batteryValue;
					currentStartIndex = j + 1;
				}
			}	
			++endIndex;
		}
		
		uint64_t jolts = 0;
		int power = 11;
		for (int i = 0; i < 12; i++)
		{
			jolts += (batteries[i] * Power(10, power));
			--power;
		}

		totalJolts += jolts;
	}


	printf("Total jolts: %llu\n", totalJolts);

	return 0;
}
