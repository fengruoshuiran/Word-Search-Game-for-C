/*! @brief Building
*
* Include some function and data about building
* Read Category_Name
* Read WordList
* Build Puzzle
* Check words
*
* @file Build.h
* @author ruoran
* @date 2018.5.12
*/


#ifndef BUILD_H
#define BUILD_H

#define DIR          2  ///< Diagonally : ascending or descending
#define ASCENDING    0
#define DESCENDING   1
#define HORIZONTALLY 2
#define VERTICALLY   3

extern char Category_Name[MAX_FLIE_TOT][MAX_STR_LEN];
extern char WordList[MAX_WORD_TOT][MAX_STR_LEN];
extern char Puzzle[MAX_HEIGHT][MAX_WIDTH];
extern bool PuzzleColor[MAX_HEIGHT][MAX_WIDTH];
extern bool WordUsed[MAX_WORD_TOT];
typedef struct Node {
    int X, Y;
    int dir;
}Node;
extern Node WordNode[MAX_WORD_TOT]; ///< Save the start coordinate and direction
extern int CategoryTot;
extern int PlayerChoose;
extern int WordTot;
extern int WordLeft;
/// @brief Get category file
extern void GetCategory();
/// @brief Read wordlist from file
extern void GetWordList();
/// @brief Build the puzzle mitrix
extern void BuildPuzzle();
/// @brief Check if the word hidden in puzzle
///
/// Check if the word is appeard in puzzle
/// @param W This word will be checked,scnaf from player
extern bool WordCheck(char* W);

extern bool DrawHorizontally(int HorizontallyTime);
extern bool DrawVertically(int VerticallyTime);
extern bool DrawDiagonally(int DiagonallyTime);
extern void FillBlank();

extern bool HorizontallyCheck(int X, int Y, int len);
extern bool VerticallyCheck(int X, int Y, int len);
extern bool AscendingCheck(int X, int Y, int len);
extern bool DescendingCheck(int X, int Y, int len);
#endif // BUILD_H
