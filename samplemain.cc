/*****************************************************
This is a sample of what the main should like for the second phase of 
the Checkers game.The only change is that the game now announces a 
winner.
	John Dolan	Ohio University		Fall 2018
*************************************************************/
#include<iostream>
#include "game.h"
#include "checkers.h"

using namespace std;
using namespace main_savitch_14;


int main(){
    checkers mygame;
	game::who winner;
	winner = mygame.play();
	if (winner == game::HUMAN)
		std::cout<<"Player 1 Wins";
	else
		std::cout<<"Player 2 Wins";
return 0;
}
