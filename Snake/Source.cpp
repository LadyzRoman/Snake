#include "Snake.h"

int selectMenu();

int main(void)
{

	Game game;

	setlocale(LC_ALL, "Rus");
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(outHandle, &structCursorInfo);
	structCursorInfo.bVisible = false;
	SetConsoleCursorInfo(outHandle, &structCursorInfo);
	SetConsoleScreenBufferSize(outHandle, { 80, 26 });

	while (true)
	{
		switch (selectMenu())
		{

		case 0:
			game.start();
			break;
		case 1:
			return 0;
		}
	}
}


int selectMenu()
{
	static int size = 2;									//Размер массива названий
	static int current = 0;									//Текущий выбранный элемент
	static HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);	//Изменение цвета строки
	static char *names[] = {								//Заголовки пунктов меню
		"Новая игра",
		"  Выход   "
	};
	int code = 72;	//Код нажатой клавиши


	system("cls");
	SetConsoleTextAttribute(outHandle, GREEN);
	SetConsoleCursorPosition(outHandle, { 0, 6 });
	printf("%26s 000  0  0   00   0  0  0000\n", "");
	printf("%26s0     00 0  0  0  0 0   0   \n", "");
	printf("%26s 00   0 00  0000  00    0000\n", "");
	printf("%26s   0  0  0  0  0  0 0   0   \n", "");
	printf("%26s000   0  0  0  0  0  0  0000\n", "");


	do
	{
		if (code == 72 || code == 80)
		{
			for (int i = 0; i < size; i++)
			{
				if (current == i)
					SetConsoleTextAttribute(outHandle, DARK_GREEN);

				SetConsoleCursorPosition(outHandle, {27, 15 + (short)i});

				printf("%-7s%s%-6s\n", current == i ? "  -->  " : "", names[i], current == i ? "  <--" : "");

				if (current == i)
					SetConsoleTextAttribute(outHandle, GREY);
			}
		}
		code = getch();
		if (code == 224 || code == 0)
			code = getch();
		if (code == 72)
		{
			current--;
			current = current < 0 ? current + size : current;
		}
		else if (code == 80)
		{
			current++;
			current %= size;
		}
	} while (code != 13);

	system("cls");
	SetConsoleTextAttribute(outHandle, GREY);

	return current;
}
