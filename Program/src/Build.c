/*! @brief Building
*
* Include some function and data about building
* Read Category_Name
* Read WordList
* Build Puzzle
* Check words
*
* @file Build.c
* @author ruoran
* @date 2018.5.12
*/

#include "include.h"
#include<stdio.h>
#include<io.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

char Category_Name[MAX_FLIE_TOT][MAX_STR_LEN];
char WordList[MAX_WORD_TOT][MAX_STR_LEN];
char Puzzle[MAX_HEIGHT][MAX_WIDTH];
bool PuzzleColor[MAX_HEIGHT][MAX_WIDTH];
bool WordUsed[MAX_WORD_TOT];
Node WordNode[MAX_WORD_TOT];
int CategoryTot  = 0;
int PlayerChoose = 0;
int WordTot      = 0;
int WordLeft     = 0;

void GetCategory() {
    struct _finddata_t fileinfo;
    long fHandle;

    if((fHandle = _findfirst(Category, &fileinfo)) == -1L)
        ErrorPrint();
    else {
        do{
            strcpy(Category_Name[CategoryTot++], fileinfo.name);
        }while(_findnext(fHandle,&fileinfo) == 0);
    }
    _findclose(fHandle);

    return;
}

void GetWordList() {
    printf("WordList Reading...");

    char wordPath[MAX_STR_LEN] = ".//rec//WordList//";

    memset(WordList, 0, sizeof WordList);
    WordTot = 0;

    strcat(wordPath, Category_Name[PlayerChoose]);
    FILE* pf = fopen(wordPath, "r");
    if (!pf) ErrorPrint();
    while (!feof(pf))
        fscanf(pf, "%s", WordList[WordTot++]);
    fclose(pf);

    printf("\tWordList ready.\n");

    return;
}

void BuildPuzzle() {
    printf("Puzzle creating...");

    int HorizontallyTime = Words * HorizontallyRate / 100;
    int VerticallyTime   = Words * VerticallyRate   / 100;
    int DiagonallyTime   = Words - HorizontallyTime - VerticallyTime;

    memset(WordUsed,    0, sizeof WordUsed);
    memset(WordNode,    0, sizeof WordNode);
    memset(Puzzle,      0, sizeof Puzzle);
    memset(PuzzleColor, 0, sizeof PuzzleColor);
    WordLeft = Words;

    while (DrawHorizontally(HorizontallyTime)
           && DrawVertically  (VerticallyTime)
           && DrawDiagonally  (DiagonallyTime) == false) {
                memset(WordUsed, 0, sizeof WordUsed);
                memset(WordNode, 0, sizeof WordNode);
                memset(Puzzle,   0, sizeof Puzzle);
           }
    FillBlank();

    printf("\tPuzzle ready!\n");

    return;
}

bool DrawHorizontally(int HorizontallyTime) {
    while (HorizontallyTime--) {
        srand((unsigned int)time(NULL));

        char wordText[MAX_STR_LEN];
        int WordLen;
        int randIndex  = rand() % WordTot;
        int X          = rand() % Height;
        int Y          = rand() % Width;
        int retTimeCnt = 0;

        while (WordUsed[randIndex] == true) randIndex = rand() % WordTot;
        WordUsed[randIndex] = true;
        strcpy(wordText, WordList[randIndex]);
        WordLen = strlen(wordText);

        while (HorizontallyCheck(X, Y, WordLen) == false && retTimeCnt++ < MAX_RET_TIME)
            X = rand() % Height, Y = rand() % Width;
        if (retTimeCnt >= MAX_RET_TIME) return false;
        for (int i = 0; i < WordLen; i++)
            Puzzle[X][Y + i] = wordText[i];
        WordNode[randIndex] = (Node) {X, Y, HORIZONTALLY};
    }

    return true;
}

bool DrawVertically(int VerticallyTime) {
    while (VerticallyTime--) {
        srand((unsigned int)time(NULL));

        char wordText[MAX_STR_LEN];
        int WordLen;
        int randIndex  = rand() % WordTot;
        int X          = rand() % Height;
        int Y          = rand() % Width;
        int retTimeCnt = 0;

        while (WordUsed[randIndex] == true) randIndex = rand() % WordTot;
        WordUsed[randIndex] = true;
        strcpy(wordText, WordList[randIndex]);
        WordLen = strlen(wordText);

        while (VerticallyCheck(X, Y, WordLen) == false && retTimeCnt++ < MAX_RET_TIME)
            X = rand() % Height, Y = rand() % Width;
        if (retTimeCnt >= MAX_RET_TIME) return false;
        for (int i = 0; i < WordLen; i++)
            Puzzle[X + i][Y] = wordText[i];
        WordNode[randIndex] = (Node) {X, Y, VERTICALLY};
    }

    return true;
}

bool DrawDiagonally(int DiagonallyTime) {
    while (DiagonallyTime--) {
        srand((unsigned int)time(NULL));

        char wordText[MAX_STR_LEN];
        int WordLen;
        int randIndex  = rand() % WordTot;
        int X          = rand() % Height;
        int Y          = rand() % Width;
        int dir        = rand() % DIR;
        int retTimeCnt = 0;

        while (WordUsed[randIndex] == true) randIndex = rand() % WordTot;
        WordUsed[randIndex] = true;
        strcpy(wordText, WordList[randIndex]);
        WordLen = strlen(wordText);

        if (dir == ASCENDING) {
            while(AscendingCheck(X, Y, WordLen) == false && retTimeCnt++ < MAX_RET_TIME)
                X = rand() % Height, Y = rand() % Width;
            if (retTimeCnt >= MAX_RET_TIME) return false;
            for (int i = 0; i < WordLen; i++)
                Puzzle[X - i][Y + i] = wordText[i];
            WordNode[randIndex] = (Node) {X, Y, ASCENDING};

        }
        if (dir == DESCENDING) {
            while(DescendingCheck(X, Y, WordLen) == false && retTimeCnt++ < MAX_RET_TIME)
                X = rand() % Height, Y = rand() % Width;
            if (retTimeCnt >= MAX_RET_TIME) return false;
            for (int i = 0; i < WordLen; i++)
                Puzzle[X + i][Y + i] = wordText[i];
            WordNode[randIndex] = (Node) {X, Y, DESCENDING};
        }
    }

    return true;
}

void FillBlank() {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < Height; i++)
        for (int j = 0; j < Width; j++)
            if (Puzzle[i][j] == 0) Puzzle[i][j] = (rand() % LETTER_TOT) + 'a';

    return;
}

bool HorizontallyCheck(int X, int Y, int len) {
    if (Y + len > Width) return false;
    for (int i = 0; i < len; i++)
        if (Puzzle[X][Y + i] != 0) return false;

    return true;
}

bool VerticallyCheck(int X, int Y, int len) {
    if (X + len > Height) return false;
    for (int i = 0; i < len; i++)
        if (Puzzle[X + i][Y] != 0) return false;

    return true;
}

bool AscendingCheck(int X, int Y, int len) {
    if (X + 1 - len < 0) return false;
    if (Y + len > Width) return false;
    for (int i = 0; i < len; i++)
        if (Puzzle[X - i][Y + i] != 0) return false;

    return true;
}

bool DescendingCheck(int X, int Y, int len) {
    if (X + len > Height) return false;
    if (Y + len > Width)  return false;
    for (int i = 0; i < len; i++)
        if (Puzzle[X + i][Y + i] != 0) return false;

    return true;
}

bool WordCheck (char* W) {
    for (int i = 0; i < WordTot; i++)
        if (strcmp(W, WordList[i]) == 0 && WordUsed[i] == true) {
            WordUsed[i] = false;
            DrawColor(i);
            return true;
        }

    return false;
}
