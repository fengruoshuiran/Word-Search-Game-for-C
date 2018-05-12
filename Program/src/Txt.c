/*! @brief All text in project
*
* Function about print
*
* @file Txt.c
* @author ruoran
* @date 2018.5.12
*/

#include "include.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<ctype.h>

const char setting[MAX_STR_LEN]   = ".//setting.ini";
const char Param[MAX_STR_LEN]     = "Param";
const char Rate[MAX_STR_LEN]      = "Rate";
const char History[MAX_STR_LEN]   = "History";
const char Welcome[MAX_STR_LEN]   = ".//rec//Welcome.txt";
const char ErrorRead[MAX_STR_LEN] = "can't open file\n";
const char Category[MAX_STR_LEN]  = ".//rec//WordList//*.txt";

void ErrorPrint() {
    printf(ErrorRead);
    exit(1);

    return;
}

void WelcomePrint() {
    char buffer[MAX_LINE_LEN];
    FILE* pf = fopen(Welcome, "r");
    if (!pf) ErrorPrint();
    while (!feof(pf)) {
        fgets(buffer, sizeof buffer, pf);
        printf("%s", buffer);
    }
    getchar();
    fflush(stdin);

    return;
}

void ChoosePrint() {
    system("cls");
    printf("Hey %s!\n\n", PlayerName);
    printf("In %d seconds, you need to find out %d words\n", TimeLimit, Words);
    printf("The size of martrix is %d * %d\n\n", Height, Width);
    printf("Have fun, %s!\n\n", PlayerName);
    printf("Choose one of the category you like:\n");
    for (int i = 0; i < CategoryTot; i++)
        printf("|--%d:%s\n", i, Category_Name[i]);
    do {
        printf("Your choose(numeric) :");
        scanf("%d", &PlayerChoose);
    } while (PlayerChoose < 0 || PlayerChoose >= CategoryTot);

    return;
}

void PuzzlePrint() {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            if (PuzzleColor[i][j] == HIDE) printf("  ");
            else if (Puzzle[i][j] == 0)    printf("  ");
            else if (Letter == 0)          printf("%c ", Puzzle[i][j]);
            else if (Letter == 1)          printf("%c ", Puzzle[i][j] + 'A' - 'a');
        }
        printf("\n");
    }

    return;
}

void ReadyPrint() {
    system("cls");
    for (int i = 5; i >= 0; i--) {
        printf( "Game will start in %d seconds...\n", i);
        Sleep(1000);
    }

    return;
}

void GamePrint() {
    char buffer[MAX_STR_LEN];
    clock_t START = clock();
    clock_t END = clock();

    while (1) {
        END = clock();
        int T = (int)((END - START) / CLOCKS_PER_SEC);

        system("cls");
        printf("Word Search\n\n");
        printf("%s:---------- Try:%d\tWin:%d\n\n",PlayerName, Try, Win);
        printf("There are %d words hidden in this grid.\n", Words);
        printf("You have %d second left\n\n", (TimeLimit - T < 0 ? 0 : TimeLimit - T));
        printf("-------------------------------------\n");
        PuzzlePrint();
        printf("-------------------------------------\n\n");
        printf("%d words left\n", WordLeft);
        printf("Word:");
        if (T >= TimeLimit || WordLeft == 0) break;
        scanf("%s", buffer);
        for (int i = 0; i < strlen(buffer); i++) tolower(buffer[i]);
        if (WordCheck(buffer) == true) WordLeft--;
    }
    ShowPuzzle();
    if (WordLeft == 0) {
        printf("You win!\n");
        Win++;
        char WinStr[MAX_STR_LEN];
        sprintf(WinStr, " %d", Win);
        WritePrivateProfileString(History, "Win", WinStr, setting);
    }
    else printf("Game Over, Try next time!\n");
    Try++;
    char TryStr[MAX_STR_LEN];
    sprintf(TryStr, " %d", Try);
    WritePrivateProfileString(History, "Try", TryStr, setting);
    printf("Press Enter to restart:");
    getchar();
    getchar();
    fflush(stdin);

    return;
}

void DrawColor(int WordId) {
    if (WordNode[WordId].dir == ASCENDING)
        for (int i = 0; i < strlen(WordList[WordId]); i++)
            PuzzleColor[WordNode[WordId].X - i][WordNode[WordId].Y + i] = HIDE;
    if (WordNode[WordId].dir == DESCENDING)
        for (int i = 0; i < strlen(WordList[WordId]); i++)
            PuzzleColor[WordNode[WordId].X + i][WordNode[WordId].Y + i] = HIDE;
    if (WordNode[WordId].dir == HORIZONTALLY)
        for (int i = 0; i < strlen(WordList[WordId]); i++)
            PuzzleColor[WordNode[WordId].X][WordNode[WordId].Y + i] = HIDE;
    if (WordNode[WordId].dir == VERTICALLY)
        for (int i = 0; i < strlen(WordList[WordId]); i++)
            PuzzleColor[WordNode[WordId].X + i][WordNode[WordId].Y] = HIDE;

    return;
}

void ShowPuzzle() {
    printf("\n\nAnswer:\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < WordTot; i++)
        if (WordUsed[i] == true) DrawColor(i);
    for (int i = 0; i < Height; i++)
        for (int j = 0; j < Width; j++)
            PuzzleColor[i][j] = !PuzzleColor[i][j];
    PuzzlePrint();
    printf("-------------------------------------\n");

    return;
}
