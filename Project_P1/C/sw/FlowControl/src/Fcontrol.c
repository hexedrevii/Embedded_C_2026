#include "Fcontrol.h"
#include "Messages.h"


void send_can_frame(CANFrame frame) {
    printf("Tx: ID=0x%X DLC = %d Data=[ ", frame.id, frame.dlc);
    for (uint8 i = 0; i < CAN_CLS_SIZE; i++)
        printf("%02X ", frame.data[i]);
    printf("]\n");
}

void sendMessages()
{
    for(uint8 i=0; i<MESSAGES_COUNT; i++)    
    {
        send_can_frame(CAN_MESSAGES[i]);
        Sleep(150);
    }
}