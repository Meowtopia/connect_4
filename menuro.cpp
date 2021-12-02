#include "FEHLCD.h"
#include "FEHUtility.h"

int main() {
    // Infinite loop so the stoplights run until the program is closed
    

while(true)
{
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("N/S", 20, 112);
   LCD.Update();

}

    return 0;
}