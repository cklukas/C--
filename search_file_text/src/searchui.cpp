#include <iostream>
#include <vector>
#include <ncurses.h>
#include <wordexp.h>
#include <vector>

#include "ui.hpp"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        // no parameters are provided, show the UI to get the user input
        char selectedStartDirectory[256];
        char filenamePostfix[256];
        std::vector<std::string> searchTerms;
        bool caseSensitiveSearch;

        initscr();
        cbreak();

        int screen_width, screen_height;
        getmaxyx(stdscr, screen_width, screen_height);
        WINDOW *input_win = newWindow(screen_width - 2, screen_height - 2, 1, 1, " Search Files ");

        int current_vertical_pos = 2;
        getInput(input_win, &current_vertical_pos, selectedStartDirectory, "Enter the root directory for the search (use '~' for your home, or '~user' for home of 'user'): ", "(current directory)");
        getInput(input_win, &current_vertical_pos, filenamePostfix, "Enter the filename or extension: ", "(all files)");
        current_vertical_pos--;
        getMultiLineInput(input_win, &current_vertical_pos, &searchTerms, "Enter search terms (use Enter to separate them):");

        char choice1[] = "Yes";
        char choice2[] = "No";
        char *choices[] = {choice1, choice2};
        current_vertical_pos+=2;
        caseSensitiveSearch = getRadioInput(&current_vertical_pos, choices, " Case sensitive search (search terms and filenames)? ") == 0;

        if (caseSensitiveSearch)
        {
            // empty
        }

        getch();
        wrefresh(input_win);
        endwin(); // End ncurses

        // Use the user input to perform the search
        // ...
    }
    else
    {
        // Use the provided parameters to perform the search
        // ...
    }

    return 0;
}