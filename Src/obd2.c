#include "obd2.h"
#include "main.h"

/* Defines */

/* Global Variables */

/* Externs */

/* Private Function prototypes */


/* Function Definitions */

/* Takes a string of hex value(s): Service and PID. Populates the tx_data with
 * correct bytes. Pads remaining bytes with 0x55.
 *
 * Returns 0 on successful parse, -1 otherwise.
 */
int OBD2_Parse(char* input, uint8_t* tx_data) {
  char* service_end, pid_end;
  uint8_t value, count;
  int i;

  // There's always a service
  count = 1;

  value = strtol(input, &service_end, 16);
  // Check for valid service
  if (value < 1 || value > 0x0A) {
    return -1;
  }
  tx_data[TX_DATA_SERVICE] = value;

  value = strtol(service_end, &pid_end, 16);

  // TODO: Use service to check for valid pids

  // Check for valid 0x00 pid
  if (service_end != pid_end) {
    printf("Next value %x\r\n", value);
    tx_data[TX_DATA_PID] = value;
    count++;
  } else {
    printf("No next value\r\n");
  }

  tx_data[TX_DATA_NUM_BYTES] = count;

  // Pad remaining bytes with 0x55
  for (i = count + 1; i < TX_DATA_LENGTH; i++) {
    tx_data[i] = 0x55;
  }
  for (i = 0; i < TX_DATA_LENGTH; i++) {
    printf(" %02x", tx_data[i]);
  }
  printf("\r\n");

  return 0;
}

/* Prints the response from the ECU into a more readable form.
 */
void OBD2_PrintResponse(CAN_RxHeaderTypeDef* rx_header, uint8_t* rx_data) {
  int i;

  printf("[%03x]", rx_header->StdId);

  for (i = 0; i < RX_DATA_LENGTH; i++) {
    printf(" %02x", rx_data[i]);
  }
  printf("\r\n");
}
