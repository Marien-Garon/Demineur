#include "cell.hpp"


Cell InitialiseCell()
{
	Cell newCell;
	newCell.isReveal = false;
	newCell.isFlag = false;
	newCell.isAMine = false;
	return newCell;
}