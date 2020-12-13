#ifndef SPACE_H
#define SPACE_H
#include "colors.h"

class space{
    public:
        space(){
            color = ""; 
            king = false;
            }      //set color to no value, and set all of the pieces to NOT KING

        void set_king(){
            king = true;
            }
            
        void dead_king(){
            king = false;
            }
            
        bool is_king()const{
            return king;
            }


        void set_red(){
            color = "red";
            }
        void set_black(){
            color = "black";
            }
        void set_none(){
            color = "none";
            king == false;
            }


        bool is_red()const{
            if(color == "red")
                return true;
            else 
                return false;
            }

        bool is_black()const{
            if(color == "black")
                return true;
            else 
                return false;
            }

        bool is_none()const{
            if(color == "none")
                return true;
            else 
                return false;
            }

    private:
        std::string color;
        bool king;
};

#endif