/*! @brief Read ini file and get param
*
* @file Ini.c
* @author ruoran
* @date 2018.5.12
*/

#include "include.h"
#include<stdio.h>
#include<windows.h>

char PlayerName[MAX_STR_LEN];
char LetterSetting[MAX_STR_LEN];
bool Letter;
int TimeLimit;
int Width;
int Height;
int Words;

int HorizontallyRate;
int VerticallyRate;
int DiagonallyRate;

int Try;
int Win;

void IniRead() {
    // Read Param
    GetPrivateProfileString(Param, "PlayerName", NULL, PlayerName, sizeof PlayerName, setting);
    GetPrivateProfileString(Param, "Letter", NULL, LetterSetting, sizeof LetterSetting, setting);
    if (LetterSetting[0] == 'l') Letter = 0;
    if (LetterSetting[0] == 'u') Letter = 1;
    TimeLimit = GetPrivateProfileInt(Param, "TimeLimit", 0, setting);
    Height = GetPrivateProfileInt(Param, "Height", 0, setting);
    Width = GetPrivateProfileInt(Param, "Width", 0, setting);
    Words = GetPrivateProfileInt(Param, "Words", 0, setting);

    // Read Rate
    HorizontallyRate = GetPrivateProfileInt(Rate, "HorizontallyRate", 0, setting);
    VerticallyRate = GetPrivateProfileInt(Rate, "VerticallyRate", 0, setting);
    DiagonallyRate = GetPrivateProfileInt(Rate, "DiagonallyRate", 0, setting);

    // Read History
    Try = GetPrivateProfileInt(History, "Try", 0, setting);
    Win = GetPrivateProfileInt(History, "Win", 0, setting);

    if (HorizontallyRate + VerticallyRate + DiagonallyRate != RATE_TOT) ErrorPrint();

    return;
}
