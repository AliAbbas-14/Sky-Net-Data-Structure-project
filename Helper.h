#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <windows.h> // For colors

using namespace std;

// Color Codes
#define COLOR_RESET 7
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_CYAN 11
#define COLOR_YELLOW 14
#define COLOR_WHITE 15
#define COLOR_GREY 8 

// Helper function to set console text color
inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif#pragma once
