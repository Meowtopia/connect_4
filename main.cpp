#include "FEHLCD.h"
#include "FEHUtility.h"
#include <iostream>
#include <string>
#include <vector>



void drawMenu ()
{
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("1P", 155, 60);
    LCD.WriteAt("2P", 155, 95);
    LCD.WriteAt("RECORDS", 130, 130);
    LCD.WriteAt("INSTRUCTIONS", 95, 165);
    LCD.WriteAt("CREDITS", 130, 200);
}
int menuCheck()
{

    float x_position, y_position;
    float x_trash, y_trash;

    while(!LCD.Touch(&x_position,&y_position)) {};
    while(LCD.Touch(&x_trash,&y_trash)) {};
    //player 1 and 2 detection x positions
    if (x_position > 120 && x_position < 190 )
    {
        LCD.Clear(BLACK);
        //player 1
        if (y_position > 50 && y_position < 85)
        {
            //LCD.WriteLine("Play game here");
            return 1;
        }
        //player 2
        else if (y_position > 85 && y_position < 120)
        {
            //LCD.WriteLine("player 2");
            return 2;
        }

    }

    //records, instructions, and credits detections
    if (x_position > 85 && x_position < 240)
    {
        LCD.Clear(BLACK);
        //records
        if (y_position > 120 && y_position < 155)
        {
            //LCD.WriteLine("recrds");
            return 3;
        }

        //instructions
        else if (y_position > 155 && y_position < 190)
        {
            //LCD.WriteLine("instructions");
            return 4;
        }

        //credits
        else if (y_position > 190 && y_position < 230)
        {
            //LCD.WriteLine("credits");
            return 5;
        }
        
    }
return 0;
}

void drawInstructions()
{
    LCD.WriteAt("", 0, 30);
LCD.WriteAt("Instructions: ", 0, 50);
LCD.WriteAt("1.Select desired chip", 0, 70);
LCD.WriteAt("design.", 0, 90);
LCD.WriteAt("2.Player 1 will go first.", 0, 110);
LCD.WriteAt("3.Place chip on board.", 0, 130);
LCD.WriteAt("4.The game will continue", 0, 150);
LCD.WriteAt("until there are four chips", 0, 170);
LCD.WriteAt("in one path.", 0, 190);
}

void drawCredits()
{
    LCD.WriteAt("Makers: Ross and Ayyoub", 60, 50);
}

int backButton ()
{
    LCD.WriteAt("Back", 5, 5);

    float x_position, y_position;
    float x_trash, y_trash;

    while(!LCD.Touch(&x_position,&y_position)) {};
    while(LCD.Touch(&x_trash,&y_trash)) {};

    //backbutton detection
    if (x_position < 50 && y_position < 30)
    {
        return 1;
    }
    return 0;

}



int main() {
    // Infinite loop so the stoplights run until the program is closed
    
    drawMenu();

    //check for menu
    int menucheck = 0;
while(true)
{
    
    LCD.ClearBuffer();

    while (menucheck == 0)
    {
        
        drawMenu();
        menucheck = menuCheck();
    }
    //LCD.Clear();
    while (menucheck == 1)
    {
        LCD.WriteAt("Play game here", 95, 165);
        if (backButton() == 1)
        {
            LCD.Clear();
            menucheck = 0;
        }
        
    }
    //
    while (menucheck == 2)
    {
        LCD.WriteAt("Play game here", 95, 165);
        if (backButton() == 1)
        {
            LCD.Clear();
            menucheck = 0;
        }
        
    }

    while (menucheck == 3)
    {
        
        LCD.WriteAt("Single Player: ", 0, 30);
        LCD.WriteAt("Player 1 Wins: 2", 10, 50);
        LCD.WriteAt("Player 2 Wins: 40 ", 10, 70);
        LCD.WriteAt("Multiplayer: ", 0, 100);
        LCD.WriteAt("Player 1 Wins: 1", 10, 120);
        LCD.WriteAt("Player 2 Wins: 4", 10, 140);
        if (backButton() == 1)
        {
            LCD.Clear();
            menucheck = 0;
        }
        
    }

    while (menucheck == 4)
    {
        //show instructions
       drawInstructions();
        if (backButton() == 1)
        {
            LCD.Clear();
            menucheck = 0;
        }
        
    }

    while (menucheck == 5)
    {
       
        if (backButton() == 1)
        {
            LCD.Clear();
            menucheck = 0;
        }
        
    }

    
    

   
    //LCD.WriteLine("The screen was under pressure");
    //LCD.Write("At x coordinate: ");
    //LCD.WriteLine(x_position);
    //LCD.Write("At y coordinate: ");
    //LCD.WriteLine(y_position);

   LCD.Update();

}
    return 0;
}