#include <iostream>
#include <vector>
#include <ncurses.h>
#include <wordexp.h>
#include <vector>
#include "ui.hpp"

void getInput(WINDOW* input_win, int* line, char* resultInput, const char* message, const char* messageEmpty) {
    mvwprintw(input_win, (*line)++, 3, message);
    wrefresh(input_win);
    mvwgetstr(input_win, (*line)++, 3, resultInput);
    
    if (strlen(resultInput) == 0) {
        mvwprintw(input_win, *line - 1, 3, messageEmpty);
        wrefresh(input_win);
    }
    (*line)++;
}

void getMultiLineInput(WINDOW* input_win, int* line, std::vector<std::string>* resultInputs, const char* message) {
    WINDOW *mainwin = derwin(input_win, 10, 52, *line, 1);
    box(mainwin, 0, 0);
    mvwprintw(mainwin, 1, 2, message);
    wrefresh(mainwin);

    WINDOW *xx = derwin(mainwin, 7, 38, 2, 2);
    scrollok(xx, true);

    char input[1024];
    int y = 0;
    while (true) {
        mvwgetnstr(xx, y, 0, input, sizeof(input));
        mvwprintw(xx, y, 0, input);
        wrefresh(xx);

        if (strlen(input) == 0) {
            if (y==0)
                mvwprintw(xx, y, 0, "(none)");
            
            break;
        } else {
            resultInputs->push_back(input);
        }

        y++;

        if (y >= 7) {
            wscrl(xx, 1);
            y--;
        }
    }

    scrollok(xx, false);
    wborder(mainwin, ' ', ' ', ' ',' ',' ',' ',' ',' '); // clear border
    wrefresh(mainwin);
    (*line) += y+2;
}

int getRadioInput(int* line, char *choices[], const char* message) {
    noecho();
    WINDOW *radio_win = newwin(3, 60, *line, 2);
    box(radio_win, 0, 0);
    wattron(radio_win, A_BOLD);
    mvwprintw(radio_win, 0, 2, message);
    wattroff(radio_win, A_BOLD);
    
    char msg0[100];
    snprintf(msg0, sizeof(msg0), "(x) %s", choices[0]);
    mvwprintw(radio_win, 1, 2, msg0);

    char msg1[100];
    snprintf(msg1, sizeof(msg1), "( ) %s", choices[1]);
    mvwprintw(radio_win, 1, 11, msg1);

    wrefresh(radio_win);

    int ch, choice = 0;
    
    curs_set(0); // hide cursor
    while (true)
    {
        // Highlight selected option
        if (choice == 0)
            mvwprintw(radio_win, 1, 2, "(x)");
        else
            mvwprintw(radio_win, 1, 2, "( )");
        
        if (choice == 1)
            mvwprintw(radio_win, 1, 11, "(x)");
        else
            mvwprintw(radio_win, 1, 11, "( )");

        wrefresh(radio_win);
        wmove(radio_win, 1, 6 + choice * 9);

        ch = wgetch(radio_win);
        if (ch == KEY_LEFT || ch == 67 || ch == KEY_RIGHT || ch == 68)
            choice++;
        else if (ch == '\n')
            break;
        
        if (choice > 1)
            choice = 0;
    }
    
    wborder(radio_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); // clear border
    wrefresh(radio_win);
    // remove radio_win
    delwin(radio_win);

    echo();
    curs_set(1); // show cursor

    return choice;
}

WINDOW* newWindow(int height, int width, int starty, int startx, const char* title) {
    auto input_win = newwin(height, width, starty, startx);
    box(input_win, 0, 0);
    int title_len = strlen(title);
    int start_col = (width - title_len) / 2;
    wattron(input_win, A_BOLD);
    mvwprintw(input_win, 0, start_col, title);
    wattroff(input_win, A_BOLD);
    wrefresh(input_win);
    return input_win;
}