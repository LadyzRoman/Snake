#include "Snake.h"

SnakePart::SnakePart()
{
	int rnd = rand() % 3;
	color = rnd == 2 ? GREEN : rnd == 1 ? DARK_GREEN : YELLOW;
}


