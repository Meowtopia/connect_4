//headers
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include <iostream>
#include <string>
#include <vector>
#include "fstream"

int main()
{
using namespace std;
FEHIMAGE pic1; //test pic
	pic1.Open("connect 4FEH.pic");
	pic1.Draw(0,0);
    LCD.Update();//end test pic
   //draw cookie
       LCD.SetFontColor(WHEAT);
    LCD.DrawCircle(10,10,10);
    LCD.FillCircle(10,10,10);
    LCD.SetFontColor(BLACK);
    LCD.DrawRectangle(4,4,2,2);
    LCD.FillRectangle(4,4,2,2);
    LCD.DrawRectangle(8,8,2,2);
    LCD.FillRectangle(8,8,2,2);
    LCD.DrawRectangle(4,10,2,2);
    LCD.FillRectangle(4,10,2,2);
    LCD.DrawRectangle(14,6,2,2);
    LCD.FillRectangle(14,6,2,2);

 LCD.SetFontColor(WHEAT);
    LCD.DrawCircle(10,10,10);
LCD.SetFontColor(YELLOW);
    LCD.FillCircle(10,10,10);
    LCD.SetFontColor(RED);
    LCD.DrawCircle(4,4,3);
    LCD.FillCircle(4,4,3);
    LCD.DrawCircle(8,8,2);
    LCD.FillCircle(8,8,2);
    LCD.DrawCircle(4,10,3);
    LCD.FillCircle(4,10,3);
    LCD.DrawCircle(14,6,2);
    LCD.FillCircle(14,6,2);
    


    }
