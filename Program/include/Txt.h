/*! @brief All text in project
*
* Function about print
*
* @file Txt.h
* @author ruoran
* @date 2018.5.12
*/

#ifndef TXT_H
#define TXT_H

#define MAX_STR_LEN    50
#define MAX_LINE_LEN   100
#define RATE_TOT       100
#define MAX_FLIE_TOT   255
#define MAX_WORD_TOT   255
#define MAX_WIDTH      30
#define MAX_HEIGHT     30
#define MAX_RET_TIME   10000
#define LETTER_TOT     26
#define CLOCKS_PER_SEC 1000
#define COLOR_TOT      14
#define SHOW           0    ///< Show letter in puzzle
#define HIDE           1    ///< Hide letter in puzzle

/// @brief Message and paths
extern const char setting[MAX_STR_LEN];
extern const char Param[MAX_STR_LEN];
extern const char Rate[MAX_STR_LEN];
extern const char History[MAX_STR_LEN];
extern const char Welcome[MAX_STR_LEN];
extern const char ErrorRead[MAX_STR_LEN];
extern const char Category[MAX_STR_LEN];

/// @brief Error interface
///
/// If sum of rate not equal to 100, exit
extern void ErrorPrint();
/// @brief welcome interface
///
/// Print "Welcome.txt" on screen,then show player the category
extern void WelcomePrint();
/// @brief Print choose message
///
/// Read file and get category list, or exit
extern void ChoosePrint();
/// @brief Print Puzzle on screen
extern void PuzzlePrint();
/// @brief Sleep 10 seconds
extern void ReadyPrint();
/// @brief Show Game interface
///
/// This function accomplish all problem in the game
extern void GamePrint();
/// @brief Color the word in puzzle
extern void DrawColor(int WordId);
/// @brief Show the answer of Puzzle
extern void ShowPuzzle();
#endif // TXT_H
