/*
 * File: searcht.cpp
 * -----------------------------------------------------------------------------
 * This file is part of the File Search Program - (c) 2023 by C. Klukas
 *
 * Licensed under the MIT License and the GNU General Public License, Version 3.
 *
 * For details, see the accompanying COPYING file or visit:
 * - MIT License: https://opensource.org/licenses/MIT
 * - GPLv3: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * Project repository: https://github.com/cklukas/C--
 *
 * Author: Christian Klukas
 */
#define Uses_TApplication
#define Uses_TDeskTop
#define Uses_TRect
#define Uses_TStaticText
#define Uses_MsgBox

#define Uses_TKeys
#define Uses_TEvent
#define Uses_TDialog
#define Uses_TMenu
#define Uses_TMenuItem
#define Uses_TSubMenu
#define Uses_TMenuBar
#define Uses_TProgram
#define Uses_TScreen
#define Uses_TDrawSurface
#define Uses_TButton

#include <tvision/tv.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#include "system_info_window.hpp"
#include "modules/SystemInfo.hpp"
#include "modules/load/SystemLoad.hpp"
#include "modules/cpu/CpuLoad.hpp"

const int cmAboutCmd = 100; // User selected menu item 'About'
const int cmLoadCmd = 101;  // User selected menu item 'System Load'
const int cmCpuCmd = 102;   // User selected menu item 'CPU Load'
const int cmFileSearchCmd = 103;   // User selected menu item 'File/Search'

// This class is used to manage the application state for the System Load Window.
// It includes functionality to periodically update the system load and redraw the System Load Window.
class SystemLoadApp : public TApplication
{
public:
    static TMenuBar *initMenuBar(TRect);
    void handleEvent(TEvent &) override;

    SystemLoadApp(std::vector<double> &systemLoadVector)
        : TProgInit(&TApplication::initStatusLine, 
                    &SystemLoadApp::initMenuBar,
                    &TApplication::initDeskTop),
          TApplication(),
          lastUpdate(std::chrono::system_clock::now())
    {
        TRect r1(0, 0, 50, 20);
        r1.move((TScreen::screenWidth - r1.b.x) / 2 - 55, (TScreen::screenHeight - r1.b.y) / 2);

        systemLoadWindow = std::make_unique<SystemInfoWindow>(r1, std::make_unique<SystemLoad>());
        if (validView(systemLoadWindow.get()) != 0)
        {
            deskTop->insert(systemLoadWindow.get());
        }

        TRect r2(0, 0, 50, 20);
        r2.move((TScreen::screenWidth - r2.b.x) / 2 + 5, (TScreen::screenHeight - r2.b.y) / 2);

        cpuLoadWindow = std::make_unique<SystemInfoWindow>(r2, std::make_unique<CpuLoad>());
        if (validView(systemLoadWindow.get()) != 0)
        {
            deskTop->insert(cpuLoadWindow.get());
        }
    }

    // This method is called periodically when the application is idle.
    // It fetches the latest system load, updates the system load vector, and redraws the System Load Window.
    void idle() override
    {
        if ((systemLoadWindow->state & sfExposed) == sfExposed ||
            (cpuLoadWindow->state & sfExposed) == sfExposed)
        {
            auto now = std::chrono::system_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count() >= 1)
            {
                if ((systemLoadWindow->state & sfExposed) == sfExposed)
                    systemLoadWindow->idle();
                
                if ((cpuLoadWindow->state & sfExposed) == sfExposed)
                    cpuLoadWindow->idle();

                lastUpdate = now;
            }
        }
        TApplication::idle();
    }

private:
    std::chrono::system_clock::time_point lastUpdate;
    std::unique_ptr<SystemInfoWindow> systemLoadWindow;
    std::unique_ptr<SystemInfoWindow> cpuLoadWindow;

    void aboutDlg();
};

TMenuBar *SystemLoadApp::initMenuBar(TRect bounds)
{
    bounds.b.y = bounds.a.y + 1;

    return new TMenuBar(bounds,
                        *new TSubMenu("~F~ile", kbAltF) +
                            *new TMenuItem("~S~earch", cmFileSearchCmd, kbAltS, hcNoContext, "Alt-S") +
                            newLine() +
                            *new TMenuItem("E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X") +
                        *new TSubMenu("~S~ystem", kbAltF) +
                            *new TMenuItem("~L~oad", cmLoadCmd, kbAltL, hcNoContext, "Alt-L") +
                            *new TMenuItem("~C~PUs", cmCpuCmd, kbAltC, hcNoContext, "Alt-C") +
                        *new TSubMenu("~H~elp", kbAltH) +
                            *new TMenuItem("~A~bout", cmAboutCmd, kbAltA, hcNoContext, "F1")
                        );
}

void SystemLoadApp::handleEvent(TEvent &event)
{
    TApplication::handleEvent(event);

    if (event.what == evCommand)
    {
        switch (event.message.command)
        {
        case cmLoadCmd:
        {
            systemLoadWindow->select();
            clearEvent(event);
            break;
        }
        case cmCpuCmd:
        {
            cpuLoadWindow->select();
            clearEvent(event);
            break;
        }
        case cmAboutCmd:
        {
            aboutDlg();
            clearEvent(event);
            break;
        }
        }
    }
}

void SystemLoadApp::aboutDlg()
{
    TDialog *pd = new TDialog(TRect(0, 0, 35, 12), "About");
    if (pd)
    {
        pd->options |= ofCentered;
        pd->insert(new TStaticText(TRect(1, 2, 34, 7),
                                   "\003CK System Utilities\n\003\n\003Version 1.0\n\003\n"
                                   "\003© 2023 by C. Klukas\n\003\n"));
        pd->insert(new TButton(TRect(3, 9, 32, 11), "~O~k", cmOK, bfDefault));

        if (validView(pd) != 0)
        {
            deskTop->execView(pd);

            destroy(pd);
        }
    }
}

// The main entry point of the program.
// It initializes an empty system load vector, creates a SystemLoadApp instance, and runs the application.
int main()
{
    std::vector<double> systemLoadVector = {};
    SystemLoadApp systemLoadApp(systemLoadVector);
    systemLoadApp.run();
    return 0;
}

// compile on Mac: g++ -std=c++14  -o searcht searcht.cpp -ltvision -Iinclude -lncurses
// g++ -g -std=c++14  -o searcht searcht.cpp -ltvision -Iinclude -lncurses && ./searcht
// lldb ./searcht
//
// ioreg -l | grep -i "gpu"

//
// autoreconf -f -i
// ./configure --enable-searcht
// make
//

// cd src
// g++ -std=c++14 -Imodules searcht.cpp modules/cpu/*.cpp modules/load/*.cpp -ltvision  -lncurses -o searcht