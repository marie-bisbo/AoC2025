#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Range
{
	uint64_t start;
	uint64_t end;
} Range;

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
	Range ranges[185];
	int currentRange = 0;

	char line[50];

	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		if (line[0] == '\n')
		{
			continue;
		}
		for (int i = 0; i < strlen(line); i++)
		{
			char current = line[i];
			if (current == '-')
			{
				beforeDash = false;
				rangeIndex = 0;
				continue;
			}
			if (current == '\n')
			{
				beforeDash = true;
				uint64_t rangeA = atoll(rangeStart);
				uint64_t rangeB = atoll(rangeEnd);
				Range range;
				range.start = rangeA;
				range.end = rangeB;
				ranges[currentRange++] = range;
				memset(rangeStart, '\0', 50);
				memset(rangeEnd, '\0', 50);
				rangeIndex = 0;
				continue;
			}
			if (beforeDash)
			{
				rangeStart[rangeIndex++] = current;
			}
			else
			{
				rangeEnd[rangeIndex++] = current;
			}
		}
	}

	FILE* file2 = fopen(argv[2], "r");

	if (file2 == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	uint64_t totalFreshIds = 0;

	while ((fgets(line, sizeof(line), file2)) != NULL)
	{
		if (line[0] == '\n')
		{
			continue;
		}

		uint64_t ingredientId = atoll(line);
		for (int i = 0; i < 185; i++)
		{
			Range currentRange = ranges[i];
			if (ingredientId >= currentRange.start && ingredientId <= currentRange.end)
			{
				++totalFreshIds;
				break;
			}
		}
	}

	printf("Fresh ids: %llu\n", totalFreshIds);

	return 0;
}
