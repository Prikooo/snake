#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>

using namespace std;

/////////////////////////////////////////////////
const int width = 41, height = 30;

const char Location[height][width] =
{
	"########################################",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"########################################"
};

char location[height][width];

bool isWork = true;
bool isApple = false;

int dx = 1, dy;

vector <pair <int, int>> Snake;

/////////////////////////////////////////////////
void snakeUpdate(int &x, int &y)
{
	for (int i = Snake.size() - 1; i > 0; i--)
		Snake[i] = Snake[i - 1];

	x += dx;
	y += dy;

	if (location[y][x] == '#')
	{
		x -= dx * (width - 3);
		y -= dy * (height - 2);
	}

	Snake[0] = pair <int, int>(x, y);

	if (location[Snake[0].second][Snake[0].first] >= '1' && location[Snake[0].second][Snake[0].first] <= '3')
	{
		for (int i = 0; i < location[Snake[0].second][Snake[0].first] - '1' + 1; i++)
			Snake.push_back(pair <int, int>(Snake[Snake.size() - 1].first, Snake[Snake.size() - 1].second));

		isApple = false;
	}

	for (int i = 1; i < Snake.size(); i++)
		location[Snake[i].second][Snake[i].first] = 'o';

	if (location[Snake[0].second][Snake[0].first] == 'o')
		isWork = false;

	location[Snake[0].second][Snake[0].first] = 'O';
}

/////////////////////////////////////////////////
int main()
{
	Snake.push_back(pair <int, int>(5, 5));
	Snake.push_back(pair <int, int>(4, 5));
	Snake.push_back(pair <int, int>(3, 5));

	int x = 5, y = 5;

	int xA, yA;

	char a = 1;

	for (int i = 0; i < height; i++)
		strcpy_s(location[i], Location[i]);

	/////////////////////////////////////////////
	while (isWork)
	{
		system("cls");

		/////////////////////////////////////////		
		if (isApple == false)
		{
			isApple = true;

			do
			{
				xA = rand() % (height - 2) + 1;
				yA = rand() % (width - 3) + 1;
			}
			while (location[xA][yA] != ' ');

			a = '1' + rand() % 3;
		}

		for (int i = 0; i < height; i++)
			strcpy_s(location[i], Location[i]);

		location[xA][yA] = a;

		/////////////////////////////////////////
		if (_kbhit() != 0)
		{
			char s = _getch();

			if (s == 'w' && dy != 1)
			{
				dx = 0;
				dy = -1;
			}
			else if (s == 's' && dy != -1)
			{
				dx = 0;
				dy = 1;
			}
			else if (s == 'a' && dx != 1)
			{
				dx = -1;
				dy = 0;
			}
			else if (s == 'd' && dx != -1)
			{
				dx = 1;
				dy = 0;
			}
		}

		snakeUpdate(x, y);

		/////////////////////////////////////////
		for (int i = 0; i < height; i++)
			puts(location[i]);

		Sleep(100);
	}
	/////////////////////////////////////////////

	puts("\n\t\tGAME OVER\n");

	system("pause");
	/////////////////////////////////////////////
}
/////////////////////////////////////////////////