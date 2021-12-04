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
    }