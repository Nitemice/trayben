#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define TRAY_WINAPI 1
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define TRAY_APPINDICATOR 1
#elif defined(__APPLE__) || defined(__MACH__)
#define TRAY_APPKIT 1
#endif

#include "tray/tray.h"

#if TRAY_APPINDICATOR
#define TRAY_ICON "indicator-messages"
#elif TRAY_APPKIT
#define TRAY_ICON "tb.png"
#elif TRAY_WINAPI
#define TRAY_ICON "tb.ico"
#endif

static void quit_cb(struct tray_menu *item)
{
    tray_exit();
}

// Init tray icon
static struct tray tray = {
    .icon = TRAY_ICON,
#if TRAY_WINAPI
    .tooltip = "TrayBen",
#endif
    .menu =
        (struct tray_menu[]){
            {.text = "Quit", .cb = quit_cb},
            {.text = NULL}},
};

int main(int argc, const char *argv[])
{
    // tray.icon = argv[0];

    if (tray_init(&tray) < 0)
    {
        printf("failed to create tray\n");
        return 1;
    }

    while (tray_loop(1) == 0)
    {
    }
    return 0;
}
