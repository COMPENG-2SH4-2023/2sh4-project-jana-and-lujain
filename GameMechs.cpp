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

}

// do you need a destructor?
//we can add this desctuctor if i later add dynamic memory allocation
GameMechs :: ~GameMechs(){
    


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

//Lujy Implementation:
bool GameMechs :: getLoseFlagStatus()
{
    return loseFlag;
   // cout << "Debug: Game Lost" << endl;
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
  //  cout << "Score Incermented-Currect Score=" << score << endl;
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
        for(int i=0; i< blockOff->getSize(); i++){
            objPos pos;
            blockOff->getElement(pos, i);

            if(candidate_x == pos.x && candidate_y == pos.y)
            {
                valid = 0; 
                break;
            }
        }




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