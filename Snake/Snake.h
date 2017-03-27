#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>


enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum Color
{
	DARK_GREEN = 2,
	YELLOW = 6,
	GREY = 7,
	GREEN = 10,
	RED = 12
};

class Apple;
class Snake;
class Stone;
class SnakePart;
class BaseElement;
class Wall;

bool operator==(const BaseElement left, const BaseElement right);

class BaseElement
{
protected:
	short x;
	short y;
	static HANDLE outHandle;
	Color color;
	char symbol;
public:
	friend bool operator==(const BaseElement left, const BaseElement right);
	BaseElement operator=(BaseElement copy);
	void snakeCollision(Snake*, Wall*);
	void changeCoord();
	bool collision(BaseElement part);
	void draw();
	short getX()
	{
		return x;
	};
	short getY()
	{
		return y;
	};
};




class Stone : public BaseElement
{
public:
	Stone();
};


class SnakePart : public BaseElement
{
public:
	SnakePart();
	void setSymbol(char symbol)
	{
		this->symbol = symbol;
	}
	void setX(int x)
	{
		this->x = x;
	};
	void setY(int y)
	{
		this->y = y;
	}
};


class Apple : public BaseElement
{
public:
	Apple();

};

class Snake
{
	SnakePart* body;
	SnakePart head;
	int size;
	Direction direction;
	HANDLE outHandle;
	COORD coord;
public:
	Snake();
	void deleteSnake();
	void move();
	void grow();
	bool collision(Wall wall);
	void draw();
	bool eat(Apple apple);
	friend void Apple::snakeCollision(Snake* snake, Wall* wall);
	SnakePart getHead()
	{
		return head;
	}
	int getSize()
	{
		return size;
	};
	int getDirection()
	{
		return direction;
	}
	void setDirection(Direction direction)
	{
		this->direction = direction;
	}
};


class Wall
{
	Stone* stones;
	int stoneCount;
public:
	Wall();
	void deleteWall();
	Stone* addNewStone();
	friend bool Snake::collision(Wall wall);
	friend void Apple::snakeCollision(Snake* snake, Wall* wall);
};


class Game
{
	Snake snake;
	Apple apple;
	bool gameOver;
	int score;
	static HANDLE outHandle;
	Wall wall;
public:
	void step();
	void start();
	void pause();
	void printResult();
	void printCurrentScore();
	void printFrame();
};

