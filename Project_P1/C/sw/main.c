#include "Fcontrol.h"
#include "Messages.h"
#include <stdio.h>


/*Pentru build: CTRL+SHIFT+B*/
int main(void) {
    initializeMessages();

    printf("Sending messages: \n");
    for(;;) {
        sendMessages();
    }
    return 0;
}