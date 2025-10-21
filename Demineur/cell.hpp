#pragma once

struct Cell
{
	bool isAMine;
	bool isFlag;
	bool isReveal;
	int mineAround;
};

Cell InitialiseCell();