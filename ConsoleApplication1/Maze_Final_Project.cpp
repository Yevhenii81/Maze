#include "Yevhenii.h"
#include "Settings.h"

int main()
{
    system("title Maze");

	HWND hwnd = GetConsoleWindow();

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	int window_width = 1360;
	int window_height = 768;

	MoveWindow(hwnd,
		(screen_width - window_width) /2,
		(screen_height - window_height) / 2,
		window_width,
		window_height,
		1);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// функция, которая скрывает курсор
	HideCursor(false, 100);

    srand(time(0));

    const int width = 60; //ширина лабиринта
    const int height = 20; //высота лабиринта 
    int maze[height][width] = {}; // заготовка

	//////////
	//setlocale(0, "RUS"); ////перевод с латины на русский


    // Функция, которая инициализирует лабиринт
    InitializeMaze(maze, width, height);

    // Функция, которая рисует лабиринт
    PrintMaze(maze, width, height);

    COORD position;
    position.X = 0;
    position.Y = 2;
    SetCursor(0, 2, PINK, "\x01");

	int coins = 0;
	int hp = 100, enemyDamage = 25, medicineRestore = 25;
	while (true) {
		int code = _getch();
		if (code == 224)
		{
			code = _getch();
		}

		//cout << code << "\n";

		SetConsoleCursorPosition(h, position);
		cout << " ";
		
		if (code == RIGTH && maze[position.Y][position.X + 1] != WALL)
		{
			position.X++;
		}
		else if (code == LEFT && maze[position.Y][position.X - 1] != WALL)
		{
			position.X--;
		}
		else if (code == DOWN && maze[position.Y + 1][position.X] != WALL)
		{
			position.Y++;
		}
		else if (code == UP && maze[position.Y - 1][position.X] != WALL)
		{
			position.Y--;
		}

		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, PINK);
		cout << (char)1;

		///////////////////////////////////

		if (position.X == width - 1 && position.Y == heigth - 3)
		{
			MessageBoxA(0, "найден выход из лабиринта!", "ПОБЕДА!", MB_OK);
			/*system("cls");
			cout << "YOU WIN!!!\n\n";*/
			break;
		}

		if (maze[position.Y][position.X] == COIN)
		{
			coins++;
			maze[position.Y][position.X] = HALL;
			COORD coins_info;
			coins_info.X = width + 2;
			coins_info.Y = 1;
			SetConsoleCursorPosition(h, coins_info);
			SetConsoleTextAttribute(h, YELLOW);
			cout << "COIN: " << coins;
			
			//// звук збора монеты
			int soundTypeCoin = 0;
			CreateThread(0, 0, MusicThread, (void*)&soundTypeCoin, 0, 0);
		}

		if (maze[position.Y][position.X] == ENEMY)
		{
			hp -= enemyDamage;
			maze[position.Y][position.X] = HALL;
			COORD hp_info;
			hp_info.X = width + 1;
			hp_info.Y = 2;
			SetConsoleCursorPosition(h, hp_info);
			SetConsoleTextAttribute(h, RED);
			cout << " HP: " << hp << " %";

			/// звук урона
			int soundTypeEnemy = 1;
			CreateThread(0, 0, MusicThread, (void*)&soundTypeEnemy, 0, 0);

			if (hp <= 0)
			{
				MessageBoxA(0, "Вас атаковали враги! Игра окончена!", "ПОРАЖЕНИЕ!", MB_OK);
				break;
			}
		}

		if (maze[position.Y][position.X] == MEDICINE)
		{
			if (hp < 100)
			{
				hp += medicineRestore;
				if (hp > 100)
				{
					hp = 100;
				}
				maze[position.Y][position.X] = HALL;
				COORD hp_info;
				hp_info.X = width + 1;
				hp_info.Y = 2;
				SetConsoleCursorPosition(h, hp_info);
				SetConsoleTextAttribute(h, RED);
				cout << " HP: " << hp << " %";
			}
		}

	}

	system("cls");
	cout << "YOU WIN!!!\n\n";


	Sleep(INFINITE);
   
}




	// коридоры - 0
	// стены - 1
	// монетки - 2
	// враги - 3


// Было 222, стало - 210

