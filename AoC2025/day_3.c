#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BANK_SIZE 101

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	char line[BANK_SIZE];
	int totalJolts = 0;

	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		if (line[0] == '\n')
		{
			continue;
		}
		int first = 0;
		int second = 0;
		for (int i = 0; i < BANK_SIZE - 2; i++)
		{
			int batteryValue = line[i] - '0';
			int nextBatteryValue = line[i + 1] - '0';
			if (batteryValue > first)
			{
				first = batteryValue;
				second = 0;
			}
			if (nextBatteryValue > second)
			{
				second = nextBatteryValue;
			}
		}

		totalJolts += (first * 10) + second;
	}


	printf("Total jolts: %d\n", totalJolts);

	return 0;
}
