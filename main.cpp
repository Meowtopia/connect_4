//headers
#include "FEHLCD.h"
#include "FEHUtility.h"
#include <iostream>
#include <string>
#include <vector>


//draws the menu
void drawMenu ()
{
    //set font color
    LCD.SetFontColor(LCD.White);
    //player 1
    LCD.WriteAt("1P", 155, 60);
    //player 2
    LCD.WriteAt("2P", 155, 95);
    //records/stats
    LCD.WriteAt("RECORDS", 130, 130);
    //instruction
    LCD.WriteAt("INSTRUCTIONS", 95, 165);
    //credits
    LCD.WriteAt("CREDITS", 130, 200);
}
//adds interactibility to menu
/*returns 0 if no menu is selected, returns 1 if player 1 is selected
2 if player 2 selected, 3 for records, 4 for instructions, 5 for credits 
*/

int menuCheck()
{
    //holds position of click/tap
    float x_position, y_position;
    float x_trash, y_trash;

    //position of touch
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
    }//ending bracket

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
}//ending bracket

//draws instructions
void drawInstructions()
{
    LCD.WriteAt("How to play Connecticut 4: ", 0, 30);
LCD.WriteAt("Instructions: ", 0, 70);
LCD.WriteAt("Get four in a row'", 0, 110);
LCD.WriteAt("2. The game will now begin. Player 1 will play first.", 0, 150);
LCD.WriteAt("3. To play, the player should select the location on top of the row that they would like the chip to fall into.", 0, 190);
LCD.WriteAt("4. It is now player 2's turn.", 0, 230);
LCD.WriteAt("Objective:", 0, 270);
LCD.WriteAt("The game will continue until four chips are connected in one straight path. The player who accomplishes this feat first is victorious.", 0, 310);
}

//draw credits
void drawCredits()
{
    //we da real
    LCD.WriteAt("Makers: Ross and Ayyoub", 60, 50);
}

//draws back buttons and adds functionality.
/* Returns 1 when back button is pressed
Otherwise returns 0
*/
int backButton ()
{
    //draws back button
    LCD.WriteAt("Back", 5, 5);

    //hold position of touch
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


//int main
int main() {
    // Infinite loop so the stoplights run until the program is closed
    
    //draw initial menu
    drawMenu();

    //check for menu
    int menucheck = 0;

//infinite loop to run program
while(true)
{
    //clear screen
    LCD.ClearBuffer();

    //while no menu element is selected
    while (menucheck == 0)
    {
        drawMenu();
        //checks for menu touch
        menucheck = menuCheck();
    }
    //LCD.Clear();
    //if player 1 selected
    while (menucheck == 1)
    {
        LCD.WriteAt("Play game here", 95, 165);
        //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //go back to main screen
            menucheck = 0;
        }
        
    }
    //plyaer 2 selected
    while (menucheck == 2)
    {
        LCD.WriteAt("Play game here", 95, 165);
        //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //go back to main screen
            menucheck = 0;
        }
        
    }
    //records selected
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
    //if instructions selected
    while (menucheck == 4)
    {
        //show instructions
       drawInstructions();
       //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //go back to main screen
            menucheck = 0;
        }
        
    }
    //if credits selected
    while (menucheck == 5)
    {
        //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //go back to main screen
            menucheck = 0;
        }
        
    }
    //update LCD
   LCD.Update();

}
    //end main
    return 0;
}