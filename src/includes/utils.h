#pragma once
#include <iostream>
#include <iomanip>
#include <regex>
#include <conio.h>

#define SPACE 32
#define ENTER 13
#define BACKSPACE 8
#define SPECIAL_KEY 0
#define LEFT 75
#define RIGHT 77

using namespace std;

/// @brief Remove whitespaces of a string
/// @param text The string
/// @return String without whitespaces
string trim(string text);

/// @brief Pass string to lower case
/// @param text The string
/// @return The string in lower case
string lower(string text);

/// @brief Capitalize the string
/// @param text The string
/// @return The capitalized string
string capitalize(string text);

/// @brief Format a string to CPF
/// @param text The string
/// @return Formatted string
string toCpf(string text);

/// @brief Check if string is formated to CPF
/// @param text The string
/// @return True if formatted, false otherwise
bool isCpf(string text);

/// @brief Clear terminal
void clear();

/// @brief Pause terminal and input a message
/// @param text Terminal message
/// @return Pressed key
char input(string text);