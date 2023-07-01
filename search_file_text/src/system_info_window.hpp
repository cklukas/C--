/*
 * File: system_load_window.hpp
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
#ifndef SYSTEM_LOAD_WINDOW_HPP
#define SYSTEM_LOAD_WINDOW_HPP

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
#include "modules/SystemInfo.hpp"

class SystemInfoWindow : public TWindow
{
public:
    typedef std::function<const std::string(short)> GetTitleFunc;

    SystemInfoWindow(const TRect& bounds, std::unique_ptr<ISystemInfo> systemInfo);
    ~SystemInfoWindow();
    virtual void setState( ushort aState, Boolean enable ) override;
    virtual const char* getTitle(short maxSize) override;
    void drawLoadBars();
    void draw() override;
    virtual void close() override;
    void idle();
public:
    std::unique_ptr<ISystemInfo> systemInfo;
    std::string title;
};

#endif // SYSTEM_LOAD_WINDOW_HPP