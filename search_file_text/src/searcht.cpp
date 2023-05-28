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

#include <tvision/tv.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#ifdef __linux__
// Linux-specific code
#elif __APPLE__
// macOS-specific code
#include <sys/sysctl.h>
#endif

// This function is used to fetch the system load depending on the operating system in use.
double getSystemLoad()
{
    struct loadavg load;

#ifdef __linux__
    // Linux-specific code
    std::ifstream loadavg("/proc/loadavg");
    if (loadavg >> load)
    {
        return load;
    }
#elif __APPLE__
    // macOS-specific code

    int mib[2];
    size_t len = sizeof(load);
    mib[0] = CTL_VM;
    mib[1] = VM_LOADAVG;

    if (sysctl(mib, 2, &load, &len, nullptr, 0) != -1)
    {
        return load.ldavg[0] / (double)load.fscale;
    }
#endif

    // Error reading load average or unsupported platform
    return -1.0;
}

// This class is used to create a System Load Window.
// It's a graphical representation of the system load over time.
class SystemLoadWindow : public TWindow
{

public:
    SystemLoadWindow(const TRect &bounds, std::vector<double> &systemLoad)
        : TWindow(bounds, "System Load", wnNoNumber), TWindowInit(&TWindow::initFrame), systemLoad(systemLoad)
    {
    }

    virtual const char *getTitle(short maxSize) override
    {
        // check if the systemLoad vector is empty
        if (this->systemLoad.empty())
        {
            return TWindow::getTitle(maxSize);
        }
        else
        {
            double load = systemLoad.back();
            std::stringstream ss;
            ss << "System Load (" << std::fixed << std::setprecision(2) << load << ")";

            // if length of ss is > maxSize, then truncate it and add "..." to the end
            if (ss.str().length() > maxSize)
            {
                std::string truncated = ss.str().substr(0, maxSize - 3);
                truncated += "...";
                this->title = ss.str();
            }
            else
            {
                // to avoid warning: address of stack memory associated with local variable 'truncated' returned
                // we need to return a c_str() of a string that is not local to this function
                std::string truncated = ss.str();
                this->title = truncated;
            }
            return this->title.c_str();
        }
    }

    // This method draws load bars proportional to the system load at a certain time point.
    void drawLoadBars()
    {
        int width = this->size.x;
        

        ushort color = getColor(0x0302);
        for (size_t i = 0; i < width-2; ++i)
        {
            // Ensure that we don't go out of bounds of the systemLoad vector
            if (i < systemLoad.size())
            {
                int load = systemLoad[systemLoad.size() - 1 - i] * 5.0;
                load = std::max(0, std::min(load, size.y - 1));
                for (int y = 0; y < load; ++y)
                {
                    TDrawBuffer b;
                    b.moveStr(0, "▓", color, 1);
                    if (y < size.y - 2)
                        writeLine(width - i - 2, size.y - y - 2, 1, 1, b);
                }
            }
        }
    }

    // This method draws the system load window, including its title and load bars.
    void draw() override
    {
        TWindow::draw();
        drawLoadBars();
    }

    virtual void close() override
    {
        exit(EXIT_SUCCESS);
        TWindow::close();
    }

private:
    std::vector<double> &systemLoad;
    mutable std::string title;
};

// This class is used to manage the application state for the System Load Window.
// It includes functionality to periodically update the system load and redraw the System Load Window.
class SystemLoadApp : public TApplication
{

public:
    SystemLoadApp(std::vector<double> &systemLoadVector)
        : TApplication(), TProgInit(&TApplication::initStatusLine, &TApplication::initMenuBar,
                                    &TApplication::initDeskTop),
          systemLoadVector(systemLoadVector)
    {
        lastUpdate = std::chrono::system_clock::now();
        TRect r(0, 0, 50, 20);
        r.move((TScreen::screenWidth - r.b.x) / 2, (TScreen::screenHeight - r.b.y) / 2);
        w = new SystemLoadWindow(r, systemLoadVector);
        if (validView(w) != 0)
        {
            deskTop->insert(w);
        }
    }

    // This method is called periodically when the application is idle.
    // It fetches the latest system load, updates the system load vector, and redraws the System Load Window.
    void idle() override
    {
        // check if w is null
        if (w != nullptr && w->valid(0))
        {
            auto now = std::chrono::system_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count() >= 1)
            {
                float load = getSystemLoad();
                if (load >= -2.0)
                {
                    // Successfully read load average, update systemLoad vector.
                    systemLoadVector.push_back(static_cast<double>(load));
                    // get terminal width
                    int width = TScreen::screenWidth;
                    if (systemLoadVector.size() > width)
                    {
                        // Keep the size of the vector to width.
                        systemLoadVector.erase(systemLoadVector.begin());
                    }
                }
                lastUpdate = now;
                w->redraw();
                w->draw();
            }
        }
        TApplication::idle();
    }

private:
    std::vector<double> &systemLoadVector;
    std::chrono::system_clock::time_point lastUpdate;
    SystemLoadWindow *w;
};

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