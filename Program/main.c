/*! @brief main
*
* Word Search Game
*
* @file main.c
* @author ruoran
* @date 2018.5.12
*/

#include<stdio.h>
#include "include.h"
int main() {
    IniRead();
    WelcomePrint();
    GetCategory();
    do {
        ChoosePrint();
        GetWordList();
        BuildPuzzle();
        ReadyPrint();
        GamePrint();
    } while(true);

    return 0;
}
