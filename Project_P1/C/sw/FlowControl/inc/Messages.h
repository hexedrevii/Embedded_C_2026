#ifndef MESSAGES_H
#define MESSAGES_H
#include "Fcontrol.h"

#define MESSAGES_COUNT 2

extern uint8 messageCounter;
extern CANFrame LDA_FC1;
extern CANFrame LDA_FC2;
extern CANFrame CAN_MESSAGES[MESSAGES_COUNT];

static inline void initializeMessages() {
    CAN_MESSAGES[0] = LDA_FC1;
    CAN_MESSAGES[1] = LDA_FC2;
}

#endif /* MESSAGES_H */