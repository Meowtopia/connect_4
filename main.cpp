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
            LCD.WriteLine("player 2");
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
            LCD.WriteLine("recrds");
            return 3;
        }

        //instructions
        else if (y_position > 155 && y_position < 190)
        {
            LCD.WriteLine("instructions");
            return 4;
        }

        //credits
        else if (y_position > 190 && y_position < 230)
        {
            LCD.WriteLine("credits");
            return 5;
        }
        
    }
return 0;
}

int backButton ()
{
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

    
    

   
    //LCD.WriteLine("The screen was under pressure");
    //LCD.Write("At x coordinate: ");
    //LCD.WriteLine(x_position);
    //LCD.Write("At y coordinate: ");
    //LCD.WriteLine(y_position);

   LCD.Update();

}
    return 0;
}