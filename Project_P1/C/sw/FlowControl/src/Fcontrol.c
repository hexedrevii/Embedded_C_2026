#include "Fcontrol.h"
#include "Messages.h"
#include "Types.h"
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void send_can_frame(CANFrame* frame) {
    printf("Tx: ID=0x%lX DLC = %d Data=[ ", frame->id, frame->dlc);
    for (uint8 i = 0; i < frame->dlc; i++)
        printf("%02X ", frame->data[i]);
    printf("]\n");
}

void prepareMessageData(CANFrame* message)  {
        if (message->id == 0x40 || message->id == 0x12DD5528) 
        {
            // Split with the byte into nibbles.
            uint8 lower = message->data[2] & 0x0F;
            uint8 upper = message->data[2] & 0xF0;

            // Basic check for bounds? I didn't quite get the exercise...
            // But this should be fine?
            lower++;
            if (lower > 0x0F) {
                lower = 0x01;
            }

            // Put the byte back together.
            message->data[2] = upper | lower;

            for (uint8 b = 3; b < message->dlc; b++)
            {
                message->data[b] = rand() % 256;
            }
        }
}

void sendMessages()
{
    for(uint8 i = 0; i < MESSAGES_COUNT; i++)
    {
        CANFrame* message = &CAN_MESSAGES[i];
        prepareMessageData(message);
        send_can_frame(message);

        SLEEP_MS(message->cycles);
    }
}