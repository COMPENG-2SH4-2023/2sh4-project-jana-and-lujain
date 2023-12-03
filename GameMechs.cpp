#include "GameMechs.h"

GameMechs::GameMechs()
{
    exitFlag = false;
    boardSizeX= 30; 
    boardSizeY = 15; 
    

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
