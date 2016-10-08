#include "AIShell.h"
#include <iostream>
#include <cstdlib>

using namespace std;
AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
		
	srand(time(NULL));

	int c = rand()%numCols;
	int r = rand()%numRows;

	while(true)
	{
		if(gameState[c][r] == NO_PIECE)
		{
			Move m(c,r);
			return m;
		}
		else
		{
			c = rand()%numCols;
			r = rand()%numRows;

		}
	}
	Move m(0, 0);
	return m;
	 
}
