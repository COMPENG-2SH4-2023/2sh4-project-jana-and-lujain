#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
int i, j; 

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
objPos randomSymbols[2]; 
objPos posPlayer;

Player* playerPtr; 
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

    while(exitFlag == false)  
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
    exitFlag = false;

    gameMechs = new GameMechs(); 
    
    playerPtr = new Player(gameMechs); 
    //GameMechs gameMechsOBJ;
    //playerPtr = new Player(&gameMechsOBJ); 
    playerPtr->getPlayerPos(posPlayer);//we update the posPlayer instances with the player initial position and the symbol


}

void GetInput(void)
{
    char this_input =0;
    if (MacUILib_hasChar()){
    this_input= MacUILib_getChar(); 
    
    if (this_input== 'w' || this_input == 'd' || this_input == 's'|| this_input == 'a' || this_input == 'W' || this_input == 'D'|| this_input == 'S' || this_input == 'A' || this_input == '+' || this_input == '-'){
        gameMechs->setInput(this_input); //apply the input recieved to the gameMechs
        } 
    else if ( this_input ==  ' '){ 
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

    randomSymbols[0].setObjPos(5, 6, 'J');
    randomSymbols[1].setObjPos(7,4, 'L'); 

    int i;
    for( i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++) {
            layout[i][j]=' ';
        }
        layout[i][30]='\n';
        layout[i][31]='\0';
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


    layout[randomSymbols[0].y][randomSymbols[0].x] = randomSymbols[0].symbol;    
    layout[randomSymbols[1].y][randomSymbols[1].x] = randomSymbols[1].symbol;    


    playerPtr->getPlayerPos(posPlayer);//updating the instance posPlayer with the player's position
    layout[posPlayer.y][posPlayer.x] = posPlayer.symbol;    


    //Finally printing out the updated layout for it to be applied on the terminal screen 
    for( i=0;i<HEIGHT;i++) 
    {
        MacUILib_printf(layout[i]);
    }

    //MacUILib_printf("Score: %d", gameMechsOBJ.getScore()); 
    


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
