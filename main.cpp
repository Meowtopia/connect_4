//headers
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//draws the menu
void drawMenu ()
{
   FEHIMAGE pic1; //initialize pic variable
	pic1.Open("cnfinalFEH.pic");
	pic1.Draw(0,0);//draw pic
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
    if (x_position > 210 && x_position < 290 )
    {
        LCD.Clear(BLACK);
        //player 1
        if (y_position > 45 && y_position < 60)
        {
            //LCD.WriteLine("Play game here");
            return 1;
        }
        //player 2
        else if (y_position > 70 && y_position < 85)
        {
            return 2;
        }
    }//ending bracket

    //records, instructions, and credits detections
    if (x_position > 210 && x_position < 290)
    {
        LCD.Clear(BLACK);
        //records
        if (y_position > 95 && y_position < 110)
        {
            return 3;
        }
        //instructions
        else if (y_position > 125 && y_position < 140)
        {
            return 4;
        }
        //credits
        else if (y_position > 160 && y_position < 175)
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

LCD.WriteAt("1.Player 1 will go first.", 0, 70);
LCD.WriteAt("2.Place chip on board.", 0, 90);
LCD.WriteAt("3.The game will continue", 0, 110);
LCD.WriteAt("until there are four chips", 0, 130);
LCD.WriteAt("in one path.", 0, 150);
LCD.WriteAt("4.If the board is filled",0, 170);
LCD.WriteAt("the game ends in a tie.",0, 190);
}//ending bracket

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
/*
class player, contains functions selectPieceTheme that selects piece theme, dropPiece that drops a piece for a player, updateStats that updates stats, updateBoard that updates the board
variables play for player two that is false when single player is selected, board a 20x20 array that mimics a connect 4 board, Nm for name, Wins for losses, Ties for ties, Theme for theme,
TotalPiecesPlaced for total pieces placed, and playerNumber which is 1 for player 1 and 2 for player 2.
*/
class player 
{
    public:
        //calls constructor
        player(char nm[] = "Player", int wins = 0, int losses = 0, int ties = 0, char theme[] = "normal", int totalPiecesPlaced = 0, bool play = false, int PlayNumber = 0);
        //Selects peice theme
        void selectPieceTheme();
        //Drops piece
        void dropPiece(player*, int playerNumber);
        //updates stats
        void updateStats(int wins, int losses, int ties, int totalPiecesPlaced);
        //updates board, takes arguments column for the column that a peice is added to and player number, the player that dropped the piece.
        void updateBoard(int column, int playerNumber);
        //bool checkTopRow(int column);
        //true for player 1, true for player 2 when two player selected, otherwise false.
        bool Play;
        //20x20 board, actually 7x6. The added space is so that checkWin does not give a seg fault or whatever when checking for pieces outside of its dimensions
        int board [20][20];
        int Wins;
        int TotalPiecesPlaced;
        //1 for player 1 and 2 for player 2
        int playerNumber;
    private:
        //name
        char Nm[25];
        //stats   
        int Losses;
        int Ties;
        char Theme[25];
};

class AI 
{
    public:
        AI(int difficulty = 1, int wins = 0, int losses = 0, int ties = 0, int totalPiecesPlaced = 0, int turnCount = 1);
        
        //drop an AI piece, *tries* to utilize AI funcitonality
        int AIDropPiece(player*);
        //update stats
        void updateStats(int wins, int losses, int ties, int totalPiecesPlaced);
        //sets difficulty
        void setDifficulty();
        int Wins;
        int TotalPiecesPlaced;
    private:
        //stats
        //2 for AI
        int playerNumber;
        int Losses;
        int Ties;
        int Difficulty;
        //counts turn count, for AI.
        int turnCount;
};
//draws board
void drawBoard(bool passThruHoles)
{
    LCD.SetFontColor(BLUE);
    //7 columns by 6 rows, draws the board
    LCD.FillRectangle(10, 45, 210, 180);
    
    LCD.SetFontColor(WHITE);
     FEHIMAGE bank1,bank2; //declare bank image variables
	bank1.Open("pxArtFEH.pic");//open bank1 picfile
	bank1.Draw(70,225);//draw bank1
    bank2.Open("yellowbankFEH.pic");//open bank2 picfile
	bank2.Draw(150,225);//draw bank2
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("P1 Bank",225,65);
    LCD.WriteAt("P2 Bank",225,140);
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

//adds interactibility to menu. Calls other functions based on clicking of setting on menu 
void menuTransition(int menucheck, player *p1, player *p2, AI *pc) 
{
    //loop exit condition
    int exit = 0;

    while (exit == 0)
    {
    //while no menu element is selected
    while (menucheck == 0)
    {
        //draws menu
        drawMenu();
        //checks for menu touch
        menucheck = menuCheck();
    }
    //LCD.Clear();
    //if singpleplayer selected, set difficulty of AI and select player 1 theme
    while (menucheck == 1)
    {
        (*pc).setDifficulty();

        //back button
        if (backButton() == 1)
        {
            LCD.Clear();
            //sets menu check to 0, goes back to main screen
            menucheck = 0;
            exit = 1;
            
        }

        (*p1).Play = true;
        //so player 2 does not intrude
        (*p2).Play = false;
        menucheck = 11111;
        //exits loop
        exit = 1;
        //if back button selected
    }
    //2 player multiplayer selected
    while (menucheck == 2)
    {
        //player 1 and player 2 play
        (*p1).Play = true;
        (*p2).Play = true;
        
        //exits loop
        menucheck = 11111;
        exit = 1;
        
    }
    //records selected
    while (menucheck == 3)
    {
        //writes records
        LCD.WriteAt("Player 1 ", 0, 30);
        LCD.WriteAt("Wins: ", 10, 50);
        //player 1 wins
        LCD.WriteAt((*p1).Wins, 75, 50);
        LCD.WriteAt("Total Pieces Placed: ", 10, 70);
        //player 1 total pieces places
        LCD.WriteAt((*p1).TotalPiecesPlaced, 265, 70);
        LCD.WriteAt("Player 2 ", 0, 100);
        LCD.WriteAt("Wins: ", 10, 120);
        //player 2 wins
        LCD.WriteAt((*p2).Wins, 75, 120);
        LCD.WriteAt("Total Pieces Placed: ", 10, 140);
        //player 2 total pieces placed
        LCD.WriteAt((*p2).TotalPiecesPlaced, 265, 140);
        LCD.WriteAt("Computer ", 0, 170);
        LCD.WriteAt("Wins: ", 10, 190);
        //AI wins
        LCD.WriteAt((*pc).Wins, 75, 190);
        LCD.WriteAt("Total Pieces Placed: ", 10, 210);
        //AI total pieces placed
        LCD.WriteAt((*pc).TotalPiecesPlaced, 265, 210);
        
        //if back button selected
        if (backButton() == 1)
        {
            LCD.Clear();
            //sets menu check to 0, goes back to main screen
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

//resets the board before and after games, set all to 0
//player 1 board is used as main board
void resetBoard(player *P1)
{
    //nested for loop to set all elements inside board array to 0
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            (*P1).board [i][j] = 0;
        }
    }
}

//reads the stats file, sets corresponding stat variables of the objects to the stats file.
void readStatsFile(fstream& stats, player *P1, player *P2, AI *Ai)
{
    while (true)
    {
        //reads and sets stat variables from stat file
        stats >> (*P1).Wins >> (*P1).TotalPiecesPlaced >> (*P2).Wins >> (*P2).TotalPiecesPlaced >> (*Ai).Wins >> (*Ai).TotalPiecesPlaced;
        //if EOF is reached, break while loop
        if( stats.eof()) break;
    }
}

//updates the stat file after a game with the new stats of each object after each game
void updateStatsFile(fstream& stats, player *P1, player *P2, AI *Ai)
{
    //clears flag to write to file
    stats.clear();
    //writes new data to file, appends it
    stats << (*P1).Wins << " " << (*P1).TotalPiecesPlaced << " " << (*P2).Wins << " " << (*P2).TotalPiecesPlaced << " " << (*Ai).Wins << " " << (*Ai).TotalPiecesPlaced << " ";
}

//checks for 4 in a row, winner
int checkWin(player *P1, player *P2, int playerNumber)
{
    //loops through entire board, checks for four in a row based on player number input.
    //player number is 1 for player 1, 2 for AI or player 2
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
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
                                    //winner
                                    LCD.Write("WIN");
                                    return playerNumber;
                                } 
                            } 
                        } 
            }
        }
    }

    //checks for tie, returns 3 if true
    //made nested for loops to improve readability
    if (((*P1).board[6][6] == 1 || (*P1).board[6][6] == 2))
    {
        if (((*P1).board[7][6] == 1 || (*P1).board[7][6] == 2))
        {
            if (((*P1).board[8][6] == 1 || (*P1).board[8][6] == 2))
            {
                if (((*P1).board[9][6] == 1 || (*P1).board[9][6] == 2))
                {
                    if (((*P1).board[10][6] == 1 || (*P1).board[10][6] == 2))
                    {
                        if (((*P1).board[11][6] == 1 || (*P1).board[11][6] == 2))
                        {
                            if (((*P1).board[12][6] == 1 || (*P1).board[12][6] == 2))
                            {
                                return 3;
                            }
                        }
                    }
                }
            }    
        }    
    }
    //ends function, main loop continues because no winner found
    return 0;
}
//int main
int main() {
    //C++ pointer to stats file
   fstream stats;

    //instantiates objects for player 1, player 2, and AI opponent
    player P1("Player 1", 0, 0, 0, " ", 0, 1);
    player P2("Player 2", 0, 0, 0, " ", 0, 2);
    AI opponent;

    //infinite loop to run program
    while(true)
    {
    //opens stats file
    stats.open ("stats.txt");

    //resets board to all 0s, readies for play
    resetBoard(&P1);
   
   //reads stats file, sets stat variables from objects to read data from stats file
    readStatsFile(stats, &P1, &P2, &opponent);

    Sleep(5);

    //draw initial menu
    drawMenu();

    //check for menu
    int menucheck = 0;

    //clear screen
    LCD.ClearBuffer();

    //checks for clicking of menu elements
    menuTransition(menucheck, &P1, &P2, &opponent);

    //update LCD
    LCD.Update();
    
    //clear LCD
    LCD.Clear();

    //draws board
    drawBoard(false);

    //0 when no winner is found, 1 when player 1 wins, 2 when AI or player 2 wins
    int winner = 0;

    //for end screen
    int loser = 0;
    
    //while no winner is found... play game
    while (winner == 0)
    {
        //player 1
        if (winner == 0)
        {
            LCD.SetFontColor(RED);
            LCD.WriteAt("Player   's Turn", 5, 5);
            LCD.WriteAt(1, 90, 5);
            //player 1 drops piece
            (P1).dropPiece(&P1, 1);
            //update stats total pieces dropped
            (P1).updateStats(0, 0, 0, 1);
            //checks win based on player 1 pieces
            winner = checkWin(&P1, &P2, 1);
        }
        //player 2
        if (P2.Play && winner == 0)
        {
            LCD.SetFontColor(YELLOW);
            LCD.WriteAt("Player   's Turn", 5, 5);
            LCD.WriteAt(2, 90, 5);
            //player 2 drops piece
           (P2).dropPiece(&P1, 2); 
           //update stats total pieces dropped
            (P2).updateStats(0, 0, 0, 1);
           //checks win based on player 2 pieces
           winner = checkWin(&P1, &P2, 2);
        }
        //AI
        else if (winner == 0)
        {
            //drop AI piece
            (opponent).AIDropPiece(&P1);
            //adds a total piece drop to AI TotalPiecesDropped varible
            (opponent).updateStats(0, 0, 0, 1);
            //checks for AI win
            winner = checkWin(&P1, &P2, 2);
        }
    }
    
    //if player 1 wins
    if (winner == 1)
    {
        //add a win to player 1 wins stats
        (P1).updateStats(1, 0, 0, 0);
        loser = 2;
    }
    //if player 2 or AI wins
    else if (winner == 2)
    {
        if (P2.Play)
        {
            //add a win to player 2 wins stats
            (P2).updateStats(1, 0, 0, 0);   
            (P2).updateStats(1, 0, 0, 0);
            loser = 1;   
        }
        else
        {
            //add a win to AI wins stats
            (opponent).updateStats(1, 0, 0, 0);
            loser = 1;
        }
    }

    //tie
    else if (winner == 3)
    {
        winner = 1;
        loser = 1;
    }

    //write new data to stats file
    updateStatsFile(stats, &P1, &P2, &opponent);
    //close the stats file so changes can be saved
    stats.close();

    //end screen
    FEHIMAGE end; //initialize pic variable
    end.Open("end screenFEH.pic");
    end.Draw(0,0);//draw pic
    LCD.SetFontColor(RED);
    LCD.WriteAt("P", 40, 92.5);
    LCD.WriteAt(loser, 50, 92.5);
    LCD.WriteAt("P", 40, 112.5);
    LCD.WriteAt(winner, 50, 112.5);
    if (winner == 3)
    {
        LCD.WriteAt("TIE", 40, 130);
    }
    Sleep(5000);
}
    //end main
    return 0;
}

//AI drop piece with AI "functionality"
int AI::AIDropPiece(player *P1)
{
    //if easiest difficulty selected, AI just places pieces in random column
    if (Difficulty == 1)
    {
        //generates random column from 1 to 7
        int columnDrop = rand() % (7 + 1 - 1) + 1;
        //LCD.Write(columnDrop);
        (*P1).updateBoard(columnDrop, 2);
        //end
        return 0;
    }
    //easy r easier difficulty isselected
    else if (Difficulty == 2)
    {
        //so that it doesnt move twice, doesnt really work yet
        bool move = true;
        //first three moves, because dominate center or whatever
        if (turnCount < 3)
        {
            //generates random number in column from 3 to 5, center
            int columnDrop = rand() % (5 + 1 - 3) + 3;
            //drops piece
            (*P1).updateBoard(columnDrop, 2);
        }

        //drop pieces based on opposing pieces and own pieces, else drops random piece
        if (turnCount >= 3)
        {
            //for loop to scan through board and detecs 3 in arow opposing pieces, drops a piece to stop
            //opponent from winning.
            //if opponent does not have 3 in a row, it drops a piece to continue its consecutive placings
            for (int i = 6; i < 13; i++)
            {
                for (int j = 6; j < 12; j++)
                {
                    //stop opponent's placings
                    if ((*P1).board[i][j] == 1)
                    {     
                        //left
                        if ((*P1).board[i-1][j] == 1)
                        {
                            if ((*P1).board[i-2][j] == 1)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-8, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                        //right
                        else if ((*P1).board[i+1][j] == 1)
                        {
                            if ((*P1).board[i+2][j] == 1)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-2, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                        //top[]
                        else if ((*P1).board[i][j-1] == 1)
                        {
                            if ((*P1).board[i][j-2] == 1)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-5, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                    }
                    //continue own cosecutive placings
                    else if ((*P1).board[i][j] == 2)
                    {           
                        //left
                        if ((*P1).board[i-1][j] == 2)
                        {
                            
                            if ((*P1).board[i-2][j] == 2)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-8, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                        //right
                        else if ((*P1).board[i+1][j] == 2)
                        {
                            if ((*P1).board[i+2][j] == 2)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-2, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                        //top[]
                        else if ((*P1).board[i][j-1] == 2)
                        {
                            if ((*P1).board[i][j-2] == 2)
                            {
                                move = false;
                                //drops piece
                                (*P1).updateBoard(i-5, 2);
                                //end loop
                                return 0;
                            } 
                        } 
                    }
                }
            }
            //if opponent doe snot have 3 in a row and no consecutive own placings, AI drops a random placing.
            if (move)
            {
                //random piece column generated
                int columnDrop = rand() % (5 + 1 - 3) + 3;
                //drops random piece
                (*P1).updateBoard(columnDrop, 2);
                move = false;
                //end loop
                return 0;
            }
        }
        //increments turn count
        ++turnCount;
    }
}

//player constructor, takes arguments name wins losses ties theme totalpiecesplaced play and player number and sets them
player::player (char nm[], int wins, int losses, int ties, char theme[], int totalPiecesPlaced, bool play, int PlayerNumbers)
{
    //sets name
    strcpy (Nm, nm);
    //sets wins
    Wins = wins;
    //sets losses
    Losses = losses;
    //sets toes
    Ties = ties;
    //sets theme
    strcpy(Theme, theme);
    //sets totalpiecesplaced
    TotalPiecesPlaced = totalPiecesPlaced;
    //sets bool play
    Play = play;
    //sets playernumbers
    PlayerNumbers = PlayerNumbers;
    
    //sets board elements to 0
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            board [i][j] = 0;
        }
    }
  
}

//AI opponenent constructor takes arguments name wins losses ties  totalpiecesplaced and turn and initializes the values 
AI::AI (int difficulty, int wins, int losses, int ties, int totalPiecesPlaced, int turn)
{
    //sets difficulty, from 1 to 2
    Difficulty = difficulty;
    //sets wins
    Wins = wins;
    //sets losses
    Losses = losses;
    //sets ties
    Ties = ties;
    //sets totalPiecesPlaced
    TotalPiecesPlaced = totalPiecesPlaced;
    //sets turn count, used for AI
    turnCount = turn;
}

//sets difficulty of AI based on player selection
void AI::setDifficulty()
{
    //exit check for loop
    int exit = 0;

    //checks for click from user to set difficulty
    while (exit == 0)
    {
    LCD.SetFontColor(LCD.Black);
    //clears screen
    LCD.FillRectangle(0, 30, 250, 190);

    LCD.SetFontColor(LCD.White);
    //writes elements
    LCD.WriteAt("Select Difficulty", 50, 10);
    LCD.WriteAt("Easiest", 10, 70);
    LCD.WriteAt("Easy", 10, 110);
    
    //hold position of touch
    float x_position, y_position;
    float x_trash, y_trash;

    while(!LCD.Touch(&x_position,&y_position)) {};
    while(LCD.Touch(&x_trash,&y_trash)) {};
    
    if (x_position > 0 && x_position < 100)
    {
        //if easiest is selected
        if (y_position > 62 && y_position < 78)
        {
            Difficulty = 1;
            exit = 1;
        }
        //if easier is selected. Normal is equivalent to easier
        else if (y_position > 102 && y_position < 118)
        {
            Difficulty = 2;
            exit = 1;
        }
       
    }
    }
}

//updates stat variables, wins losses ties and totalpiecesplaced.
void player::updateStats(int wins, int losses, int ties, int totalPiecesPlaced)
{
    Wins += wins;
    Losses += losses;
    Ties += ties;
    TotalPiecesPlaced += totalPiecesPlaced;
}

//updates stat variables, wins losses ties and totalpiecesplaced.
void AI::updateStats(int wins, int losses, int ties, int totalPiecesPlaced)
{
    Wins += wins;
    Losses += losses;
    Ties += ties;
    TotalPiecesPlaced += totalPiecesPlaced;
}

//select piece theme. not fully implemented, do not plan to implement this
void player::selectPieceTheme()
{
    //exit loop check
    int exit = 0;

    //checks for menu element selection and sets the theme corresponding to selection
    while (exit == 0)
    {
    LCD.Clear();
    //writes selection
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
        //if normal option selected
        if (y_position > 135 && y_position < 157)
        {
            strcpy(Theme, "Normal");
            exit = 1;
        }
        //pizza option selected
        else if (y_position > 158 && y_position < 177)
        {
            strcpy(Theme, "Pizza");
            exit = 1;
        }
        //cookie option selected
        else if (y_position > 178 && y_position < 200)
        {
            strcpy(Theme, "Cookies");
            exit = 1;
        }
    }
    }

}

//drops a piece for the player. takes object player 1 to set the board and player number
//player number is used to set the board index to corresponding piece and update the theme
//when dropping
void player::dropPiece(player *P1, int playerNumber)
{
    //hold position of touch
    float x_position, y_position;
    float x_trash, y_trash;
    float x_init;
    float y_init;

    while(!LCD.Touch(&x_position,&y_position)) {};
    //while piece is held
    while(LCD.Touch(&x_trash,&y_trash)) {
        //if position of cursor when piece is held
        if (x_init != x_trash || y_init != y_trash)
        {
            //erase old position
            LCD.SetFontColor(BLACK);
            LCD.FillCircle(x_init, y_init, 120);
        }
        //sets chip theme, red if player 1, yellow if player 2
        if (playerNumber == 1)
        {
            LCD.SetFontColor(RED);
        }
        else if (playerNumber == 2)
        {
            LCD.SetFontColor(YELLOW);
        }

        //sets coordinates to new coordinates
        x_init = x_trash;
        y_init = y_trash;

        //sets circle at new position
        LCD.FillCircle(x_trash, y_trash, 10);

        //draws the board while piece held to prevent overlap
        drawBoard(false);

        //updates the pieces on the board so the player can see where
        //they are dropping it
        (*P1).updateBoard(0, 5);

        //lowers framerate
        Sleep(10);
    }
    
    //sets position of when the piece is let go to _position variables to be analyzed
    //in function updateBoard(...);
    x_position = x_init;
    y_position = y_init;

    drawBoard(true);
    
    //if piece is dropped within vincinity of board
    if (x_position < 226)
    {
        //while the piece is above the board
        while (y_init < 63)
        {
            LCD.SetFontColor(BLACK);
            //blots out old circle
            LCD.FillCircle(x_init, y_init, 10);

            //sets color of piece based on player number
            //red if 1, yellow if 2
            if (playerNumber == 1)
            {
                LCD.SetFontColor(RED);
            }
            else if (playerNumber == 2) 
            {
                LCD.SetFontColor(YELLOW);
            }

            //fills the circle at a y value lower than before
            //to animate falling effect
            LCD.FillCircle(x_init, ++y_init, 10);

            //draws board while falling
            drawBoard(false);

            //draws pieces in board while falling
            (*P1).updateBoard(0, 5);
            
            //framerate check
            Sleep (10);
        }

        //if piece is above column 1 of board and the top piece of
        //column 1 is not filled
        if (x_position < 44 && board [6][6] == 0)
        {
            (*P1).updateBoard(1, playerNumber);
        }

        //if piece is above column 2 of board and the top piece of
        //column 2 is not filled
        else if (x_position < 72 && board [7][6] == 0)
        {
            (*P1).updateBoard(2, playerNumber);
        }

        //if piece is above column 3 of board and the top piece of
        //column 3 is not filled
        else if (x_position < 100 && board [8][6] == 0)
        {
            (*P1).updateBoard(3, playerNumber);
        }

        //if piece is above column 4 of board and the top piece of
        //column 4 is not filled
        else if (x_position < 128 && board [9][6] == 0)
        {
            (*P1).updateBoard(4, playerNumber);
        }

        //if piece is above column 5 of board and the top piece of
        //column 5 is not filled
        else if (x_position < 156 && board [10][6] == 0)
        {
            (*P1).updateBoard(5, playerNumber);
        }

        //if piece is above column 6 of board and the top piece of
        //column 6 is not filled
        else if (x_position < 184 && board [11][6] == 0)
        {
            (*P1).updateBoard(6, playerNumber);
        }

        //if piece is above column 7 of board and the top piece of
        //column 7 is not filled
        else if (x_position < 212 && board [12][6] == 0)
        {
            (*P1).updateBoard(7, playerNumber);
        }
    }

    //if the piece is not dropped within the dimensionsions of the board
    else
    { 
        //drops the piece into nothingness. . . . . . .
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
}

//updates the board to account for dropped piece
void player::updateBoard(int column, int playerNumber)
{
    //nested for loop to draw the pieces based on whether it is occupied by player 1 or 2 or AI
    //if occupied by player 1, draw a red circle there. If player 2 or AI, draw a yellow circle.
    for (int i = 6; i < 13; i++)
    {
        for (int j = 6; j < 12; j++)
        {
            //if equal to playerNumber 1
            if (board [i][j] == 1)
            {
                //draw a red cirlc there
                LCD.SetFontColor(RED);
                LCD.FillCircle(30 + (28*(i-6)), 63 + (29*(j-6)), 10);
            }
            //if equal to playerNumber 2, player 2 or AI
            if (board [i][j] == 2)
            {
                //draw a red cirlc there
                LCD.SetFontColor(YELLOW);
                LCD.FillCircle(30 + (28*(i-6)), 63 + (29*(j-6)), 10);
            }
        }
    }
    
    //counter for while loop to draw falling animation in board
    int i = 0;
    //draws falling animation in board
    while (i < 5 && board[column+5][i+7] == 0)
    {
        //fills the previous circle
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(30 + (28*(column-1)), 63 + (29*i), 10);

        //sets piece color based on player number
        //sets red on player number 1
        if (playerNumber == 1)
        {
            LCD.SetFontColor(RED);
        }
        //sets yellow on player number 2
        else if (playerNumber == 2)
        {
            LCD.SetFontColor(YELLOW);
        }
        //fills the new circle
        LCD.FillCircle(30 + (28*(column-1)), 63 + (29*(i+1)), 10);
        Sleep(100);
        //increments i to continue falling effect
        ++i;
    }
    //fills new piece position with player number, player number # occupies this space
    board[column+5][i+6] = playerNumber;
}