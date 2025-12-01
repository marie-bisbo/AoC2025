#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("No file found!\n");

		return 0;
	}

	char line[10];
	int currentPosition = 50;
	int password = 0;

	while ((fgets(line, sizeof(line), file)) != NULL)
	{
		char direction = line[0];
		int amount = atoi(&line[1]);
		int rotations = amount / 100;
		password += rotations;
		amount -= (rotations * 100);

		switch (direction)
		{
		case 'R':
		{
			if ((currentPosition + amount) > 99)
			{
				++password;
			}
			currentPosition = (currentPosition + amount) % 100;
			break;
		}
		case 'L':
		{
			if ((currentPosition - amount) < 1 && currentPosition != 0)
			{
				++password;
			}
			const int remainder = (currentPosition - amount) % 100;
			currentPosition = remainder < 0 ? 100 + remainder : remainder;
			break;
		}
		default:
			continue;
		}
	}

	printf("Password: %d\n", password);

	return 0;
}