#include "Fcontrol.h"
#include "Messages.h"

#define LDA_GENERIC_CYCLE 150

/*LDA_FC1 Message*/
#define LDA_FC1_IDENT 0x12u
#define LDA_FC1_DLC 8u

CANFrame LDA_FC1 = {
    LDA_FC1_IDENT,                                             // id
    {0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},          // data
    LDA_FC1_DLC,                                                // dlc
    LDA_GENERIC_CYCLE
};

/*LDA_FC2 Message*/
#define LDA_FC2_IDENT 0xABu
#define LDA_FC2_DLC 8u

CANFrame LDA_FC2 = {
    LDA_FC2_IDENT,                                              // id
    {0x00, 0x00, 0xFF, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE},           // data
    LDA_FC2_DLC,                                                 // dlc
    LDA_GENERIC_CYCLE
};

#define LDA_FC3_IDENT 0x40
#define LDA_FC3_DLC 16u
#define LDA_FC3_CYCLE 40

CANFrame LDA_FC3 = {
    LDA_FC3_IDENT,
    { 0x0, 0x67, 0x01, /* Random from here, generated inside the program! */},
    LDA_FC3_DLC,
    LDA_FC3_CYCLE
};

#define LDA_FC4_IDENT 0x12DD5528
#define LDA_FC4_DLC 64u
#define LDA_FC4_CYCLE 80

CANFrame LDA_FC4 = {
    LDA_FC4_IDENT,
    { 0x1, 0x67, 0x01, /* Same story as before */},
    LDA_FC4_DLC,
    LDA_FC4_CYCLE
};

CANFrame CAN_MESSAGES[MESSAGES_COUNT];