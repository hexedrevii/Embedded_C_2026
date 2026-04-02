#ifndef FCONTROL_H
#define FCONTROL_H
#include <stdio.h>
#include <string.h>
#include <windows.h> 
#include "Types.h"

// Constants for CAN frame
#define CAN_CLS_SIZE 8  // 8-byte CAN payload

/**
 * Structura corespondenta unui mesaj de CAN de tip clasic
 * DLC-ul este maxim 8 bytes
 */
typedef struct {
    uint8 id;                             // CAN ID
    uint8 data[CAN_CLS_SIZE];             // Data array
    uint8 dlc;                            // Data Length Code  
} CANFrame;

void send_can_frame(CANFrame frame);
void sendMessages();
#endif /* FCONTROL_H */