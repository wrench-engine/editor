#include <wrench_editor/utils/sleep.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace wrench_editor
{
void sleep_microseconds(long long microseconds)
{
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    const long long ticksToWait = (microseconds * frequency.QuadPart) / 1000000;

    if (ticksToWait <= 0) {
        return;
    }
    do {
        QueryPerformanceCounter(&end);
    } while (end.QuadPart - start.QuadPart < ticksToWait);
#else
    usleep(microseconds);
#endif
}
} // namespace wrench_editor
