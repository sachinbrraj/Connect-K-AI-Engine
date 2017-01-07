#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include<vector>
#include<map>
#include<set>
#include "Move.h"
#include<fstream>
using namespace std;

class MoveWithScore
{
public :
	MoveWithScore();
	MoveWithScore(int col, int row, int score)
	{
		m_move.col = col;
		m_move.row = row;
		m_score= score;
	}
	Move m_move;
	int m_score;

};

//struct classcomp
//{
//	bool operator() (const Move& lhs, const Move& rhs) const
//	{return lhs.m_score < rhs.m_score;}
//};

typedef map < string, set< Move > > sortMoves;

// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int TIMER = 5000;

	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;

private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.
	ofstream fs;
	int eliminateRedudancy;
public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	sortMoves m_sortMoves;
	void Insert(string gameState, Move move,int score);
	vector<Move> GetMoves(int **gameState, bool desc);
	string Serialize(int **gameState);
	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
	int CheckBack(vector<int> seq);
	int MinValue (int depth,int alpha, int beta, unsigned int timeDiff);
	int MaxValue (int depth,int alpha, int beta,  unsigned int timeDiff);
	int GetUtilityHorizontal();
	int GetUtilityVertical();
	int GetUtilityNorthEast();
	int GetUtilitySouthEast();
	int CheckWinLoss(int col,int row);
	int CheckTerminalState();
	int Utility();
	vector<Move> getPossibleMoves();
};

#endif //AISHELL_H
