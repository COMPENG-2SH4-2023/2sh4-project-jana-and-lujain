#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

int i, j; 
char cmd; //for debugging message 
char this_input;//process user input 


//for board border 
#define WIDTH 30
#define HEIGHT 15

//board border layout
char layout[HEIGHT][WIDTH+2];


//Here we are creating arrays of objPos instances 
//This will be used to implement the board border
objPos borderTop[WIDTH];
objPos borderBottom[WIDTH];
objPos borderLeft[HEIGHT-2];
objPos borderRight[HEIGHT-2];
//objPos randomSymbols[2]; 

//replacing the data memeber objPos playerPos with the objPosArrayList* playerPosList
//objPos posPlayer;
objPosArrayList* playerPosList; 

objPos foodPos;

Player* playerPtr; //pointer to Okayer OBject in the global scope 

GameMechs* gameMechs;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
//void createBoder(void);


int main(void)
{

    Initialize();

    while(gameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    this_input =0;
    cmd = 0; 

    //initialize the board border  for it to be printed out in draw screan rotine
    for(int i=0;i< WIDTH; i++) {
        //creates the top and bottom edge of the border
        borderTop[i].setObjPos(i,0, '#');
        borderBottom[i].setObjPos(i,HEIGHT-1, '#');
    }
    for(int i=0;i< HEIGHT-2; i++) {
        //Creates the left and right edge of the border
        borderLeft[i].setObjPos(0,i+1, '#');
        borderRight[i].setObjPos(WIDTH-1,i+1, '#');
    }


    gameMechs = new GameMechs(); //in
    
    playerPtr = new Player(gameMechs); //

    objPosArrayList* pos = playerPtr->getPlayerPos();
    gameMechs->generateFood(pos);//generating food

    gameMechs->getFoodPos(foodPos); //updatting the foodPos instances with the generated food position and food symbol.

    

}

void GetInput(void)
{
    if (MacUILib_hasChar()){
    this_input= MacUILib_getChar(); 
    
    if (this_input== 'w' || this_input == 'd' || this_input == 's'|| this_input == 'a' || this_input == 'W' || this_input == 'D'|| this_input == 'S' || this_input == 'A' || this_input == '+' || this_input == '-'){
        gameMechs->setInput(this_input); //apply the input recieved to the gameMechs
        } 
    else if ( this_input ==  '\t'){ 
        gameMechs->setInput(this_input);
        gameMechs->setExitTrue();
    }
    else{
        this_input = 0; 
    }
    }

}

void RunLogic(void)
{
    playerPtr->updatePlayerDir(); 
    playerPtr->movePlayer();    
}




void DrawScreen(void)
{
    MacUILib_clearScreen();
  
    //assigning each element of the arrays(topBorder, bottomBorder, leftBorder, rightBorder) to the the specificied position and symbol



    int i;
    for( i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++) {
            layout[i][j]=' ';
        }
        layout[i][WIDTH]='\n';
        layout[i][WIDTH+1]='\0';
    }
    
    //setting the layout to the updated border symbols with respect to their postion on the x and y coordinates using the arrays we initialized
    for(i=0;i<WIDTH;i++){
        layout[borderTop[i].y][borderTop[i].x]=borderTop[i].symbol;
        layout[borderBottom[i].y][borderBottom[i].x]=borderBottom[i].symbol;
    }
    for(i=0;i<HEIGHT-2;i++){
        layout[borderLeft[i].y][borderLeft[i].x]=borderLeft[i].symbol;
        layout[borderRight[i].y][borderRight[i].x]=borderRight[i].symbol;
    }


  //  layout[randomSymbols[0].y][randomSymbols[0].x] = randomSymbols[0].symbol;    
  //  layout[randomSymbols[1].y][randomSymbols[1].x] = randomSymbols[1].symbol;    

    objPosArrayList * posArray;
    posArray=playerPtr->getPlayerPos();//updating the instance posPlayer with the player's position

    
    for(i=0;i<posArray->getSize();i++) {
        objPos posPlayer;
        posArray->getElement(posPlayer, i);
        layout[posPlayer.y][posPlayer.x] = posPlayer.symbol;    
    }
    gameMechs->getFoodPos(foodPos); //updatting the foodPos instances with the generated food position and food symbol.

    layout[foodPos.y][foodPos.x] = foodPos.symbol;


    //Finally printing out the updated layout for it to be applied on the terminal screen 
    for( i=0;i<HEIGHT;i++) 
    {
        MacUILib_printf(layout[i]);
    }

    //MacUILib_printf("Score: %d", gameMechsOBJ.getScore()); 
    
    MacUILib_printf("Score: %d\n", gameMechs->getScore());
    MacUILib_printf("======== DEBUG MESSAGE ========\n");
    MacUILib_printf("Board Size: %d x %d \n", gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());

    if(this_input == 'w')
    {
        cmd = 'U'; 
    }
    else if(this_input == 's')
    {
        cmd = 'D';
    }
    else if( this_input == 'a')
    {
        cmd = 'L';
    }
    else if(this_input == 'd')
    {
        cmd = 'R';
    }
    else
    {
        cmd = '0'; 
    }

    MacUILib_printf("Player Direction: %c\n", cmd);

    objPosArrayList * playerCoor;
    playerCoor = playerPtr->getPlayerPos(); 
    objPos coordinates; 
    playerCoor->getHeadElement(coordinates); 
    MacUILib_printf("Player Position: %d, %d\n", coordinates.x, coordinates.y ); 

    if(gameMechs->getExitFlagStatus())
    {
        MacUILib_clearScreen();
        MacUILib_printf("YOU LOST"); 
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST*4); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
    delete gameMechs; 
}
