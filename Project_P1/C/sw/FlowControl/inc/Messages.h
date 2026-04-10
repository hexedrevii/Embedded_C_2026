#ifndef MESSAGES_H
#define MESSAGES_H
#include "Fcontrol.h"

#define MESSAGES_COUNT 4

extern uint8 messageCounter;
extern CANFrame LDA_FC1;
extern CANFrame LDA_FC2;
extern CANFrame LDA_FC3;
extern CANFrame LDA_FC4;
extern CANFrame CAN_MESSAGES[MESSAGES_COUNT];

static inline void initializeMessages() {
    CAN_MESSAGES[0] = LDA_FC1;
    CAN_MESSAGES[1] = LDA_FC2;
    CAN_MESSAGES[2] = LDA_FC3;
    CAN_MESSAGES[3] = LDA_FC4;
}

#endif /* MESSAGES_H */