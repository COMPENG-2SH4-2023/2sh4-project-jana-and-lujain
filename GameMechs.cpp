#include "GameMechs.h"
#include <cstdlib> //added for the random number generation 

GameMechs::GameMechs()
{
    exitFlag = false;
    loseFlag = false;
    boardSizeX= 30; 
    boardSizeY = 15; 
    score =0; 

    

}

GameMechs::GameMechs(int boardX, int boardY)
{
    //we have no use of copy constructor in the program
}

// do you need a destructor?
GameMechs :: ~GameMechs(){
    //we have no use of this destructor in the program
    //we end up deleting allocated memeory for GameMechs in the Project.cpp in the clean up routine    
}



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;

}

int GameMechs::getBoardSizeX()
{
    
    return boardSizeX;

}

int GameMechs::getBoardSizeY()
{
    
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag= true;

}

void GameMechs::setInput(char this_input)
{
    input = this_input;

}

void GameMechs::clearInput()
{

}

bool GameMechs :: getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs :: setLoseFlagStatus( bool status)
{
    loseFlag = status;
    

}

int GameMechs:: getScore()
{
    return score;

}
void GameMechs:: incrementScore()
{
    score++;
}


void GameMechs::generateFood(objPosArrayList * blockOff)
{
    srand(time(NULL));  // seed the random integer generator

    int valid=0;
    int candidate_x; int candidate_y;
    int i; 

    while(valid == 0 )
    {
        candidate_x = (rand()%(boardSizeX-2)) +1;
        candidate_y = (rand()%(boardSizeY-2)) +1; 
        valid=1;

        //in this for loop we are checking to make sure that the randomly generted coordinates do not over lap any of the player elements
        for(int i=0; i< blockOff->getSize(); i++){
            objPos pos;
            blockOff->getElement(pos, i);
            
            //for this condition: if true, while loop will continue to generate new random coordinates 
            if(candidate_x == pos.x && candidate_y == pos.y)
            {
                valid = 0; 
                break;
            }
        }



        //if the randomly generated coordinates do not over lap any of the players elements(valid =1), the food position will be updated 
        if(valid == 1)
        {
            foodPos.x = candidate_x;
            foodPos.y = candidate_y; 
            foodPos.symbol = 'O'; 
        }

    }


}
void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos); 

}