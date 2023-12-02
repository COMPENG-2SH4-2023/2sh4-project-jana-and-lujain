#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
int i, j; 

//board border layout
char layout[10][22];


//Here we are creating arrays of objPos instances 
//This will be used to implement the board border
objPos borderTop[22];
objPos borderBottom[22];
objPos borderLeft[8];
objPos borderRight[8];
objPos randomSymbols[2];



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
void createBoder(void);


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

}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}
/*
void createBoder() {
    for(int i=0;i< 20; i++) {
        //creates the top and bottom edge of the border
        borderTop[i].setObjPos(i,0, '#');
        borderBottom[i].setObjPos(i,9, '#');
    }
    for(int i=0;i< 8; i++) {
        //Creates the left and right edge of the border
        borderLeft[i].setObjPos(0,i+1, '#');
        borderRight[i].setObjPos(19,i+1, '#');
    }





}
*/



void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    for(int i=0;i< 20; i++) {
        //creates the top and bottom edge of the border
        borderTop[i].setObjPos(i,0, '#');
        borderBottom[i].setObjPos(i,9, '#');
    }
    for(int i=0;i< 8; i++) {
        //Creates the left and right edge of the border
        borderLeft[i].setObjPos(0,i+1, '#');
        borderRight[i].setObjPos(19,i+1, '#');
    }

    randomSymbols[0].setObjPos(5, 6, 'J');
    randomSymbols[1].setObjPos(7,4, 'L'); 

    int i;
    for( i=0;i<10;i++){
        for(int j=0;j<20;j++) {
            layout[i][j]=' ';
        }
        layout[i][20]='\n';
        layout[i][21]='\0';
    }
    
    //setting the layout to the updated border symbols with respont to their postion on the x and y coordinates
    for(i=0;i<20;i++){
        layout[borderTop[i].y][borderTop[i].x]=borderTop[i].symbol;
        layout[borderBottom[i].y][borderBottom[i].x]=borderBottom[i].symbol;
    }
    for(i=0;i<8;i++){
        layout[borderLeft[i].y][borderLeft[i].x]=borderLeft[i].symbol;
        layout[borderRight[i].y][borderRight[i].x]=borderRight[i].symbol;
    }


    layout[randomSymbols[0].y][randomSymbols[0].x] = randomSymbols[0].symbol;    
    layout[randomSymbols[1].y][randomSymbols[1].x] = randomSymbols[1].symbol;     
 
    //Finally printing out the updated layout for it to be applied on the terminal screen 
    for( i=0;i<=9;i++) 
    {
        MacUILib_printf(layout[i]);
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
