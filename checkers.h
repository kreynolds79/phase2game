/******************************************************************
	This is the declaration file of the child class "checkers", 
    derived from the parent class "game". This file contains 
    a default constructor, a restart function, a display function,
    a make_move function, and an is_legal function.
    Necessary files:
    game.h
    space.h
    colors.h

    Kyle Reynolds           Fall 2020
******************************************************************/
#ifndef CHECKERS_H
#define CHECKERS_H
#include "game.h"
#include "space.h"
#include "colors.h"
#include <string>
#include <iostream>
#include <queue>

namespace main_savitch_14{

    class checkers : public game{
            public:
                who winning()const;
                checkers();      

				static const int rows = 8;
				static const int columns = 8;
                void restart();                       
                void display_status()const; 
                void make_move(const std::string& move);     
                bool is_legal(const std::string& move)const;      

                //Helper functions for make_move and is_legal
                void convert_start(const std::string& move, int& i, int& j)const;
                void convert_start(const std::string& move, int& i, int& j);
                void convert_end(const std::string& move, int& x, int& y)const;
                void convert_end(const std::string& move, int& x, int& y);
				void convert_jump(const std::string& move, int& x, int& y, int& counter)const;
                void convert_jump(const std::string& move, int& x, int& y, int& counter);

                bool jump_up_left(const std::string& move)const;	//possible jumps
                bool jump_up_right(const std::string& move)const;	//for black pieces or red kings
                bool jump_down_left(const std::string& move)const;	//possible jumps
                bool jump_down_right(const std::string& move)const;	//for red pieces or black kings
                bool king_jumps(const std::string& move)const;

                bool is_jump_available()const;						//returns true if a piece can jump
                bool is_jump_legal(const std::string& move)const;	//determines if the input from user is legal
                bool is_move_legal(const std::string& move) const;	//determines if the input from user is legal
                

                //STUBS
                game* clone()const {}
                void compute_moves(std::queue<std::string>& moves) const{}
                int evaluate() const {}
                bool is_game_over() const;


            private:
                space board_data[rows][columns];
        };

}
#endif