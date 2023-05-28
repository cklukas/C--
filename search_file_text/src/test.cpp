#include <iostream>
#include <fstream>

#include <iostream>
#include <cstring> // For strerror
#include <cerrno>  // For errno
#include <sys/sysctl.h>

#include <sys/sysctl.h>
#include <mach/mach_types.h>
 
double getSystemLoad() {
    struct loadavg load;
    size_t len = sizeof(load);

    int mib[2];
    mib[0] = CTL_VM;
    mib[1] = VM_LOADAVG;

    if (sysctl(mib, 2, &load, &len, nullptr, 0) != -1) {
        return load.ldavg[0]/(double)load.fscale;
    } else {
        std::cerr << "Error retrieving system load: " << strerror(errno) << std::endl;
    }

    // Error reading load average or unsupported platform
    return -1.0;
}

int main() {
    double systemLoad = getSystemLoad();
    if (systemLoad >= 0.0) {
        std::cout << "System Load: " << systemLoad << std::endl;
    } else {
        std::cout << "Failed to retrieve system load." << std::endl;
    }

    return 0;
}
    
