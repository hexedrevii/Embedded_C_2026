#ifndef FCONTROL_H
#define FCONTROL_H
#include <stdio.h>
#include <string.h>
#include "Types.h"

// Constants for CAN frame
#define CAN_FD_MAX_SIZE 64

/**
 * Structura corespondenta unui mesaj de CAN de tip clasic
 * DLC-ul este maxim 8 bytes
 */
typedef struct {
    uint64 id;                               // CAN ID
    uint8 data[CAN_FD_MAX_SIZE];             // Data array
    uint8 dlc;                               // Data Length Code
    uint8 cycles;                            // Cycle count
} CANFrame;

void send_can_frame(CANFrame* frame);
void prepareMessageData(CANFrame* message);
void sendMessages();
#endif /* FCONTROL_H */