#include "cell.hpp"
#include "grid.hpp"


void MainLoop()
{
	Grid grid;
	Grid* gridPtr = &grid;

	srand(time(NULL));

	CreateGrid(gridPtr);

	int x;
	int y;
	bool isPlaying = true;
	bool win = false;

	x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\nx :");
	y = AskInt(0, gridPtr->line, "y : ");

	gridPtr->cellTab[x][y].isAMine = false;
	gridPtr->cellTab[x][y].isReveal = true;

	PlaceMine(gridPtr);

	UpdateCell(gridPtr);

	RevealCase(gridPtr, x, y);

	while (isPlaying)
	{
		DisplayGrid(gridPtr);

		while (AskInt(0, 1, "Veux tu placer un drapeau ? (0 = non, 1 = oui)"))
		{
			x = AskInt(0, gridPtr->column, "Rentrer les coordonnes :\n");
			y = AskInt(0, gridPtr->line, "y :");

			gridPtr->cellTab[x][y].isFlag = true;
			DisplayGrid(gridPtr);
		}

		x = AskInt(0, gridPtr->column, "Rentrer les coordonnees :\nx :");
		y = AskInt(0, gridPtr->line, "y :");

		gridPtr->cellTab[x][y].isReveal = true;

		RevealCase(gridPtr, x, y);

		if (gridPtr->cellTab[x][y].isAMine)
		{
			win = false;
			isPlaying = false;
		}
		if (CheckWin(gridPtr))
		{
			win = true;
			isPlaying = false;
		}
	}
	RevealGrid(gridPtr);
	DisplayGrid(gridPtr);
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


