/*********************************************************
	This is the implementation file for the child class
    "checkers". This file contains the logic for the functions
    listed in the declaration file, "checkers.h".
    The files necessary for this file are 
    checkers.h

    Kyle Reynolds           Fall 2020
**********************************************************/

#include "checkers.h"
using namespace std;
namespace main_savitch_14{



    checkers::checkers(){
            board_data[rows][columns];
        }

        checkers::who checkers::winning() const{
            int player_one_total = 0;
            int player_two_total = 0;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(board_data[i][j].is_black()){
                        player_one_total++;
                    } else if(board_data[i][j].is_red()){
                        player_two_total++;
                    } else {

                    }
                }
            }
            if(player_one_total == player_two_total){
                return NEUTRAL;
            } 
            return(player_one_total > player_two_total) ? HUMAN : COMPUTER;
        }

        void checkers::display_status()const{
            cout << B_BLACK << "                              " << RESET << endl;
            cout << B_BLUE << " " << B_BLUE << "   A  B  C  D  E  F  G  H    " << B_BLACK << "     " << RESET << endl;
            for(int i = 0; i < rows; i++){
                cout << B_BLUE << " " << B_BLUE << i+1 << " " << RESET;
                for(int j = 0; j < columns; j++){
                    if((i+j)%2 == 0)
                        cout << B_BLACK << "   " << RESET;
                    else if ((!board_data[i][j].is_red()) && (!board_data[i][j].is_black()))
                        cout << B_WHITE << "   " << RESET;
                    else if (board_data[i][j].is_king() && board_data[i][j].is_red())
                        cout << B_WHITE << RED << " K " << RESET;
                    else if (board_data[i][j].is_red())
                        cout << B_WHITE << RED << " O " << RESET;
                    else if (board_data[i][j].is_king() && board_data[i][j].is_black())
                        cout << B_WHITE << BLACK << " K " << RESET;  
                    else if (board_data[i][j].is_black())
                        cout << B_WHITE << BLACK << " 0 " << RESET;
                }
                cout << B_BLUE << " " << B_BLUE << i+1 << " " << RESET;
                cout << endl;
            }
            cout << B_BLUE << " " << B_BLUE << "   A  B  C  D  E  F  G  H    " << B_BLACK << "     " << RESET << endl;
        }

        void checkers::restart(){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){

                    if ((i == 0) && (j == 1 || j == 3 || j == 5 || j == 7))
                    { 
                        board_data[i][j].set_red();
                    }
                    else if (i == 1 && (j == 0 || j == 2 || j == 4 || j == 6))
                    {
                        board_data[i][j].set_red();
                    }
                    else if (i == 2 && (j == 1 || j == 3 || j == 5 || j==7))
                    {
                        board_data[i][j].set_red();
                    }
                    else if (i == 5 && (j == 0 || j == 2 || j == 4 || j == 6))
                    {
                        board_data[i][j].set_black();
                    }
                    else if (i == 6 && (j == 1 || j == 3 || j == 5 || j == 7))
                    {
                        board_data[i][j].set_black();
                    }
                    else if (i == 7 && (j == 0 || j == 2 || j == 4 || j == 6))
                    {
                        board_data[i][j].set_black();
                    }
                    else 
                    { 
                        board_data[i][j].set_none();
                    }
                    if(board_data[i][j].is_king()){
                        board_data[i][j].dead_king();
                    }   
                }
            }
            game::restart();
        }


        /**
        POSSIBLE CASES FOR IS_LEGAL

        -BEFORE ANY PIECE CAN MOVE, NEED TO DEETERMINE IF THE PIECE IS ABLE TO JUMP.
        -IF THE PIECE CAN JUMP, IT WILL JUMP.

        -AFTER, NEED TO CHECK IF THE SPACE IN QUESTION IS BLOCKED OR NOT.

        -RED PIECE MOVES UP ONE, LEFT ONE		-- up_left
        -RED PIECE MOVES UP ONE, RIGHT ONE		-- up_right
        -BLACK PIECE MOVES UP ONE, LEFT ONE		-- down_left
        -Black PIECE MOVES UP ONE, RIGHT ONE	-- down_right

        -combine all for easier time -- into is_jump_legal();

        -RED PIECE WILL JUMP	//IF THERE IS A PIECE (UP AND LEFT, UP AND RIGHT) AND NO PIECE (UP AND LEFT, UP AND RIGHT)
        -BLACK PIECE WILL JUMP

        -RED PIECE WILL DOUBLE JUMP
        -BLACK PIECE WILL DOUBLE JUMP

        -RED KING WILL BE HAVE DIFFERENT LEGAL MOVES THAN RED PIECE	(COULD MOVE UP LEFT, UP RIGHT, DOWN LEFT, DOWN RIGHT)
        -BLACK KING WILL BE HAVE DIFFERENT LEGAL MOVES THAN RED PIECE	(COULD MOVE UP LEFT, UP RIGHT, DOWN LEFT, DOWN RIGHT)



        */


        bool checkers::is_legal(const string& move)const{

            if(move[0]  < 'A' || (move[0]) > 'H'){    	                //the column doesnt exist
                return false;
            }

            if(move[1] < '1' || move[1] > '8'){     					//the row does not exist
                return false;
            } 

            if(move[2] < 'A' || (move[2]) > 'H'){     	            //the column does not exist
                return false;
            }

            if(move[3] < '1' || move[3] > '8'){    						//the row does not exist
                return false;
            }

            if(is_jump_available()){ 
                cout << "jumping" << endl;           //if a jump is available -- it will return true only if the jump is legal
                return(is_jump_legal(move));    //checks for jumps before making move
            } else {				          
                cout << "moving" << endl;  // else it will return true only if the move is legal
                return(is_move_legal(move));
            }
        }


    void checkers::make_move(const string& move){
        int i, j, x, y = 0;
        int counter = 0;
        while(move[counter] != '\0'){       //when move[counter] != NULL -- move[4] will == NULL , so += 2, for conversion and move;

            if(counter == 0){
                checkers::convert_start(move, i, j);
                checkers::convert_end(move, x, y);
                counter += 2;
            } else {
                checkers::convert_jump(move, x, y, counter);
            }   

            if( board_data[i][j].is_black() && ((i-1 == x) || (i+1 == x)) && ((j+1 == y) || (j-1 == y)) ){    //if input is legal
                board_data[x][y].set_black();       //set new space to black
                if(board_data[i][j].is_king()){     //if the piece was a king, need to set it to king for next display
                    board_data[x][y].set_king();    
                }
                board_data[i][j].set_none();        //set old position to none
                if(!board_data[x][y].is_king() && x == 0){      //if the piece reached the end of the board set its status to king
                    board_data[x][y].set_king();        
                }
                counter += 2;               //increment
            }

            if((board_data[i][j].is_red()) && (i - 1 == x || i + 1 == x) && (j+1 == y || j-1 == y)){    //if input is legal
                board_data[x][y].set_red();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();
                if(!board_data[x][y].is_king() && x == 7){
                    board_data[x][y].set_king();
                }
                counter += 2;
            }	

            if(board_data[i][j].is_black() && (i-2 == x) && (j+2 == y)){       //black piece jumping top right
                board_data[x][y].set_black();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();
                board_data[i-1][j+1].set_none();
                if(!(board_data[x][y].is_king()) && x == 0){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            }
            
            if(board_data[i][j].is_black() && (i-2 == x) && (j-2 == y)){    //black piece jumping top left
                board_data[x][y].set_black();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();
                board_data[i-1][j-1].set_none();
                if(!(board_data[x][y].is_king()) && (x==0)){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            } 

            if(board_data[i][j].is_red() && (i+2 == x) && (j+2 == y)){      //red piece jumping bottom right
                board_data[x][y].set_red();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();
                board_data[i+1][j+1].set_none();
                if(!(board_data[x][y].is_king()) && (x==7)){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            } 
            
            if(board_data[i][j].is_red() && (i+2 == x) && (j-2 == y)){      //red piece jumping bottom left
                board_data[x][y].set_red();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();
                board_data[i+1][j-1].set_none();
                if(!(board_data[x][y].is_king()) && (x==7)){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            } 
                    
            if(board_data[i][j].is_king() && board_data[i][j].is_black() && (i+2 == x) && (j+2 == y)){          //black king jumping bot right
                board_data[x][y].set_black();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();        //sets where original pos for king was to none
                board_data[i+1][j+1].set_none();    //set where the piece taken was to none
                if(!(board_data[x][y].is_king()) && x == 0){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            }

            if(board_data[i][j].is_king() && board_data[i][j].is_black() && (i+2 == x) && (j-2 == y)){          //black king jumping bot left
                board_data[x][y].set_black();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();        //sets where original pos for king was to none
                board_data[i+1][j-1].set_none();    //set where the piece taken was to none
                if(!(board_data[x][y].is_king()) && x == 0){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            }

            if(board_data[i][j].is_king() && board_data[i][j].is_red() && (i-2 == x) && (j+2 == y)){        //red king jumping top right
                board_data[x][y].set_red();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();        //sets kings original pos to none
                board_data[i-1][j+1].set_none();    // sets piece taken by king to none
                if(!board_data[x][y].is_king() && (x == 7)){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            }   

             if(board_data[i][j].is_king() && board_data[i][j].is_red() && (i-2 == x) && (j-2 == y)){        //red king jumping top left
                board_data[x][y].set_red();
                if(board_data[i][j].is_king()){
                    board_data[x][y].set_king();
                }
                board_data[i][j].set_none();        //sets kings original pos to none
                board_data[i-1][j-1].set_none();    // sets piece taken by king to none
                if(!board_data[x][y].is_king() && (x == 7)){
                    board_data[x][y].set_king();
                    game::make_move(move);
                    return;
                }
                i = x;
                j = y;
                counter += 2;
                continue;
            }



        }
        game::make_move(move);
    }


    void checkers::convert_start(const std::string& move, int& i, int& j)const{
        j = move[0] - 'A';
        i = move[1] - '1';
    }

     void checkers::convert_start(const std::string& move, int& i, int& j){
        j = move[0] - 'A';
        i = move[1] - '1';
    }

    void checkers::convert_end(const std::string& move, int& x, int& y)const{
        y = move[2] - 'A';
        x = move[3] - '1';
    }

    void checkers::convert_end(const std::string& move, int& x, int& y){
        y = move[2] - 'A';
        x = move[3] - '1';
    }


    void checkers::convert_jump(const std::string& move, int& x, int& y, int& counter)const{     
        for(int a = counter; a < (counter+2); a++){
            if(move[a] == '1'){
                x = 0;
            }
            if(move[a] == '2'){
                x = 1;
            }
            if(move[a] == '3'){
                x = 2;
            }
            if(move[a] == '4'){
                x = 3;
            }
            if(move[a] == '5'){
                x = 4;
            }
            if(move[a] == '6'){
                x = 5;
            }
            if(move[a] == '7'){
                x = 6;
            }
            if(move[a] == '8'){
                x = 7;
            }
            if(move[a] == 'A'){
                y = 0;
            }
            if(move[a] == 'B'){
                y = 1;
            }
            if(move[a] == 'C'){
                y = 2;
            }
            if(move[a] == 'D'){
                y = 3;
            }
            if(move[a] == 'E'){
                y = 4;
            }
            if(move[a] == 'F'){
                y = 5;
            }
            if(move[a] == 'G'){
                y = 6;
            }
            if(move[a] == 'H'){
                y = 7;
            }
        }
    }

    void checkers::convert_jump(const std::string& move, int& x, int& y, int& counter){     
        for(int a = counter; a < (counter+2); a++){
            if(move[a] == '1'){
                x = 0;
            }
            if(move[a] == '2'){
                x = 1;
            }
            if(move[a] == '3'){
                x = 2;
            }
            if(move[a] == '4'){
                x = 3;
            }
            if(move[a] == '5'){
                x = 4;
            }
            if(move[a] == '6'){
                x = 5;
            }
            if(move[a] == '7'){
                x = 6;
            }
            if(move[a] == '8'){
                x = 7;
            }
            if(move[a] == 'A'){
                y = 0;
            }
            if(move[a] == 'B'){
                y = 1;
            }
            if(move[a] == 'C'){
                y = 2;
            }
            if(move[a] == 'D'){
                y = 3;
            }
            if(move[a] == 'E'){
                y = 4;
            }
            if(move[a] == 'F'){
                y = 5;
            }
            if(move[a] == 'G'){
                y = 6;
            }
            if(move[a] == 'H'){
                y = 7;
            }
        }
    }
    

    


    bool checkers::is_jump_available()const{
        for (int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if((moves_completed() % 2) == 0){		//denoting first player
                    if(board_data[i][j].is_black()){	// checking for jump available in black pieces
                        if(board_data[i-1][j-1].is_red() && board_data[i-2][j-2].is_none() && (j-2 >= 0)){  
                            return true;
                        }	
                        if( (board_data[i-1][j+1].is_red()) && (board_data[i-2][j+2].is_none()) && (j+2 < 8) ){
                            return true;
                        }
                        if(board_data[i][j].is_king()){		// jumps in kings case
                            if(board_data[i+1][j-1].is_red() && board_data[i+2][j-2].is_none()){
                                return true;
                            }
                            if(board_data[i+1][j+1].is_red() && board_data[i+2][j+2].is_none()){
                                return true;
                            }
                        }
                    }
                }
                if((moves_completed() % 2) == 1){	//denoting second player
                    if(board_data[i][j].is_red()){		//checking for jump available in red pieces
                        if(board_data[i+1][j-1].is_black() && board_data[i+2][j-2].is_none() && (j-2 >= 0)){
                            return true;
                        } 
                        if(board_data[i+1][j+1].is_black() && board_data[i+2][j+2].is_none() && (j+2 <8)){
                            return true;
                        }
                        if(board_data[i][j].is_king()){
                            if(board_data[i-1][j-1].is_black() && board_data[i-2][j-2].is_none()){
                                return true;
                            }
                            if(board_data[i-1][j+1].is_black() && board_data[i-2][j+2].is_none()){
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }


    bool checkers::jump_up_left(const std::string& move) const {
        int i, j, x, y = 0;
        checkers::convert_start(move, i, j);
        checkers::convert_end(move, x, y);
        if(moves_completed() % 2 == 0 && board_data[i][j].is_black() && board_data[i-1][j-1].is_red() && board_data[i-2][j-2].is_none() && ((i-2) == x && (j-2) == y)){
            return true;
        }
        return false;
    }

    bool checkers::jump_up_right(const std::string& move)const{
        int i, j, x, y = 0;
        checkers::convert_start(move, i, j);
        checkers::convert_end(move, x, y);
        if(moves_completed() % 2 == 0 && board_data[i][j].is_black() && board_data[i-1][j+1].is_red() && board_data[i-2][j+2].is_none() && ((i-2) == x && (j+2) == y)){
            return true;
        }
        return false;
    }

    bool checkers::jump_down_left(const std::string& move)const{
        int i, j, x, y = 0;
        checkers::convert_start(move, i, j);
        checkers::convert_end(move, x, y);
        if(moves_completed() % 2 == 1 && board_data[i][j].is_red() && board_data[i+1][j-1].is_black() && board_data[i+2][j-2].is_none() && ((i+2) == x && (j-2) == y)){
            return true;
        }
        return false;
    }

    bool checkers::jump_down_right(const std::string& move)const{
        int i, j, x, y = 0;
        checkers::convert_start(move, i, j);
        checkers::convert_end(move, x, y);
        if(moves_completed() % 2 == 1 && board_data[i][j].is_red() && board_data[i+1][j+1].is_black() && board_data[i+2][j+2].is_none() && ((i+2) == x && (j+2) == y)){
            return true;
        }
        return false;
    }

    bool checkers::king_jumps(const std::string& move)const{
        int i, j, x, y = 0;
        checkers::convert_start(move, i,j);
        checkers::convert_end(move, x, y);
        if(board_data[i][j].is_king()){
            if(board_data[i][j].is_red()){
                if(board_data[i+1][j+1].is_black() && board_data[i+2][j+2].is_none() && ((i+2 == x) && (j+2 == y)))   //down right
                    return true;
                if(board_data[i+1][j-1].is_black() && board_data[i+2][j-2].is_none() && ((i+2 == x) && (j-2 == y)))   //down left
                    return true;
                if(board_data[i-1][j+1].is_black() && board_data[i-2][j+2].is_none() && ((i-2 == x) && (j+2 == y)))   //up right
                    return true;
                if(board_data[i-1][j-1].is_black() && board_data[i-2][j-2].is_none() && ((i-2 == x) && (j-2 == y)))   //up left
                    return true;
            }else if(board_data[i][j].is_black()){
                if(board_data[i+1][j+1].is_red() && board_data[i+2][j+2].is_none() && ((i+2 == x) && (j+2 == y)))     //down right
                    return true;
                if(board_data[i+1][j-1].is_red() && board_data[i+2][j-2].is_none() && ((i+2 == x) && (j-2 == y)))     //down left
                    return true;
                if(board_data[i-1][j+1].is_red() && board_data[i-2][j+2].is_none() && ((i-2 == x) && (j+2 == y)))     //up right
                    return true;
                if(board_data[i-1][j-1].is_red() && board_data[i-2][j-2].is_none() && ((i-2 == x) && (j-2 == y)))    //up left
                    return true;
            }
        } else {
            return false;
        }
    }



    bool checkers::is_jump_legal(const std::string& move)const{
        if(jump_up_right(move) || jump_up_left(move) || jump_down_right(move) || jump_down_left(move) || king_jumps(move)){
            return true;
        } else {
            return false;
        }
    }



    bool checkers::is_move_legal(const std::string& move) const{
        int i, j, x, y = 0;
        checkers::convert_start(move, i, j);
        checkers::convert_end(move, x, y);

        if((moves_completed()%2) == 0){				//PLAYER ONE -- BLACK PIECES
            if(board_data[i][j].is_black()){
                if((i-1) == x){	//moving 'up' the board
                    if(board_data[i-1][j-1].is_none() && (j-1 == y)){	//moving up to the left
                        return true;
                    }
                    if(board_data[i-1][j+1].is_none() && (j+1 == y)){	//moving up to the right
                        return true;
                    }
                }
                if(board_data[i][j].is_king()){
                    if(i+1 == x){	//allowing for the king to move 'down the board'
                        if(board_data[i+1][j-1].is_none() && (j-1 == y)){	//moving down to the left
                            return true;
                        }
                        if(board_data[i+1][j+1].is_none() && (j+1 == y)){	//moving down to the right
                            return true;
                        }
                    }		
                }
            }
        }
        if((moves_completed()%2) == 1){		//PLAYER TWO -- RED PIECES     
            if(board_data[i][j].is_red()){
                if((i+1)==x){	//allowing the red pieces to move 'down' the board
                    if(board_data[i+1][j-1].is_none() && j-1 == y){	//moving down to the left
                        return true;
                    }
                    if(board_data[i+1][j+1].is_none() && j+1 == y){	//moving down to the right
                        return true;
                    }
                }
                if(board_data[i][j].is_king()){
                    if((i-1) == x){	//allowing for the red king to move 'up' the board
                        if(board_data[i-1][j-1].is_none() && (j-1 == y)){	//moving up to the left
                            return true;
                        }
                        if(board_data[i-1][j+1].is_none() && (j+1 == y)){	//moving up to the right
                            return true;
                        }
                    }
                }
            }
        }
        return false; 
    }

    bool checkers::is_game_over()const{
        int player_one_count = 0;
        int player_two_count = 0;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(board_data[i][j].is_black()){            //adds up all pieces for black
                    player_one_count = player_one_count + 1;
                } else if (board_data[i][j].is_red()){      //adds up all pieces for red
                    player_two_count = player_two_count + 1;
                } 
            }
        }

        if(player_one_count == 0 || player_two_count == 0){
            cout << "The game is over, Player one had " << player_one_count << " pieces left. Player two had " << player_two_count << " pieces left." << endl;
            return true;
        } else {
            return false;
        }
    }
}// end of savitch namespace