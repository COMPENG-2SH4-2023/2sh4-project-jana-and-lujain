#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    incLength= false;
    playerPosList = new objPosArrayList(); 
    objPos playerPos; 
    playerPos.setObjPos(5,5,'*');
    playerPosList->insertHead(playerPos);
    

    // more actions to be included

    //Here we update the objPos foodPos with the posiiton of the generated food for furher use 
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos); 



}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

 objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char c = mainGameMechsRef->getInput();//recording the user input into c
    if(c != 0)  // if not null character then these evaulations will be excuted
    {
        switch(c)//use switch
        {                      
            case ' ':  // exit // space is also a terminating command
                mainGameMechsRef->setExitTrue();
                break;

            case 'w'://includes boht lower case and upper case values as input for the direction 
            case 'W':
                switch(myDir) {
                    case LEFT://the original case is left 
                    case STOP:
                    case RIGHT://if the previous case is right then it will switch to up 
                        myDir=UP;
                }
                break;

            case 's':
            case 'S':
                switch(myDir) {
                    case LEFT:
                    case STOP:
                    case RIGHT:
                        myDir=DOWN;
                }
                break;

            case 'a':
            case 'A':
                switch(myDir) {
                    case UP:
                    case STOP:
                    case DOWN:
                        myDir=LEFT;
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
                }
                break;

            default:
                break;
        }
        mainGameMechsRef->setInput(0);//resets input to avoid double-proccesing  
    }      
}

void Player::movePlayer()
{
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    bool hit= false;

    // PPA3 Finite State Machine logic

    switch(myDir)// based on the direction changed based on the input given before, we then continue on to the switch cases regarding the  mFSMode
    {
        case UP:
            playerPos.y--;//Up will result in a decrease in y coordintes 
            if(playerPos.y == 0)//if we change it to 1, then the player will wrap around before reaching the edge of the screen diaplayed
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY()-2;//wrap around 
            }
            
            playerPosList->insertHead(playerPos); 

            //incLength is a falg that is updated every time food consuption occurs
                //In these conditoins, we make sure to insert the head and keep the tall when food consumption occurs 
                //Otherwise, we continue to insert the head and remove the tail if food cosumption doesn't happen
            if(incLength){
                //occurs when food consumption does occur
                incLength=false;
                //resetting incLength to false 
            } else {
                //occurs when food consuption does not occur
                playerPosList->removeTail();
            }
            break;

        case DOWN:
            playerPos.y++;
            if(playerPos.y== mainGameMechsRef->getBoardSizeY()-1) 
            {
                playerPos.y = 1;// resets it to y-coordinate = to 1
            }

            playerPosList->insertHead(playerPos); 
            if(incLength){
                incLength=false;
            } else {
                playerPosList->removeTail();
            }            
            break;

        case LEFT:
            playerPos.x--;//left results in a drecese in x coordinates
            if(playerPos.x == 0)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX()-2;// the edge of the screen to the rght
            }

            playerPosList->insertHead(playerPos); 
            if(incLength){
                incLength=false;
            } else {
                playerPosList->removeTail();
            }           break;
        case RIGHT:
            playerPos.x++;//right results in increase in x coordinates
            if(playerPos.x==mainGameMechsRef->getBoardSizeX()-1)//edge one unit beyond 
            {
                playerPos.x = 1;//resets to 1
            }

            playerPosList->insertHead(playerPos); 
            if(incLength){
                incLength=false;
            } else {
                playerPosList->removeTail();
            }
            break;
        default:
            break;
        //TAKE AWAY
            //The player wraps around when it reaches the edge nto the border, but 1 unit beyound it to prevent it from wrapping around before 


    }

    if(checkFoodConsumption()){//if food consuption occurs -> the method increasePlayerLength will be called
        increasePlayerLength();
        mainGameMechsRef->generateFood(playerPosList);//generating new food in a new random position after its consumption
    }


    //Checking if snake collids with itself
        //in this for loop we check whether if the head collids with any element in the player 
    for(int i =1; i<playerPosList->getSize(); i++)//start at i =1 bc we don't need to check whether the head collided with itself (i=0 represents the head)
    { 
        objPos arrayPos;
        playerPosList->getElement(arrayPos, i);//updating arrayPos with the i elemnt of the player 

        if(playerPos.x == arrayPos.x && playerPos.y == arrayPos.y)
        {
            //this sets the lose flag and exit flag to true 
            mainGameMechsRef->setExitTrue(); 
            mainGameMechsRef->setLoseFlagStatus(true);
        }

    }
}



bool Player::checkFoodConsumption()
{
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos); 
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);

    //Here we increment the score when food consumption occurs
    if(playerPos.x == foodPos.x && playerPos.y == foodPos.y)
    {
        mainGameMechsRef->incrementScore();
        return true; 
    }

    return false;

}
void Player::increasePlayerLength()
{
    //here we set the incLength flag to true 
    //Therefore, whenever increasePlayerLength is called (which is whenever food consuption occurs) we insert the head without removing the tail
    incLength = true;

}