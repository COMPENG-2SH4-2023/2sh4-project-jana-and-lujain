#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        bool loseFlag; //boolen flag recoding whether the player has lost the game 
        int score; // hoding the current score of the player

        objPos foodPos; //holding the most recently generated food position and its ASCII symbol

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); //destructor

        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        bool getLoseFlagStatus();
        void setLoseFlagStatus(bool status);

        int getScore(); // getter method for the game score
        void incrementScore(); // specialized stter for the score field

        //Random Food Generation
        void generateFood(objPos blockOff); 
        void getFoodPos(objPos &returnPos); 

      

};

#endif