extern "C" void run_device_specific_code();
#include <notify/notify.h>

void run_device_specific_code()
{
    //Run some device specific code
    notify("Executed device specific code!");
}