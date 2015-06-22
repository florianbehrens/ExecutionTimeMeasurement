#include <thread>

#include "measurement.h"

int main()
{
    measurement m1(&std::this_thread::yield, std::chrono::seconds(1));
    m1();
    m1.print_report();
    return 0;
}
