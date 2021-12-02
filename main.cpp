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

//draw credits
void drawCredits()
{
    //we da real
    LCD.WriteAt("Makers: Ross and Ayyoub", 0, 50);
    LCD.WriteAt("Sources:",0,70);
    LCD.WriteAt("https://u.osu.edu/fehprote",0,90);
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




void menuTransition(int menucheck) 
{
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
        LCD.WriteAt("Play game here", 10, 60);
        
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
        drawCredits();
        //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //go back to main screen
            menucheck = 0;
        }
    }
}

class player 
{
    public:
        player(char nm[] = "Player", int wins = 0, int losses = 0, int ties = 0, char theme[] = "normal", int totalPiecesPlaced = 0);
        void selectPieceTheme();
        void dropPiece();
        void updateStats();
    private:
        //name
        char Nm[25];
        //stats
        int Wins;
        int Losses;
        int Ties;
        char Theme[25];
        int TotalPiecesPlaced;
};



//int main
int main() {
    // Infinite loop so the stoplights run until the program is closed
    
    //draw initial menu
    drawMenu();

    //check for menu
    int menucheck = 0;

    player P1;
    player P2;

//infinite loop to run program
while(true)
{
    //clear screen
    LCD.ClearBuffer();

    menuTransition(menucheck);
    //update LCD
   LCD.Update();

}



    //end main
    return 0;
}

player::player (char nm[], int wins, int losses, int ties, char theme[], int totalPiecesPlaced)
{
    strcpy (Nm, nm);
    Wins = wins;
    Losses = losses;
    Ties = ties;
    strcpy(Theme, theme);
    TotalPiecesPlaced = totalPiecesPlaced;
}

/*
player::selectPieceTheme()
{
    LCD.WriteAt("Select Theme", 90, 110);
    LCD.WriteAt("Normal", 110, 140);
    LCD.WriteAt("Pizza", 110, 160);
    LCD.WriteAt("Cookies", 110, 180);
}
*/