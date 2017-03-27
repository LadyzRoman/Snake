#include "Snake.h"


Snake::Snake()
{
	head.setSymbol(2);
	head.setX(40);
	head.setY(10);
	direction = RIGHT;
	size = 3;
	outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	body = new SnakePart[size];
	for (int i = 0; i < size; i++)
	{
		body[i].setSymbol(!(i % 2) ? 'o' : 'O');
		body[i].setX(39 - i);
		body[i].setY(10);
	}
}

void Snake::deleteSnake()
{
	delete[] body;
}

void Snake::move()
{
	SnakePart temp;
	temp = body[size - 1];

	coord = { temp.getX(), temp.getY() };
	SetConsoleCursorPosition(outHandle, coord);
	putch(32);

	for (int i = size - 1; i > 0; i--)
		body[i] = body[i - 1];
	body[0] = temp;
	body[0].setX(head.getX());
	body[0].setY(head.getY());

	switch (direction)
	{
	case UP:
		head.setY(head.getY() - 1);
		break;
	case DOWN:
		head.setY(head.getY() + 1);
		break;
	case RIGHT:
		head.setX(head.getX() + 1);
		break;
	case LEFT:
		head.setX(head.getX() - 1);
		break;
	}
}


void Snake::grow()
{
	SnakePart* temp = new SnakePart[size + 1];
	memcpy(temp, body, size * sizeof(SnakePart));
	temp[size] = temp[size - 1];
	temp[size].setSymbol(!(size % 2) ? 'o' : 'O');
	body = temp;
	size++;
}

void Snake::draw()
{
	for (int i = 0; i < size; i++)
		body[i].draw();
	head.draw();
}



bool Snake::collision(Wall wall)
{
	for (int i = 0; i < size; i++)
	{
		if (head.collision(body[i]))
			return true;
	}
	for (int i = 0; i < wall.stoneCount; i++)
	{
		if (head.collision(wall.stones[i]))
			return true;
	}
	return head.getX() <= 23 || head.getX() >= 56 || !head.getY() || head.getY() >= 24;
}

bool Snake::eat(Apple apple)
{
	return apple.collision(head);
}