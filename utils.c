#include <windows.h>
#include "utils.h"

long long GetCurrentTimeMS() {
    static LARGE_INTEGER frequency = {0};
    LARGE_INTEGER currentTime;
    if (frequency.QuadPart == 0) QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);
    return (long long)((currentTime.QuadPart * 1000) / frequency.QuadPart);
}
