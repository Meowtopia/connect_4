//headers
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include <iostream>
#include <string>
#include <vector>
#include "fstream"

using namespace std;

//draws the menu
void drawMenu ()
{
   FEHIMAGE pic1; //draw pic pic
	pic1.Open("connect4pageFEH.pic");
	pic1.Draw(0,0);//draw pic
    //draw cookie
  LCD.SetFontColor(WHEAT);
    LCD.DrawCircle(10,10,10);
LCD.SetFontColor(YELLOW);
    LCD.FillCircle(10,10,10);
    LCD.SetFontColor(RED);
    LCD.DrawPixel(5,5);
    LCD.DrawPixel(2,2);
    LCD.DrawPixel(2,8);
    LCD.DrawPixel(8,4);
    LCD.DrawPixel(3,6);

   
    //set font color
    LCD.SetFontColor(LCD.Black);
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

    LCD.SetFontColor(LCD.White);

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
    LCD.WriteAt("us/programming-syntax/",0,110);
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

class player 
{
    public:
        player(char nm[] = "Player", int wins = 0, int losses = 0, int ties = 0, char theme[] = "normal", int totalPiecesPlaced = 0, bool play = false, int PlayNumber = 0);
        void selectPieceTheme();
        void dropPiece(player*, int playerNumber);
        void updateStats();
        void updateBoard(int column, int playerNumber);
        bool Play;
        int board [20][20];
    private:
        //name
        char Nm[25];
        //stats
        
        int Wins;
        int Losses;
        int Ties;
        char Theme[25];
        int TotalPiecesPlaced;
        
        int playerNumber;
};

class AI 
{
    public:
        AI(int difficulty = 1, int wins = 0, int losses = 0, int ties = 0, int totalPiecesPlaced = 0, int turnCount = 1);
        
        void AIDropPiece(player*);
        void updateStats();
        void setDifficulty();
    private:
        //stats
        int playerNumber;
        int Wins;
        int Losses;
        int Ties;
        int Difficulty;
        int TotalPiecesPlaced;
        int turnCount;
};

void drawBoard(bool passThruHoles)
{
    LCD.SetFontColor(BLUE);
    //7 columns by 6 rows, draws the board
    LCD.FillRectangle(10, 45, 210, 180);
    
    LCD.SetFontColor(WHITE);
     FEHIMAGE bank1,bank2; //draw pic pic
	bank1.Open("P1 bankFEH.pic");
	bank1.Draw(70,225);//draw pic
    bank2.Open("P2 bankFEH.pic");
	bank2.Draw(150,225);//draw pic
    if (!passThruHoles)
    {
    //nested for loop to draw the holes inside the board at equal increments
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            LCD.SetFontColor(WHITE);
            LCD.FillCircle(30 + (28*(i-6)), 63 + (29*(j-6)), 10);
        }
    }
    }
}


void menuTransition(int menucheck, player *p1, player *p2, AI *pc) 
{
    int exit = 0;

    while (exit == 0)
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
        //LCD.WriteAt("Play game here", 10, 60);
        (*p1).selectPieceTheme();
        (*pc).setDifficulty();

        (*p1).Play = true;
        (*p2).Play = false;
        menucheck = 11111;
        exit = 1;
        //if back button selected
    }
    //plyaer 2 selected
    while (menucheck == 2)
    {
        //LCD.WriteAt("Play game here", 95, 165);
        (*p1).selectPieceTheme();
        (*p2).selectPieceTheme();
        (*p1).Play = true;
        (*p2).Play = true;
        
        menucheck = 11111;
        exit = 1;
        //if back button selected
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
}


int checkWin(player *P1, player *P2, int playerNumber)
{
    /*
    |   ->
    8
       6   7  8  9  10 11 12
   6   {0, 0, 0, 0, 0, 0, 0}
   7   {0, 0, 0, 1, 0, 0, 0}
   8   {0, 0, 2, 1, 0, 0, 0}
   9   {0, 0, 1, 2, 1, 0, 0}
   10   {0, 0, 1, 2, 2, 0, 0}
   11   {0, 1, 1, 2, 1, 2, 0}
   ...
    (2, 3), (3, 4), (4, 5), (5, 6)
    */
    //int winCheck = 1;
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
           // LCD.Write((*P1).board[i][j]);
            //LCD.ClearBuffer();
            if ((*P1).board[i][j] == playerNumber)
            {   
                        //top left
                        if ((*P1).board[i-1][j-1] == playerNumber)
                        {
                            if ((*P1).board[i-2][j-2] == playerNumber)
                            {
                                if ((*P1).board[i-3][j-3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        //left
                        
                        else if ((*P1).board[i-1][j] == playerNumber)
                        {
                            
                            if ((*P1).board[i-2][j] == playerNumber)
                            {
                                if ((*P1).board[i-3][j] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        
                        //bottom left
                        else if ((*P1).board[i-1][j+1] == playerNumber)
                        {
                            if ((*P1).board[i-2][j+2] == playerNumber)
                            {
                                if ((*P1).board[i-3][j+3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        //bottom 
                        else if ((*P1).board[i][j+1] == playerNumber)
                        {
                            if ((*P1).board[i][j+2] == playerNumber)
                            {
                                if ((*P1).board[i][j+3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        //bottom right diagonal
                        else if ((*P1).board[i+1][j+1] == playerNumber)
                        {
                            if ((*P1).board[i+2][j+2] == playerNumber)
                            {
                                if ((*P1).board[i+3][j+3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        //right
                        else if ((*P1).board[i+1][j] == playerNumber)
                        {
                            if ((*P1).board[i+2][j] == playerNumber)
                            {
                                if ((*P1).board[i+3][j] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                   // Sleep(5000);
                                } 
                            } 
                        } 
                        //top right
                        else if ((*P1).board[i+1][j-1] == playerNumber)
                        {
                            if ((*P1).board[i+2][j-2] == playerNumber)
                            {
                                if ((*P1).board[i+3][j-3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
                        //top[]
                        else if ((*P1).board[i][j-1] == playerNumber)
                        {
                            if ((*P1).board[i][j-2] == playerNumber)
                            {
                                if ((*P1).board[i][j-3] == playerNumber)
                                {
                                    LCD.Write("WIN");
                                    return playerNumber;
                                    //Sleep(5000);
                                } 
                            } 
                        } 
            }
        }
    }
    return 0;
}
//int main
int main() {
    // Infinite loop so the stoplights run until the program is closed
    //infinite loop to run program
    while(true)
    {
    //draw initial menu
   drawMenu();

    //check for menu

    int menucheck = 0;

    

    player P1("Player 1", 0, 0, 0, " ", 0, 1);
    player P2("Player 2", 0, 0, 0, " ", 0, 2);
    AI opponent;


    // Clear background


    //clear screen
    LCD.ClearBuffer();

    menuTransition(menucheck, &P1, &P2, &opponent);


    LCD.Write("sussy");
    //update LCD
    LCD.Update();
    
    LCD.Clear();

    drawBoard(false);

    bool win = false;
    int winner = 0;
    

    while (winner == 0)
    {
        if (winner == 0)
        {
            (P1).dropPiece(&P1, 1);
            winner = checkWin(&P1, &P2, 1);
        }
        if (P2.Play && winner == 0)
        {
           (P2).dropPiece(&P1, 2); 
           winner = checkWin(&P1, &P2, 2);
           //LCD.Write ("bakka");
        }
        
        else if (winner == 0)
        {
            (opponent).AIDropPiece(&P1);
            winner = checkWin(&P1, &P2, 2);
        }
        
    }
    LCD.Write("Game overe");
    LCD.Write(winner);
    LCD.Write(" wins!!");
    Sleep(5000000);
}
    //end main
    return 0;
}

void AI::AIDropPiece(player *P1)
{
    LCD.Write(Difficulty);
    /*
    |   ->
    8
       6   7  8  9  10 11 12
       1   2  3  4  5  6  7
   6   {0, 0, 0, 0, 0, 0, 0}
   7   {0, 0, 0, 1, 0, 0, 0}
   8   {0, 0, 2, 1, 0, 0, 0}
   9   {0, 0, 1, 2, 1, 0, 0}
   10   {0, 0, 1, 2, 2, 0, 0}
   11   {0, 1, 1, 2, 1, 2, 0}
   ...
    (2, 3), (3, 4), (4, 5), (5, 6)
    */
    if (Difficulty == 1)
    {
        int columnDrop = rand() % (7 + 1 - 1) + 1;
        //LCD.Write(columnDrop);
        (*P1).updateBoard(columnDrop, 2);
    }
    else if (Difficulty == 2)
    {
        
        if (turnCount <= 4)
        {
            LCD.Write(turnCount);
            int columnDrop = rand() % (10 + 1 - 8) + 8;
            LCD.Write(columnDrop);
            (*P1).updateBoard(columnDrop, 2);
            
        }
        if (turnCount > 4)
        {
            for (int i = 6; i < 13; i++)
            {
                for (int j = 6; j < 12; j++)
                {
                    // LCD.Write((*P1).board[i][j]);
                    //LCD.ClearBuffer();
                    if ((*P1).board[i][j] == playerNumber)
                    {   
                                
                        //left
                        if ((*P1).board[i-1][j] == 1)
                        {
                            
                            if ((*P1).board[i-2][j] == 1)
                            {
                                (*P1).updateBoard(i-3, 2);
                            } 
                        } 
                        //right
                        else if ((*P1).board[i+1][j] == 1)
                        {
                            if ((*P1).board[i+2][j] == 1)
                            {
                                (*P1).updateBoard(i+3, 2);
                            } 
                        } 
                        //top[]
                        else if ((*P1).board[i][j-1] == 1)
                        {
                            if ((*P1).board[i][j-2] == 1)
                            {
                                (*P1).updateBoard(i, 2);
                            } 
                        } 
                    }
                }
            }
        }
        ++turnCount;
    }
}

player::player (char nm[], int wins, int losses, int ties, char theme[], int totalPiecesPlaced, bool play, int PlayerNumbers)
{
    strcpy (Nm, nm);
    Wins = wins;
    Losses = losses;
    Ties = ties;
    strcpy(Theme, theme);
    TotalPiecesPlaced = totalPiecesPlaced;
    Play = play;
    PlayerNumbers = PlayerNumbers;
    
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            board [i][j] = 0;
        }
    }
  
}

AI::AI (int difficulty, int wins, int losses, int ties, int totalPiecesPlaced, int turn)
{
    Difficulty = difficulty;
    Wins = wins;
    Losses = losses;
    Ties = ties;
    TotalPiecesPlaced = totalPiecesPlaced;
    turnCount = turn;
}

void AI::setDifficulty()
{
    int exit = 0;

    while (exit == 0)
    {
    LCD.SetFontColor(LCD.Black);
    LCD.FillRectangle(0, 30, 250, 190);

    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Select Difficulty", 90, 110);
    LCD.WriteAt("Easiest", 110, 140);
    LCD.WriteAt("Easy", 110, 160);
    LCD.WriteAt("Normal", 110, 180);
    
    //hold position of touch
    float x_position, y_position;
    float x_trash, y_trash;

    while(!LCD.Touch(&x_position,&y_position)) {};
    while(LCD.Touch(&x_trash,&y_trash)) {};
    
    if (x_position > 105 && x_position < 205)
    {
        if (y_position > 135 && y_position < 157)
        {
            Difficulty = 1;
            exit = 1;
        }
        else if (y_position > 158 && y_position < 177)
        {
            Difficulty = 2;
            exit = 1;
        }
        else if (y_position > 178 && y_position < 200)
        {
            Difficulty = 3;
            exit = 1;
        }
    }
    //LCD.Write(Difficulty);
    }
}


void player::selectPieceTheme()
{
    int exit = 0;
    while (exit == 0)
    {
    LCD.Clear();
    LCD.WriteAt(Nm, 0, 110);
    LCD.WriteAt("Select Theme", 95, 110);
    LCD.WriteAt("Normal", 110, 140);
    LCD.WriteAt("Pizza", 110, 160);
    LCD.WriteAt("Cookies", 110, 180);

    //hold position of touch
    float x_position, y_position;
    float x_trash, y_trash;

    while(!LCD.Touch(&x_position,&y_position)) {};
    while(LCD.Touch(&x_trash,&y_trash)) {};
    
    if (x_position > 105 && x_position < 205)
    {
        if (y_position > 135 && y_position < 157)
        {
            strcpy(Theme, "Normal");
            exit = 1;
        }
        else if (y_position > 158 && y_position < 177)
        {
            strcpy(Theme, "Pizza");
            exit = 1;
        }
        else if (y_position > 178 && y_position < 200)
        {
            strcpy(Theme, "Cookies");
            exit = 1;
        }
    }
    //LCD.Write(Theme);
    }

}

void player::dropPiece(player *P1, int playerNumber)
{
    //hold position of touch
    float x_position, y_position;
    float x_trash, y_trash;
    float x_init;
    float y_init;

    while(!LCD.Touch(&x_position,&y_position)) {
        //LCD.SetFontColor(RED);
        //LCD.FillCircle(x_position, y_position, 5);
    };
    while(LCD.Touch(&x_trash,&y_trash)) {
        
        if (x_init != x_trash || y_init != y_trash)
        {
            //LCD.Write("sus");
            LCD.SetFontColor(BLACK);
            LCD.FillCircle(x_init, y_init, 120);
        }
        LCD.SetFontColor(RED);

        x_init = x_trash;
        y_init = y_trash;

        LCD.FillCircle(x_trash, y_trash, 10);
//LCD.Write("1");
        drawBoard(false);
        (*P1).updateBoard(0, 5);
        Sleep(10);
    };

    x_position = x_init;
    y_position = y_init;

        drawBoard(true);
        
            if (x_position < 226)
            {
                while (y_init < 63)
                {
                 //drawBoard(false);
                LCD.SetFontColor(BLACK);
                LCD.FillCircle(x_init, y_init, 10);

                LCD.SetFontColor(RED);
                LCD.FillCircle(x_init, ++y_init, 10);
            
                drawBoard(false);
                (*P1).updateBoard(0, 5);
                Sleep (10);
                }

                if (x_position < 44)
                {
                    (*P1).updateBoard(1, playerNumber);
                }

                else if (x_position < 72)
                {
                    (*P1).updateBoard(2, playerNumber);
                }

                else if (x_position < 100)
                {
                    (*P1).updateBoard(3, playerNumber);
                }

                else if (x_position < 128)
                {
                    (*P1).updateBoard(4, playerNumber);
                }

                else if (x_position < 156)
                {
                    (*P1).updateBoard(5, playerNumber);
                }

                else if (x_position < 184)
                {
                    (*P1).updateBoard(6, playerNumber);
                }

                else if (x_position < 212)
                {
                    (*P1).updateBoard(7, playerNumber);
                }
            }
            else
            { 
            while (y_init < 220)
            {
                //drawBoard(false);
                LCD.SetFontColor(BLACK);
                LCD.FillCircle(x_init, y_init, 10);

                LCD.SetFontColor(RED);
                LCD.FillCircle(x_init, ++y_init, 10);
            
                drawBoard(false);
                (*P1).updateBoard(0, 5);
                Sleep (10);
            }
            }
    //LCD.Write("sus");

}

void player::updateBoard(int column, int playerNumber)
{
    //nested for loop to draw the holes inside the board at equal increments
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            if (board [i][j] == 1)
            {
                LCD.SetFontColor(RED);
                LCD.FillCircle(30 + (28*(i-6)), 63 + (29*(j-6)), 10);
            }
            if (board [i][j] == 2)
            {
                LCD.SetFontColor(YELLOW);
                LCD.FillCircle(30 + (28*(i-6)), 63 + (29*(j-6)), 10);
            }
        }
    }
    
    int i = 0;
    while (i < 5 && board[column+5][i+7] == 0)
    {
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(30 + (28*(column-1)), 63 + (29*i), 10);
        if (playerNumber == 1)
        {
            LCD.SetFontColor(RED);
        }

        if (playerNumber == 2)
        {
            LCD.SetFontColor(YELLOW);
        }
        
        LCD.FillCircle(30 + (28*(column-1)), 63 + (29*(i+1)), 10);
        Sleep(100);
        ++i;
    }
    
        board[column+5][i+6] = playerNumber;
    
}

