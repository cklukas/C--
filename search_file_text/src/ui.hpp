#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <vector>

/**
 * @brief Get input from the user
 * @param input_win The window to display the input
 * @param line The current line number
 * @param resultInput The result of the input
 * @param message The message to display
 * @param messageEmpty The message to display if the input is empty
 * 
*/
void getInput(WINDOW* input_win, int* line, char* resultInput, const char* message, const char* messageEmpty);

/**
 * @brief Get multi-line input from the user
 * @param line The current line number
 * @param inputs The result of the input
 * @param message The message to display
*/
void getMultiLineInput(WINDOW* input_win, int* line, std::vector<std::string>* resultInputs, const char* message);

/**
 * @brief Get radio input from the user
 * @param line The current line number
 * @param choices The choices to display
 * @param message The message to display
 * @return The index of the selected choice
*/
int getRadioInput(int* line, char *choices[], const char* message);

/**
 * @brief Create a new window
 * @param height The height of the window
 * @param width The width of the window
 * @param starty The starting y position of the window
 * @param startx The starting x position of the window
 * @param title The title of the window
 * @return The created window
*/
WINDOW* newWindow(int height, int width, int starty, int startx, const char* title);

#endif