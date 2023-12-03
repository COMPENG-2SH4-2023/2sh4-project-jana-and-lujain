#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(5,5,'*'); //Jana Nofal

    // more actions to be included


}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char c = mainGameMechsRef->getInput();
    if(c != 0)  // if not null character then these evaulations will be excuted
    {
        switch(c)//use switch
        {                      
            case ' ':  // exit // space is also a terminating command
                mainGameMechsRef->setExitTrue();
                break;

            // Add more key processing here
            // Add more key processing here
            // Add more key processing here    
            case 'w'://includes boht lower case and upper case values as input for the direction 
            case 'W':
                switch(myDir) {
                    case LEFT://the original case is left 
                    case STOP:
                    case RIGHT://if the previous case is right then it will switch to up 
                        myDir=UP;
                        //MacUILib_printf("UP\n")
                }
                break;
            case 's':
            case 'S':
                switch(myDir) {
                    case LEFT:
                    case STOP:
                    case RIGHT:
                        myDir=DOWN;
                        //MacUILib_printf("DOWN\n");
                }
                break;
            case 'a':
            case 'A':
                switch(myDir) {
                    case UP:
                    case STOP:
                    case DOWN:
                        myDir=LEFT;
                        //MacUILib_printf("LEFT\n");

                        //no break is iputed here as it will continue to be left until a different command is inputed
                }
                break;
            case 'd':
            case 'D':
                switch(myDir) {
                    case UP:
                    case STOP:
                    case DOWN:
                        myDir=RIGHT;
                        //MacUILib_printf("Right \n"); 
                }
                break;

            default:
                break;
        }
        mainGameMechsRef->setInput(0);//resets input 
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)// based on the direction changed based on the input given before, we then continue on to the switch cases regarding the  mFSMode
    {
        case UP://if command is up, then the y-coordinate of the player will decrese resulting in the symbol going up
            playerPos.y--;
            if(playerPos.y == 0)//if we change it to 1, then the player will wrap around before reaching the edge of the screen diaplayed
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY()-2;//this is the wrap around command that enables the player to go the buttom of the screen once it reaches the top of the screen as it the y-cordinate decreases in value
            }
            break;
        case DOWN:

            playerPos.y++;
            if(playerPos.y== mainGameMechsRef->getBoardSizeY()-1)//same thing here 
            {
                playerPos.y = 1;// resets it to y-coordinate = to 1
            }
            break;
        case LEFT:
            playerPos.x--;//left results in a drecese in value
            if(playerPos.x == 0)// the player reaches the left edge which is a x-coordinate of zero then it will reset the player to 18
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX()-2;// the edge of the screen to the rght
            }
            break;
        case RIGHT:
            playerPos.x++;
            if(playerPos.x==mainGameMechsRef->getBoardSizeX()-1)//edge one unit beyond 
            {
                playerPos.x = 1;//resets to 1
            }
            break;
        default:
            break;
        //TAKE AWAY
            //The player wraps around when it reaches the edge nto the border, but 1 unit beyound it to prevent it from wrapping around before 


     }

}


