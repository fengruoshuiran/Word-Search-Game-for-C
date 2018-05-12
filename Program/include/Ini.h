/*! @brief Read ini file and get param
*
* @file Ini.h
* @author ruoran
* @date 2018.5.12
*/

#ifndef INI_H
#define INI_H
#include<stdbool.h>

/// @brief Read setting.ini
/// @brief [Param]
extern char PlayerName[];
extern char LetterSetting[];
extern bool Letter;
extern int TimeLimit;
extern int Width;
extern int Height;
extern int Words;

/// @brief [Rate]:Rate / 100
extern int HorizontallyRate;
extern int VerticallyRate;
extern int DiagonallyRate;

/// @brief [History]
extern int Try;
extern int Win;

/// @brief Read file "setting.ini"
///
/// If sum of rate is not equal to 100, exit
extern void IniRead();

#endif // INI_H
