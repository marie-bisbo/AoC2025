#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW_SIZE 136
#define COLUMN_SIZE 136

int GridPositionToIndex(int xPosition, int yPosition, int numRows)
{
	if (xPosition < 0 || yPosition < 0)
	{
		return -1;
	}

	return (yPosition * numRows) + xPosition;
}

int* GetNeighbours(int* grid, int xPosition, int yPosition, int numRows, int numColumns)
{
	int* neighbours = malloc(8 * sizeof(int));
	if (neighbours == NULL)
	{
		return NULL;
	}
	memset(neighbours, 0, 8 * sizeof(int));

	int neighbourCount = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == j && i == 0)
			{
				continue;
			}
			if (xPosition + i > -1 && xPosition + i < ROW_SIZE && yPosition + j > -1 && yPosition + j < COLUMN_SIZE)
			{
				int index = GridPositionToIndex(xPosition + i, yPosition + j, COLUMN_SIZE);
				neighbours[neighbourCount++] = grid[index];
			}
		}
	}

	return neighbours;
}

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	char line[ROW_SIZE + 1];
	int grid[ROW_SIZE * COLUMN_SIZE];
	int currentRow = 0;

	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		if (line[0] == '\n')
		{
			continue;
		}

		for (int i = 0; i < ROW_SIZE; i++)
		{
			int index = GridPositionToIndex(i, currentRow, COLUMN_SIZE);
			grid[index] = line[i] == '@' ? 1 : 0;
		}

		++currentRow;
	}

	bool canRemove = true;
	int accessibleToiletRolls = 0;
	while (canRemove)
	{
		int tmpToiletRolls = 0;
		for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COLUMN_SIZE; j++)
			{
				int index = GridPositionToIndex(i, j, COLUMN_SIZE);
				if (grid[index] == 0)
				{
					continue;
				}
				int* neighbours = GetNeighbours(grid, i, j, COLUMN_SIZE, ROW_SIZE);
				int numToiletRolls = 0;
				for (int rolls = 0; rolls < 8; rolls++)
				{
					int isRoll = neighbours[rolls];
					numToiletRolls += neighbours[rolls];
				}
				if (numToiletRolls < 4)
				{
					grid[index] = 0;
					++accessibleToiletRolls;
					++tmpToiletRolls;
				}

				free(neighbours);
			}
		}

		canRemove = tmpToiletRolls != 0;
	}

	printf("Accessible toilet rolls: %d\n", accessibleToiletRolls);

	return 0;
}
