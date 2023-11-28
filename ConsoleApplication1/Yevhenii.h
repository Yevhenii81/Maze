//#include <iostream>
//#include <ctime> // time
//#include <Windows.h> // окрашивание, работа с координатами
//#include <conio.h> // configurate input output
//
//#pragma comment(lib, "winmm.lib")
#include "Settings.h"


using namespace std;

// 1) определение (создание) функции

enum Directions { LEFT = 75, RIGTH = 77, DOWN = 80, UP = 72 };
enum Colors { RED = 12, BLACK = 0, DARKBLUE = 3, YELLOW = 14, PINK = 13 };
enum ObjectTypes { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, MEDICINE = 4 };

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


// ОПИСАНИЕ ФУНКЦИИ:
    // установка курсора в определённую позицию
    // + окрашивание текста в определённый цвет
    // + вывод строки текста


//1) функция курсора
void SetCursor(int x, int y, int color, string text) // пример функции с 4 параметрами
{
    // дескриптор окна консоли (уникальный номер окна в консоли, нужен для того чтобы найти конкретное окно и выполнить именно над ним определённые действия)
    // специальный структурный тип для работы с координатами (для перестановки курсора)
    COORD position;
    position.X = x; // настройка конкретных координат
    position.Y = y;
    SetConsoleCursorPosition(h, position); // установка курсора в заданную точку
    SetConsoleTextAttribute(h, color); // смена цвета
    cout << text; // вывод строки текста
    cout << "\n";
}


const int width = 60; //ширина лабиринта
const int heigth = 20; //высота лабиринта 
int maze[heigth][width] = {};


// 2) Функция, которая инициализирует лабиринт
void InitializeMaze(int maze[][width], int width, int heigth)
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5;

			if (x == 0 || y == 0 || x == width - 1 || y == heigth - 1)
			{
				maze[y][x] = WALL;
			}
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 || x == width - 1 && y == heigth - 3) {
				maze[y][x] = HALL;

			}

			if (maze[y][x] == ENEMY)
			{
				int probality = rand() % 10;
				if (probality != 0)
				{
					maze[y][x] = HALL;
				}
			}


			if (maze[y][x] == MEDICINE)
			{
				int probality_m = rand() % 10;
				if (probality_m != 0)
				{
					maze[y][x] = HALL;
				}
			}

		}
	}
}

// 3)Функция, которая рисует лабиринт
void PrintMaze(int maze[][width], int width, int heigth)
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (maze[y][x] == HALL)
			{
				SetConsoleTextAttribute(h, BLACK);
				cout << " "; // коридор
			}
			else if (maze[y][x] == WALL)
			{
				SetConsoleTextAttribute(h, DARKBLUE);
				cout << (char)178; // стена
				// cout << "#";
			}
			else if (maze[y][x] == COIN)
			{
				SetConsoleTextAttribute(h, YELLOW);
				cout << ".";
			}
			else if (maze[y][x] == ENEMY)
			{
				// cout << "*"; // враг
				SetConsoleTextAttribute(h, RED);
				cout << (char)1;
			}
			else if (maze[y][x] == MEDICINE)
			{
				SetConsoleTextAttribute(h, 91);
				cout << (char)5;
			}
		}
		cout << "\n";
	}
}

//4) функция, которая скрывает курсор
 
void HideCursor(bool vision, int size)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
}


DWORD WINAPI MusicThread(void* param)
{
	int soundType = *((int*)param);

	switch (soundType)
	{
		case 0:
			PlaySoundA("C:\\!music\\!wav\\upali-dengi-na-igrovoy-schet.wav", NULL, SND_NODEFAULT | SND_LOOP);
			break;
		case 1:
			PlaySoundA("C:\\!music\\!wav\\damage-sound.wav", NULL, SND_NODEFAULT | SND_LOOP);
			break;
	}
	
	
	return 0;
}
