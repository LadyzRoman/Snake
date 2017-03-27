#include "Snake.h"


HANDLE Game::outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Game::start()
{
	int size;
	int speed;
	score = 0;
	gameOver = false;
	snake = Snake();
	wall = Wall();

	printFrame();
	printCurrentScore();
	snake.draw();
	apple.changeCoord();
	apple.draw();
	pause();
	while (!gameOver)
	{
		step();
		size = snake.getSize();
		speed = 60 * (float)(size + 18) / (float)size;
		Sleep(speed);
	}
	printResult();
	while (getch() != 13);

	snake.deleteSnake();
	wall.deleteWall();
}


void Game::step()
{
	int x;
	if (kbhit())
	{
		x = getch();

		if (x == 27)
		{
			pause();
		}
		else if (x == 224 && kbhit())
		{
			switch (getch())
			{
			case 80:
				snake.setDirection(DOWN);
				break;
			case 72:
				snake.setDirection(UP);
				break;
			case 75:
				snake.setDirection(LEFT);
				break;
			case 77:
				snake.setDirection(RIGHT);
				break;
			}
		}
	}

	snake.move();
	snake.draw();
	if (snake.eat(apple))
	{
		snake.grow();
		if (!(rand() % 7))
		{
			Stone* stone = wall.addNewStone();
			stone->changeCoord();
			stone->snakeCollision(&snake, &wall);
			stone->draw();
		}
		apple.changeCoord();
		apple.snakeCollision(&snake, &wall);
		apple.draw();
		score += 10;

		printCurrentScore();
	}

	else
		gameOver = snake.collision(wall);

}


void Game::printFrame()
{
	printf("%23s@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%22s\n", "", "");
	for (int i = 0; i < 23; i++)
		printf("%23s@%32s@%22s\n", "", "", "");
	printf("%23s@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%22s\n", "", "");
	SetConsoleCursorPosition(outHandle, { 0, 0 });
}


void Game::printResult()
{
	SetConsoleTextAttribute(outHandle, RED);
	SetConsoleCursorPosition(outHandle, { 24, 8 });
	printf("%9s%s%9s", "", "ÂÛ ÏÐÎÈÃÐÀËÈ!", "");
	SetConsoleCursorPosition(outHandle, { 24, 9 });
	printf("%32s", "");
	SetConsoleCursorPosition(outHandle, { 24, 10 });
	printf("%9s%s%4d%9s", "", "ÂÀØ Ñ×ÅÒ:", score, "");
	SetConsoleCursorPosition(outHandle, { 24, 11 });
	printf("%32s", "Äëÿ âûõîäà â ìåíþ íàæìèòå Enter!");
	SetConsoleCursorPosition(outHandle, { 24, 12 });
	printf("%32s", "");
}


void Game::printCurrentScore()
{
	SetConsoleCursorPosition(outHandle, { 5, 10 });
	SetConsoleTextAttribute(outHandle, DARK_GREEN);
	printf("ÒÅÊÓÙÈÉ Ñ×ÅÒ");
	SetConsoleCursorPosition(outHandle, { 5, 12 });
	printf("%6d", score);
}

void Game::pause()
{
	SetConsoleCursorPosition(outHandle, { 6, 5 });
	SetConsoleTextAttribute(outHandle, RED);
	printf("Ï À Ó Ç À");
	system("pause>nul");
	SetConsoleCursorPosition(outHandle, { 6, 5 });
	printf("         ");

}