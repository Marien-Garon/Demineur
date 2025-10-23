#include <conio.h>
#include "grid.hpp"
#include "color.h"


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27


int clamp(int val, int min, int max)
{
	if (val < min) val = min;
	if (val >= max)  val = max -1;
	return val;
}

bool KeyInput(Grid* grid, int* row, int* col, bool isFlagMode)
{
	int key = 0;
	bool notEscape = true;
	while (key != ENTER && key != ESC)
	{
		switch (key = _getch())
		{
		case KEY_UP :
			*row-=1;
			break;
		case KEY_DOWN :
			*row += 1;
			break;
		case KEY_LEFT :
			*col -= 1;
			break;
		case KEY_RIGHT :
			*col += 1;
			break;
		case ESC:
			notEscape = false;
			break; 
		}
		*row = clamp(*row,0, grid->rowCount);
		*col = clamp(*col, 0, grid->colCount);
		DisplayGrid(grid, *row, *col, isFlagMode, false);
	}
	return notEscape;
}

void DisplayWin(bool win)
{
	if (win)
	{
		std::cout << "GG well play ta gagne" << RESETCOLOR << std::endl;
		return;
	}
	std::cout << "Cheh ta perdu" << RESETCOLOR << std::endl;

}

void MainLoop()
{
	Grid grid;
	Grid* gridPtr = &grid;

	srand(time(NULL));

	CreateGrid(gridPtr);

	int row = 0;
	int col = 0;
	bool isPlaying = true;
	bool win = false;

	//x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\nx :");
	//y = AskInt(0, gridPtr->line, "y : ");
	KeyInput(gridPtr, &row, &col,false);


	gridPtr->cellTab[row][col].isAMine = false;
	gridPtr->cellTab[row][col].isReveal = true;

	PlaceMine(gridPtr);

	UpdateCells(gridPtr);

	RevealCase(gridPtr, row, col);

	while (isPlaying)
	{
		DisplayGrid(gridPtr, row, col, false, false);

		//while (AskInt(0, 1, "Veux tu placer un drapeau ? (0 = non, 1 = oui)"))
		//{
		//	x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\n");
		//	y = AskInt(0, gridPtr->line, "y :");

		//	gridPtr->cellTab[x][y].isFlag = true;
		//	DisplayGrid(gridPtr, x, y);
		//}

		while (KeyInput(gridPtr, &row, &col, true))
		{	
			gridPtr->cellTab[row][col].isFlag = !gridPtr->cellTab[row][col].isFlag;


			DisplayGrid(gridPtr, row, col, true, false);
		}

		KeyInput(gridPtr, &row, &col, false);

		//x = AskInt(0, gridPtr->column, "Rentrer les coordonnees :\nx :");
		//y = AskInt(0, gridPtr->line, "y :");

		gridPtr->cellTab[row][col].isReveal = true;

		RevealCase(gridPtr, row, col);

		if (gridPtr->cellTab[row][col].isAMine)
		{
			win = false;
			isPlaying = false;
		}
		else if (CheckWin(gridPtr))
		{
			win = true;
			isPlaying = false;
		}
	}
	RevealGrid(gridPtr);
	DisplayGrid(gridPtr, row, col, false,win);
	DisplayWin(win);
}

void Game() {
	bool playing = true;
	while (playing)
	{
		MainLoop();
		if (!AskInt(0, 1, "Veux tu rejouer ? (0 = non, 1 = oui)"))
		{
			playing = false;
		}
		system("cls");
	}
}


int main()
{
	Game();
	return 0;
}


