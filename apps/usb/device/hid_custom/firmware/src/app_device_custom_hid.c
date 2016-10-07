/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"

#include <string.h>

#include "system.h"
#include "internal_flash.h"


/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #else defined(__XC8)
        unsigned char ReceivedDataBuffer[64] @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

/** DEFINITIONS ****************************************************/
typedef enum
{
    COMMAND_GET_CONFIG = 0x80,
    COMMAND_SET_CONFIG = 0x81,
    COMMAND_LOAD_CONFIG = 0x82,
    COMMAND_SAVE_CONFIG = 0x83,
    COMMAND_GET_FALGS = 0x84,
    COMMAND_SET_FALGS = 0x85,
} CUSTOM_HID_DEMO_COMMANDS;


extern APP_CONFIG AppConfig;

/** FUNCTIONS ******************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,(uint8_t*)&ReceivedDataBuffer,64);
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks()
{   
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false)
    {   
        //We just received a packet of data from the USB host.
        //Check the first uint8_t of the packet to see what command the host
        //application software wants us to fulfill.
        switch(ReceivedDataBuffer[0])				//Look at the data the host sent, to see what kind of application specific command it sent.
        {
            case COMMAND_SET_CONFIG:
            {
                uint8_t * Temp;                        
                uint16_t j = 1;
                //ToSendDataBuffer[0] = COMMAND_SET_CONFIG;				//Echo back to the host PC the command we are fulfilling in the first uint8_t.  In this case, the Get Pushbutton State command.                    
                //memcpy(&ToSendDataBuffer[1],&AppConfig,sizeof(AppConfig));
                Temp = (uint8_t *)&AppConfig;                    
                for(uint16_t i = 0; i< sizeof(APP_CONFIG); i++){
                    Temp[i] = ReceivedDataBuffer[j];
                    j++;
                }
                CCP9Init(&AppConfig);
                LED_Toggle(LED_D2);
                break;
            }
            case COMMAND_GET_CONFIG:	//Read config
            {
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    uint8_t * Temp;                        
                    uint16_t j = 1;
                    ToSendDataBuffer[0] = COMMAND_GET_CONFIG;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
                    Temp = (uint8_t *)&AppConfig;
                    GetStatusFlags(&AppConfig.StatusFlags);
                    memset(&ToSendDataBuffer[1], 0, sizeof(ToSendDataBuffer)-1);    
                    for(uint16_t i = 0; i< sizeof(APP_CONFIG); i++){
                        ToSendDataBuffer[j] = Temp[i];
                        j++;
                    }
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
            }
            break;
            case COMMAND_LOAD_CONFIG:	//Load config
            {
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    uint8_t * Temp;                        
                    uint16_t j = 1;
                    ToSendDataBuffer[0] = COMMAND_GET_CONFIG;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
                    LoadCfg(&AppConfig);
                    Temp = (uint8_t *)&AppConfig;
                    memset(&ToSendDataBuffer[1], 0, sizeof(ToSendDataBuffer)-1); 
                    for(uint16_t i = 0; i< sizeof(APP_CONFIG); i++){
                        ToSendDataBuffer[j] = Temp[i];
                        j++;
                    }

                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
            }
            break;
            case COMMAND_SAVE_CONFIG:  
            {
                uint8_t * Temp;                        
                uint16_t j = 1;
                Temp = (uint8_t *)&AppConfig;

                for(uint16_t i = 0; i< sizeof(APP_CONFIG); i++){
                    Temp[i] = ReceivedDataBuffer[j];
                    j++;
                }
                CCP9Init(&AppConfig);
                LED_Toggle(LED_D2);
                SaveCfg(&AppConfig);                                        
            }
            break; 
            case COMMAND_GET_FALGS:	//Read config
            {
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    uint8_t * Temp;                        
                    uint16_t j = 1;
                    ToSendDataBuffer[0] = COMMAND_GET_FALGS;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
                    GetStatusFlags(&AppConfig.StatusFlags);
                    Temp = (uint8_t *)&AppConfig.StatusFlags;
                    memset(&ToSendDataBuffer[1], 0, sizeof(ToSendDataBuffer)-1);                         
                    for(uint16_t i = 0; i< sizeof(STATUS_FLAGS); i++){
                        ToSendDataBuffer[j] = Temp[i];
                        j++;
                    }
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
            }
            break;
            case COMMAND_SET_FALGS:  
            {
                uint8_t * Temp;                        
                uint16_t j = 1;
                Temp = (uint8_t *)&AppConfig.StatusFlags;

                for(uint16_t i = 0; i< sizeof(STATUS_FLAGS); i++){
                    Temp[i] = ReceivedDataBuffer[j];
                    j++;
                }
                CCP9Init(&AppConfig);
                LED_Toggle(LED_D2);
            }
            break; 
        }
        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer, 64);
    }
}