#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void fillemptypos(vector<vector<int>>& vec, int& x, int& y)
{
	x = rand() % 4;
	y = rand() % 4;
	srand(time(NULL));
	while (true)
	{
		if (vec[y][x] == 0)
		{
			vec[y][x] = 2;
			break;
		}
		else
		{
			x = rand() % 4;
			y = rand() % 4;
		}
	}

}

void fillvector(vector<vector<int>>& vec)
{
	vector<int> rowvec;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rowvec.push_back(0);
		}
		vec.push_back(rowvec);
		rowvec.erase(rowvec.begin(), rowvec.end());
	}
}

void printvector(vector<vector<int>>& vector, int& x, int& y)
{
	int tempj = 0;
	for (int i = 0; i < 4; i++)
	{
		gotoxy(10, 5 + i);
		for (int j = 0; j < 4; j++)
		{
			if (j == x && i == y)
			{
				color(10);
				cout << vector[i][j];
				color(7);
			}
			else
			{
				cout << vector[i][j];
			}
			if (vector[i][j] > 999)
				cout << " ";
			else if (vector[i][j] > 99)
				cout << "  ";
			else if (vector[i][j] > 9)
				cout << "   ";
			else
				cout << "    ";

		}
		cout << endl;
	}
}

void rightmove(vector<vector<int>>& vec)
{
	int crow, ccol;
	for (int i = 0; i < 4; i++)
	{
		crow = i, ccol = 3;
		for (int j = 2; j >= 0; j--)
		{
			if (vec[i][j] != 0)
			{
				if (vec[i][j + 1] == 0 || vec[i][j + 1] == vec[i][j])
				{
					if (vec[crow][ccol] == vec[i][j])
					{
						vec[crow][ccol] *= 2;
						vec[i][j] = 0;
					}
					else
					{
						if (vec[crow][ccol] == 0)
						{
							vec[crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
						else
						{
							vec[crow][--ccol] = vec[i][j];
							vec[i][j] = 0;
						}
					}
				}
				else ccol--;
			}
		}
	}
}

void leftmove(vector<vector<int>>& vec)
{
	int crow, ccol;
	for (int i = 0; i < 4; i++)
	{
		crow = i, ccol = 0;
		for (int j = 1; j < 4; j++)
		{
			if (vec[i][j] != 0)
			{
				if (vec[i][j - 1] == 0 || vec[i][j - 1] == vec[i][j])
				{
					if (vec[crow][ccol] == vec[i][j])
					{
						vec[crow][ccol] *= 2;
						vec[i][j] = 0;
					}
					else
					{
						if (vec[crow][ccol] == 0)
						{
							vec[crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
						else
						{
							vec[crow][++ccol] = vec[i][j];
							vec[i][j] = 0;
						}
					}
				}
				else ccol++;
			}
		}
	}
}

void downmove(vector<vector<int>>& vec)
{
	int crow, ccol;
	for (int j = 0; j < 4; j++)
	{
		crow = 3, ccol = j;
		for (int i = 2; i >= 0; i--)
		{
			if (vec[i][j] != 0)
			{
				if (vec[i + 1][j] == 0 || vec[i + 1][j] == vec[i][j])
				{
					if (vec[crow][ccol] == vec[i][j])
					{
						vec[crow][ccol] *= 2;
						vec[i][j] = 0;
					}
					else
					{
						if (vec[crow][ccol] == 0)
						{
							vec[crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
						else
						{
							vec[--crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
					}
				}
				else crow--;
			}
		}
	}
}

void upmove(vector<vector<int>>& vec)
{
	int crow, ccol;
	for (int j = 0; j < 4; j++)
	{
		crow = 0, ccol = j;
		for (int i = 1; i < 4; i++)
		{
			if (vec[i][j] != 0)
			{
				if (vec[i - 1][j] == 0 || vec[i - 1][j] == vec[i][j])
				{
					if (vec[crow][ccol] == vec[i][j])
					{
						vec[crow][ccol] *= 2;
						vec[i][j] = 0;
					}
					else
					{
						if (vec[crow][ccol] == 0)
						{
							vec[crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
						else
						{
							vec[++crow][ccol] = vec[i][j];
							vec[i][j] = 0;
						}
					}
				}
				else crow++;
			}
		}
	}
}

int checkgame(vector<vector<int>>& vec)
{
	bool space = false, movepossible = false, win = false;
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (vec[i][j] == 0)
			{
				space = true;
				break;
			}
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (vec[i + 1][j] == vec[i][j] || vec[i][j + 1] == vec[i][j])
			{
				movepossible = true;
				break;
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (vec[i][j] == 2048)
			{
				win = true;
				break;
			}
		}
	}

	if (win)
		return 2;
	else if (space || movepossible)
		return 1;
	else
		return 0;
}

bool movecheck(vector<vector<int>>& tempvec, vector<vector<int>>& vec)
{
	bool moveflag = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tempvec[i][j] != vec[i][j])
			{
				moveflag = true;
				break;
			}
		}
	}
	return moveflag;
}

int score(vector<vector<int>>& vec)
{
	int score = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			score += vec[i][j];
		}
	}
	return score;
}

int gethigh(vector<vector<int>>& vec)
{
	int highscore = 0, bestscore = 0;
	ifstream scorestream;
	ofstream scoreout;
	scorestream.open("highscore.txt");
	scorestream >> bestscore;
	scorestream.close();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			highscore += vec[i][j];
		}
	}
	if (highscore > bestscore)
	{
		bestscore = highscore;
		scoreout.open("highscore.txt");
		scoreout << highscore;
		scoreout.close();
	}
	return bestscore;
}
void game()
{
	char ch, gameover, wingame;
	int x, y;
	bool quit = false, mainquit = false;
	vector<vector<int>> vec, tempvec;
	fillvector(vec);
	fillvector(tempvec);
	fillemptypos(vec, x, y);
	printvector(vec, x, y);
	gotoxy(10, 10);
	cout << "Score: " << score(vec);
	gotoxy(10, 12);
	cout << "Current high score: " << gethigh(vec);
	while (!quit)
	{
		ch = _getch();
		tempvec = vec;
		switch (ch)
		{
		case 75:
			leftmove(vec);
			break;
		case 77:
			rightmove(vec);
			break;
		case 72:
			upmove(vec);
			break;
		case 80:
			downmove(vec);
			break;
		case 'q':
			quit = true;
			break;
		}
		if (movecheck(tempvec, vec))
		{
			fillemptypos(vec, x, y);
		}
		printvector(vec, x, y);
		gotoxy(10, 10);
		cout << "Score: " << score(vec);
		gotoxy(10, 12);
		cout << "Current high score: " << gethigh(vec);
		if (checkgame(vec) == 2)
		{
			gotoxy(10, 2);
			color(10);
			cout << "You Win!";
			gotoxy(10, 3);
			color(7);
			cout << "Press Enter to return to Main Menu";
			while (!quit)
			{
				wingame = _getch();
				if (wingame == '\r')
				{
					quit = true;
				}
			}
		}
		else if (!checkgame(vec))
		{

			gotoxy(10, 2);
			color(12);
			cout << "Game Over!";
			gotoxy(10, 3);
			color(7);
			cout << "Press Enter to return to Main Menu";
			while (!quit)
			{
				gameover = _getch();
				if (gameover == '\r')
				{
					quit = true;
				}
			}
		}

	}

}
int main()
{
	vector<int> colorvec = { 7,7,7,7 };
	bool mainquit = false;
	char ch;
	int counter = 2;
	while (!mainquit)
	{
		gotoxy(0, 2);
		color(colorvec[0]);
		cout << "Play";

		gotoxy(0, 4);
		color(colorvec[1]);
		cout << "Rules";

		gotoxy(0, 6);
		color(colorvec[2]);
		cout << "Quit";

		ch = _getch();
		if (ch == 72 && (counter >= 2 && counter <= 3))
		{
			--counter;
		}
		if (ch == 80 && (counter >= 1 && counter <= 2))
		{
			++counter;
		}
		if (ch == '\r')
		{
			system("cls");
			if (counter == 1)
			{
				game();
			}

			if (counter == 2)
			{
				cout << "Move with the arrow keys" << endl << endl << "To win, get 2048" << endl << endl;
				cout << "Newly added numbers are colored ";
				color(10);
				cout << "green" << endl << endl;
				color(7);
				cout << "Quit - q";
				_getch();
			}

			if (counter == 3)
			{
				mainquit = true;
			}

			system("cls");
		}
		colorvec[0] = 7;
		colorvec[1] = 7;
		colorvec[2] = 7;
		if (counter == 1)
		{
			colorvec[0] = 10;
		}
		if (counter == 2)
		{
			colorvec[1] = 10;
		}
		if (counter == 3)
		{
			colorvec[2] = 10;
		}
	}
}