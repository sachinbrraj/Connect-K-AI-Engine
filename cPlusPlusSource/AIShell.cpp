#include "AIShell.h"
#include <iostream>
#include<climits>

#include<sys/time.h>

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
	this->eliminateRedudancy = 0;

	//fs.open("Temp.txt",std::fstream::app);
}



AIShell::~AIShell()
{

	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;
	fs.close();
}

vector<Move>  AIShell::getPossibleMoves()
{
	vector<Move> validmoves;
	for (int col =0; col<numCols; col++)
	{
		for (int row =0; row<numRows; row++)
		{
			if (gameState[col][row] == AIShell::NO_PIECE)
			{
				validmoves.push_back(Move(col,row));
			}
		}
	}
	return validmoves;
}


void AIShell::Insert(string gameState, Move move,int score)
{
	string skey = gameState;
	//MoveWithScore tempmove(move.col,move.row,score);
	Move tempmove = move;
	tempmove.score=score;

	sortMoves::iterator it = m_sortMoves.find(skey);
	if(it == m_sortMoves.end())
	{
		set<Move> temp;
		temp.insert(tempmove);
		m_sortMoves[skey]=temp;
	}
	else
	{
		set<Move> temp = m_sortMoves.find(skey)->second;
		temp.insert(tempmove);
		m_sortMoves[skey]=temp;
	}
}

// uncomment below for sorting
//vector<Move> AIShell::GetMoves(int **gameState, bool desc)
//{
	//	string skey = Serialize(gameState);
	//	sortMoves::iterator it = m_sortMoves.find(skey);
	//	if(it == m_sortMoves.end())
	//	{
	//		return getPossibleMoves();
	//	}
	//	else
	//	{
	//		set< Move> temp = m_sortMoves.find(skey)->second;
	//		set<Move>::iterator it= temp.begin();
	//		vector<Move> moves;
	//		for(;it!=temp.end();it++)
	//		{
	//
	//			moves.push_back(*it);
	//		}
	//		//vector<Move> moves(m_sortMoves.find(skey)->second.begin(),m_sortMoves.find(skey)->second.end());
	//		if(desc)
	//		{
	//			moves  = std::reverse(moves.begin(),moves.end());
	//		}
	//		return moves;
	//	}

//}
string AIShell::Serialize(int **gameState)
{
	string sret ="";
	for (int col =0; col<numCols; col++)
	{
		for (int row =0; row<numRows; row++)
		{
			if (gameState[col][row] == AIShell::NO_PIECE)
			{
				sret+="+1";
			}
			else if (gameState[col][row] == AIShell::HUMAN_PIECE)
			{
				sret+="-1";
			}
			if (gameState[col][row] == AIShell::NO_PIECE)
			{
				sret+="0";
			}
		}
	}
	return sret;
}

int AIShell::GetUtilitySouthEast()
{
	int AI_score = 0;
	int Human_score = 0;
	for(int row = k-1; row <  numRows; row++)
	{
		for(int col = 0; col <= numCols -k ; col++)
		{
			int i=0;int cnt=0;
			for (; i < k ; i++)
			{
				if(gameState[col + i] [row - i] == AIShell::HUMAN_PIECE )
				{
					break;
				}
				if(gameState[col + i] [row - i] == AIShell::AI_PIECE )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MAX;
			if(i==k) AI_score++;
			i=0;cnt=0;
			for ( ; i < k ; i++)
			{
				if(gameState[col + i] [row - i] == AIShell::AI_PIECE )
				{
					break;
				}
				if(gameState[col + i] [row - i] == AIShell::HUMAN_PIECE )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MIN;
			if(i==k) Human_score++;
		}
	}
	return AI_score - Human_score;
}

int AIShell::GetUtilityNorthEast()
{
	int AI_score = 0;
	int Human_score = 0;
	for(int row = 0; row <= numRows -k ; row++)
	{
		for(int col = 0; col <= numCols -k ; col++)
		{
			int i=0;int cnt=0;
			for ( ; i < k ; i++)
			{
				if(gameState[col + i] [row + i] == AIShell::HUMAN_PIECE )
				{
					break;
				}
				if(gameState[col + i] [row + i] == AIShell::AI_PIECE )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MAX;
			if(i==k) AI_score++;
			i=0;cnt=0;
			for (; i < k ; i++)
			{
				if(gameState[col + i] [row + i] == AIShell::AI_PIECE )
				{
					break;
				}
				if(gameState[col + i] [row + i] == AIShell::HUMAN_PIECE )
				{
					cnt++;
				}


			}
			if(cnt==k) return INT_MIN;
			if(i==k) Human_score++;
		}
	}
	return AI_score - Human_score;
}

int AIShell::GetUtilityVertical()
{
	int AI_score = 0;
	int Human_score = 0;
	for(int col = 0; col < numCols ; col++)
	{
		for(int row = 0; row <= numRows -k ; row++)
		{
			int i=0;int cnt=0;
			for (; i < k ; i++)
			{
				if(gameState[col] [row + i] == AIShell::HUMAN_PIECE  )
				{
					break;
				}
				if(gameState[col][row+ i] == AIShell::AI_PIECE)
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MAX;
			if(i==k) AI_score++;
			i=0;cnt=0;
			for ( ; i < k ; i++)
			{
				if(gameState[col][row+ i] == AIShell::AI_PIECE)
				{
					break;
				}
				if(gameState[col] [row + i] == AIShell::HUMAN_PIECE  )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MIN;
			if(i==k) Human_score++;
		}
	}
	return AI_score - Human_score;
}


int AIShell::GetUtilityHorizontal()
{
	int AI_score = 0;
	int Human_score = 0;
	for(int row = 0; row < numRows;row++)
	{
		for(int col = 0; col <= numCols -k ; col++)
		{
			int i=0;int cnt=0;
			for (; i < k ; i++)
			{
				if(gameState[col + i] [row] == AIShell::HUMAN_PIECE  )
				{
					break;
				}
				if(gameState[col + i] [row] == AIShell::AI_PIECE )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MAX;
			if(i==k) AI_score++;
			i=0; cnt=0;
			for (; i < k ; i++)
			{
				if(gameState[col + i] [row] == AIShell::AI_PIECE )
				{
					break;
				}
				if(gameState[col + i] [row] == AIShell::HUMAN_PIECE  )
				{
					cnt++;
				}

			}
			if(cnt==k) return INT_MIN;
			if(i==k) Human_score++;
		}
	}
	return AI_score - Human_score;
}
int AIShell::CheckTerminalState()
{
	int ret=0;
	for (int col =0; col<numCols; col++)
	{
		for (int row =0; row<numRows; row++)
		{
			ret = CheckWinLoss(col,row);
			if(ret == INT_MAX || INT_MIN) return ret;
		}
	}
	return 0;
}

int AIShell::CheckWinLoss(int col,int row)
{

	int AIcnt=0;
	int Humancnt=0;

	if(col <= numCols -k)
		for (int i=0; i < k ; i++)
		{
			if(gameState[col + i] [row] == AIShell::AI_PIECE  )
			{
				AIcnt++;
			}
			if(gameState[col + i] [row] == AIShell::HUMAN_PIECE )
			{
				Humancnt++;
			}

		}

	if(AIcnt == k ) return INT_MAX;


	if(Humancnt == k ) return INT_MIN;


	AIcnt=0;
	Humancnt=0;

	if(row <= numRows -k)
		for (int i=0; i < k ; i++)
		{
			if(gameState[col] [row + i] == AIShell::AI_PIECE  )
			{
				AIcnt++;
			}
			if(gameState[col] [row + i] == AIShell::HUMAN_PIECE)
			{
				Humancnt++;
			}

		}

	if(AIcnt == k ) return INT_MAX;

	if(Humancnt == k ) return INT_MIN;



	AIcnt=0;
	Humancnt=0;

	if(row <= numRows-k && col <= numCols -k )
		for (int i=0; i < k ; i++)
		{
			if(gameState[col + i] [row + i]  == AIShell::AI_PIECE  )
			{
				AIcnt++;
			}
			if(gameState[col + i] [row + i]  == AIShell::HUMAN_PIECE)
			{
				Humancnt++;
			}

		}

	if(AIcnt == k ) return INT_MAX;

	if(Humancnt == k ) return INT_MIN;



	AIcnt=0;
	Humancnt=0;

	if(row >= k-1 && col <= numCols -k)
		for (int i=0; i < k ; i++)
		{
			if(gameState[col + i] [row - i]  == AIShell::AI_PIECE  )
			{
				AIcnt++;
			}
			if(gameState[col + i] [row - i]  == AIShell::HUMAN_PIECE)
			{
				Humancnt++;
			}

		}

	if(AIcnt == k ) return INT_MAX;

	if(Humancnt == k ) return INT_MIN;

	return 0;
}


int AIShell::Utility()
{
	int a = GetUtilityHorizontal();
	if( a == INT_MAX || a==INT_MIN) return a;
	int b = GetUtilityVertical();
	if( b == INT_MAX || b==INT_MIN) return b;
	int c = GetUtilityNorthEast();
	if( c == INT_MAX || c==INT_MIN) return c;
	int d = GetUtilitySouthEast();
	if( d == INT_MAX || d==INT_MIN) return d;

	return a+b+c+d;

}

int AIShell::MinValue (int depth,int alpha, int beta, unsigned int timeConstraint)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	unsigned int timeNow = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	//long int timePast = timeNow - timeBegin;

	eliminateRedudancy =  (timeNow >= timeConstraint) ? 1 : 0;

	if(depth <= 0 || eliminateRedudancy == 1) return Utility();

	//int minscore = INT_MAX;
	int maxscore;
	// uncomment below for sorting
	//string sgamestate = Serialize(gameState);
	//vector<Move> validmoves = GetMoves(gameState,true);
	vector<Move> validmoves = getPossibleMoves();
	if(validmoves.size() ==0 ) return Utility();
	vector<Move>::iterator it = validmoves.begin();
	for(; it!=validmoves.end();++it)
	{
		//timeNow = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		gameState[it->col][it->row] = AIShell::HUMAN_PIECE;
		int terminal = CheckTerminalState();
		if(terminal == INT_MIN)
		{
			// uncomment below for sorting
			//Move move(it->col,it->row);
			//Insert(sgamestate,move,INT_MIN);
			gameState[it->col][it->row] = AIShell::NO_PIECE;
			return INT_MIN;
		}
		maxscore = MaxValue(depth-1,alpha,beta,timeConstraint);
		// uncomment below for sorting
		//Move move(it->col,it->row);
		//Insert(sgamestate,move,maxscore);
		beta = (beta < maxscore) ? beta : maxscore;
		gameState[it->col][it->row] = AIShell::NO_PIECE;
		if (alpha >= beta)
		{
			return INT_MIN;
		}
		if(beta==INT_MIN) break;
	}
	return beta;
}

int AIShell::MaxValue (int depth,int alpha, int beta, unsigned int timeConstraint)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	unsigned int timeNow = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	//long int timePast = timeNow - timeBegin;
	eliminateRedudancy =  (timeNow >= timeConstraint) ? 1 : 0;

	if(depth <= 0 || eliminateRedudancy == 1) return Utility();

	//int maxscore = INT_MIN;
	int minscore;
	// uncomment below for sorting
	//string sgamestate = Serialize(gameState);
	//vector<Move> validmoves = GetMoves(gameState,true);
	vector<Move> validmoves = getPossibleMoves();
	if(validmoves.size() ==0 ) return Utility();
	vector<Move>::iterator it = validmoves.begin();
	for(; it!=validmoves.end();++it)
	{
		gameState[it->col][it->row] = AIShell::AI_PIECE;
		int terminal = CheckTerminalState();
		if(terminal == INT_MAX)
		{
			// uncomment below for sorting
			//Move move(it->col,it->row);
			// uncomment below for sorting
			//Insert(sgamestate,move,INT_MAX);
			gameState[it->col][it->row] = AIShell::NO_PIECE;
			return INT_MAX;
		}
		minscore = MinValue(depth-1,alpha,beta,timeConstraint);
		// uncomment below for sorting
		//Move move(it->col,it->row);
		//Insert(sgamestate,move,minscore);
		alpha = (alpha > minscore) ? alpha : minscore;
		gameState[it->col][it->row] = AIShell::NO_PIECE;
		if (alpha >= beta)
		{
			return INT_MAX;
		}
		if(alpha==INT_MAX) break;
	}
	return alpha;
}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2

	vector<Move> validmoves = getPossibleMoves();
	vector<Move>::iterator it = validmoves.begin();
	Move bestMove=validmoves.front();
	bestMove.col=validmoves.front().col;
	bestMove.row=validmoves.front().row;
	//cout<<bestMove.col<<bestMove.row;
	int score;
	int bestScore = INT_MIN;
	//int retScore = INT_MIN;
	Move retMove;
	int depth = 1;
	struct timeval tp;
	gettimeofday(&tp, NULL);
	unsigned int timeNow = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	unsigned int timeConstraint = timeNow +  (TIMER - 1000);
	//		fs<<timeNow<<endl;
	//		fs<<TIMER<<endl;
	//		fs<<timeConstraint<<endl;
	// uncomment below for sorting
	//string sgamestate = Serialize(gameState);
	while(true)
	{
		// uncomment below for sorting
		//validmoves = GetMoves(gameState,true);
		it = validmoves.begin();
		bestScore = INT_MIN;


		for(; it!=validmoves.end();it++)
		{
			gettimeofday(&tp, NULL);
			timeNow = tp.tv_sec * 1000 + tp.tv_usec / 1000;
			if(timeNow >= timeConstraint)
			{
				eliminateRedudancy =1;
				break;
			}
			gameState[it->col][it->row] = AIShell::AI_PIECE;
			int terminal = CheckTerminalState();
			if (terminal == INT_MAX)
			{
				// uncomment below for sorting
				//Move move(it->col,it->row);
				//Insert(sgamestate,move,INT_MAX);
				gameState[it->col][it->row] = AIShell::NO_PIECE;
				retMove.col = it->col;
				retMove.row = it->row;
				return retMove;
			}
			//score = MinValue(depth-1,INT_MIN,INT_MAX);
			score = MinValue(depth-1,INT_MIN,INT_MAX,timeConstraint);

			// uncomment below for sorting
			//Move move(it->col,it->row);
			//Insert(sgamestate,move,score);
			if(score >= bestScore)
			{
				bestScore=score;
				bestMove.col = it->col;
				bestMove.row = it->row;
			}

			gameState[it->col][it->row] = AIShell::NO_PIECE;
		}
		if(eliminateRedudancy == 1) break;
		if(eliminateRedudancy == 0)
		{
			//fs<<"depth="<<depth<<endl;
			//fs<<bestMove.col <<","<<bestMove.row<<endl;
			retMove.col = bestMove.col;
			retMove.row = bestMove.row;
		}
		depth+=1;
	}
	//fs<<"BREAK DEPTH="<<depth<<endl;
	//fs.seekp(ios_base::end);


	return retMove;
}
