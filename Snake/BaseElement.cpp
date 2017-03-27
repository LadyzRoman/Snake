#include "Snake.h"


HANDLE BaseElement::outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

bool BaseElement::collision(BaseElement obj)
{
	return x == obj.x && y == obj.y;
}

void BaseElement::draw()
{
	SetConsoleTextAttribute(outHandle, color);
	SetConsoleCursorPosition(outHandle, { x, y });
	putch(symbol);
}

bool operator==(const BaseElement left, const BaseElement right)
{
	return left.x == right.x && left.y == right.y && left.symbol == right.symbol;
}

void BaseElement::changeCoord()
{
	x = rand() % 32 + 24;
	y = rand() % 23 + 1;
}


void BaseElement::snakeCollision(Snake* snake, Wall* wall)
{
	if (collision(snake->head))
	{
		changeCoord();
		snakeCollision(snake, wall);
	}
	for (int i = 0; i < snake->size; i++)
		if (collision(snake->body[i]))
		{
			changeCoord();
			snakeCollision(snake, wall);
		}
	for (int i = 0; i < wall->stoneCount; i++)
		if (!(*this == wall->stones[i]) && collision(wall->stones[i]))
		{
			changeCoord();
			snakeCollision(snake, wall);
		}

	
}

BaseElement BaseElement::operator=(BaseElement copy)
{
	x = copy.x;
	y = copy.y;
	return *this;
};