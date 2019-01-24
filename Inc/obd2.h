#ifndef __obd2_H
#define __obd2_H

/* Includes */
#include "can.h"

/* Defines */
#define SCANNER_STDID     (0x7DF)

#define TX_DATA_LENGTH    (8)
#define RX_DATA_LENGTH    (8)
// Indices for rx_data/tx_data
#define RX_DATA_NUM_BYTES (0)
#define TX_DATA_NUM_BYTES (0)
#define TX_DATA_SERVICE   (1)
#define TX_DATA_PID       (2)

/* Function Prototypes */
int OBD2_Parse(char* input, uint8_t* tx_data);
void OBD2_PrintResponse(CAN_RxHeaderTypeDef* rx_header, uint8_t* rx_data);

#endif  /*__obd2_H */
