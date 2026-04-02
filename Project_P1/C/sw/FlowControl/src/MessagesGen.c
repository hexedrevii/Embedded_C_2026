#include "Messages.h"

/*LDA_FC1 Message*/
#define LDA_FC1_IDENT 0x12u
#define LDA_FC1_DLC 8u

CANFrame LDA_FC1 = {
    LDA_FC1_IDENT,                                             // id
    {0x00, 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},          // data
    LDA_FC1_DLC                                                // dlc
};

/*LDA_FC2 Message*/
#define LDA_FC2_IDENT 0xABu
#define LDA_FC2_DLC 8u

CANFrame LDA_FC2 = {
    LDA_FC2_IDENT,                                              // id
    {0x00, 0x00, 0xFF, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE},           // data
    LDA_FC2_DLC                                                 // dlc
};

CANFrame CAN_MESSAGES[MESSAGES_COUNT];