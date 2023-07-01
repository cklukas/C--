/*
 * File: system_load_window.cpp
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

SystemInfoWindow::SystemInfoWindow(
    const TRect &bounds,
    std::unique_ptr<ISystemInfo> systemInfo) : TWindowInit(&TWindow::initFrame),
                                               TWindow(bounds, systemInfo->getTitle(-1), wnNoNumber),
                                               systemInfo(std::move(systemInfo))
{
}

SystemInfoWindow::~SystemInfoWindow()
{
    delete &systemInfo;
}

void SystemInfoWindow::idle()
{
    // get window width
    int width = this->size.x;
    systemInfo->idle(width - 2);
    redraw();
    draw();
}

const char *SystemInfoWindow::getTitle(short maxSize)
{
    this->title = this->systemInfo->getTitle(maxSize);
    return this->title.c_str();
}

// This method draws load bars proportional to the system load at a certain time point.
void SystemInfoWindow::drawLoadBars()
{
    auto systemLoad = this->systemInfo->getInfoValues();
    int width = this->size.x;

    auto maxValue = this->systemInfo->getMaxValue();

    // determine Y axis labels
    //
    auto middleVal = maxValue / 2;
    // format the values to be displayed as a string with one decimal place
    std::stringstream maxYstr;
    maxYstr << std::fixed << std::setprecision(1) << maxValue;
    std::stringstream middleYstr;
    middleYstr << std::fixed << std::setprecision(1) << middleVal;
    // check if maxYstr and middleYstr both end with ".0", if yes, remove that
    auto maxValStrEndsWithZero = maxYstr.str().substr(maxYstr.str().size() - 2) == ".0";
    auto middleValStrEndsWithZero = middleYstr.str().substr(middleYstr.str().size() - 2) == ".0";
    if (maxValStrEndsWithZero && middleValStrEndsWithZero)
    {
        maxYstr.str(maxYstr.str().substr(0, maxYstr.str().size() - 2));
        middleYstr.str(middleYstr.str().substr(0, middleYstr.str().size() - 2));
    }
    //
    // Y axis labels are now determined

    // draw a line at middle of window and top
    // using writeBuf
    // create a string of "·" with the length of the window
    std::string lineString;
    for (int i = 0; i < width - 2; ++i)
        if (i > middleYstr.str().size()) //  && (i%2==0)
            lineString += "·";
        else
            lineString += " ";
        
    TDrawBuffer b;
    b.moveStr(0, lineString, getColor(1));
    writeBuf(1, size.y/2, size.x-2, 1, b);


    // draw histogram
    //
    ushort color = getColor(4);
    for (size_t i = 0; i < width - 2; ++i)
    {
        // Ensure that we don't go out of bounds of the systemLoad vector
        if (i < systemLoad.size())
        {
            int load;
            if (maxValue < 0)
                load = systemLoad[systemLoad.size() - 1 - i] * 5.0;
            else
                load = systemLoad[systemLoad.size() - 1 - i] * (size.y - 2) / maxValue;
            
            load = std::max(0, std::min(load, size.y - 1));
            for (int y = 0; y < load; ++y)
            {
                TDrawBuffer b;
                if (y < size.y - 2)
                    b.moveStr(0, " ", color, 1);
                    writeLine(width - i - 2, size.y - y - 2, 1, 1, b);
            }
        }
    }

    // draw Y axis labels
    //
    ushort colorF = getColor(1);
    ushort colorT = getColor(4);

    auto strMaxLen = maxYstr.str().size();
    auto strMidLen = middleYstr.str().size();
    
    bool* maxLoadCoversMaxVal = this->systemInfo->getCoverFlags(size.x-2, strMaxLen, maxValue);
    bool* maxLoadCoversMidVal = this->systemInfo->getCoverFlags(size.x-2, strMidLen, maxValue/2);
    
    TDrawBuffer maxValBuffer;
    
    for (int i = 0; i < strMaxLen; ++i)
    {
        TDrawBuffer b;
        b.moveChar(0, maxYstr.str()[i], maxLoadCoversMaxVal[i] ? colorT : colorF, 1);
        writeBuf(i + 1, 1, 1, 1, b);
    }
    
    
    TDrawBuffer middleValBuffer;
    for (int i = 0; i < strMidLen; ++i)
    {
        TDrawBuffer b;
        b.moveChar(0, middleYstr.str()[i], maxLoadCoversMidVal[i] ? colorT : colorF, 1);
        writeBuf(i + 1, size.y / 2, 1, 1, b);
    }
    delete(maxLoadCoversMaxVal);
    delete(maxLoadCoversMidVal);

    auto debug = False;
    if (debug) {
        // from top to bottom write a number 0 to 9
        // usign the color 0 to 9
        // using writeBuf
        for (int i = 0; i < size.y - 2; ++i)
        {
            TDrawBuffer b;
            b.moveStr(0, std::to_string(i).c_str(), getColor(i));
            writeBuf(15, size.y - i - 2, 2, 1, b);
        }
    }
}

// This method draws the system load window, including its title and load bars.
void SystemInfoWindow::draw()
{
    TWindow::draw();
    drawLoadBars();
}

void SystemInfoWindow::close()
{
    // exit(EXIT_SUCCESS);
    TWindow::close();
}

#include <iostream>

void SystemInfoWindow::setState( ushort aState, Boolean enable )
{
    TWindow::setState(aState, enable);
    if ((aState  & sfSelected) == sfSelected)
        draw();
}
