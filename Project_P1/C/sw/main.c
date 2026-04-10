#include "Fcontrol.h"
#include "Messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  Pentru build Windows: CTRL+SHIFT+P (Raw cl.exe)
  Pentru build Linux/MacOS: Build/Run in jos-stanga (CMake)
*/
int main(void) {
    srand(time(NULL));

    initializeMessages();

    printf("Sending messages: \n");
    for(;;) {
        sendMessages();
    }
    return 0;
}