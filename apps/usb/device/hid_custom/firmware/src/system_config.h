#include "usb_config.h"
#include "fileio_config.h"

#define mInitCCP_PIN()          TRISCbits.TRISC6 = 0; 
#define CCP9_PORT               PORTCbits.RC6



