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

#include <xc.h>
#include "system.h"
#include "system_config.h"
#include "usb.h"
#include "leds.h"
#include "buttons.h"
#include "Stepper.h"
//#include "fileio.h"
#include "driver/fileio/internal_flash.h"
#include "rtcc.h"


/** CONFIGURATION Bits **********************************************/
#pragma config WDTEN = OFF          //WDT disabled (enabled by SWDTEN bit)
#pragma config PLLDIV = 4          //Divide by 4 (12 MHz oscillator input)
#pragma config STVREN = ON          //stack overflow/underflow reset enabled
#pragma config XINST = OFF          //Extended instruction set disabled
#pragma config CPUDIV = OSC1        //No CPU system clock divide
#pragma config CP0 = OFF            //Program memory is not code-protected
#pragma config OSC = HSPLL          //HS oscillator, PLL enabled, HSPLL used by USB
#pragma config FCMEN = OFF          //Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF           //Two-Speed Start-up disabled
#pragma config WDTPS = 32768        //1:32768
#pragma config DSWDTOSC = INTOSCREF //DSWDT uses INTOSC/INTRC as clock
#pragma config RTCOSC = INTOSCREF   //RTCC uses T1OSC/T1CKI as clock
#pragma config DSBOREN = OFF        //Zero-Power BOR disabled in Deep Sleep
#pragma config DSWDTEN = OFF        //Disabled
#pragma config DSWDTPS = 2048       //1:8,192 (8.5 seconds)
#pragma config IOL1WAY = OFF        //IOLOCK bit can be set and cleared
#pragma config MSSP7B_EN = MSK7     //7 Bit address masking
#pragma config WPFP = PAGE_1        //Write Protect Program Flash Page 0
#pragma config WPEND = PAGE_0       //Start protection at page 0
#pragma config WPCFG = OFF          //Write/Erase last page protect Disabled
#pragma config WPDIS = OFF          //WPFP[5:0], WPEND, and WPCFG bits ignored
#pragma config CFGPLLEN = ON



// This structure must be maintained as long as the user wishes to access the specified drive.
const FILEIO_DRIVE_CONFIG InternalFlashDrive =
{
    (FILEIO_DRIVER_IOInitialize) NULL,                                      // I/O Initialization function
    (FILEIO_DRIVER_MediaDetect) FILEIO_InternalFlash_MediaDetect,           // Media Detection function
    (FILEIO_DRIVER_MediaInitialize) FILEIO_InternalFlash_MediaInitialize,   // Media Initialization function
    (FILEIO_DRIVER_MediaDeinitialize) NULL,                                 // Media Deinitialization function.
    (FILEIO_DRIVER_SectorRead) FILEIO_InternalFlash_SectorRead,                        // Function to read a sector of the media.
    (FILEIO_DRIVER_SectorWrite) FILEIO_InternalFlash_SectorWrite,                      // Function to write a sector of the media.
    (FILEIO_DRIVER_WriteProtectStateGet) FILEIO_InternalFlash_WriteProtectStateGet         // Function to determine if the media is write-protected.
};

#define STAR_DAY_LENGHT     86164.090530833
#define MAIN_GEAR_COG_COUNT 360
#define REDUCTION_RATIO     20
#define SM_STEP_CONT        200
#define SM_MICRO_STEP_COUNT 16
#define SM_PULSE_WIDTH      1000 // STEP minimum, HIGH pulse width, microseconds 
#define INTERVAL            5609
#define INTERVAL_1KK        641310
#define INTERVAL_1KK_MAX    1000000

// Application-dependent structure used to contain address information
typedef struct 
{
    double StarDayLength;
    uint16_t MainGearCogsCount;     // 
                                    // 
    uint16_t GearRatio;             // 
    uint16_t SM_StepCount;          // 
    uint16_t SM_uStepCount;         // 
    int16_t IntervalCorrection;     // 
    int32_t IntervalCorrection_1kk;    //
    uint16_t PulseWidth;
    uint16_t Interval;
    uint32_t Interval_1kk;

} APP_CONFIG;

typedef struct 
{
    uint16_t IntervalCounter;        // 
    uint32_t IntervalCounter_1kk;
    bool     State;
} APP_WORK;


APP_CONFIG AppDefault = {
    (double)STAR_DAY_LENGHT, MAIN_GEAR_COG_COUNT,REDUCTION_RATIO,SM_STEP_CONT,SM_MICRO_STEP_COUNT, 0, 0, SM_PULSE_WIDTH, INTERVAL, INTERVAL_1KK
};


void Timer1Init(void);
void CCP9Init(void);
void Timer1Process(void);
void CCP9Process(void);
void LoadCfg(void);
// GetTimestamp will be called by the FILEIO library when it needs a timestamp for a file
void GetTimestamp (FILEIO_TIMESTAMP * timeStamp);
// Helper function to initialize the RTCC from the compiler timestamp
void RTCCInit (void);
void AppParamCalc(APP_CONFIG * config, APP_WORK * workparam);


APP_CONFIG AppConfig;
APP_WORK   AppWork;

/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize( SYSTEM_STATE state )
{
    switch(state)
    {
        case SYSTEM_STATE_DEVICE_INIT:
            Timer1Init();
            CCP9Init();
            break;
        case SYSTEM_STATE_CFG_LOAD:
            LoadCfg();    
            break;
        case SYSTEM_STATE_USB_START:
             //In this devices family of USB microcontrollers, the PLL will not power up and be enabled
             //by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
             //This allows the device to power up at a lower initial operating frequency, which can be
             //advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
             //operation.  On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit to
             //power up the PLL.
             {
                 unsigned int pll_startup_counter = 600;
                 OSCTUNEbits.PLLEN = 1;  //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
                 while(pll_startup_counter--);
             }
             //Device switches over automatically to PLL output after PLL is locked and ready.
			 
            LED_Enable(LED_USB_DEVICE_STATE);
            LED_Enable(LED_USB_DEVICE_HID_CUSTOM);
            
            BUTTON_Enable(BUTTON_USB_DEVICE_HID_CUSTOM);
            
            //ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
            //ADC_Enable(ADC_CHANNEL_POTENTIOMETER);
            break;
        case SYSTEM_STATE_USB_SUSPEND: 
            break;
            
        case SYSTEM_STATE_USB_RESUME:
            OSCCON = 0x70;		//Primary clock source selected.
            
            //Adding a software start up delay will ensure
            //that the primary oscillator and PLL are running before executing any other
            //code.  If the PLL isn't being used, (ex: primary osc = 48MHz externally applied EC)
            //then this code adds a small unnecessary delay, but it is harmless to execute anyway.
            {
                unsigned int pll_startup_counter = 800;	//Long delay at 31kHz, but ~0.8ms at 48MHz
                while(pll_startup_counter--);			//Clock will switch over while executing this delay loop
            }
            break;
    }
}

			
			
#if defined(__XC8)
void interrupt SYS_InterruptHigh(void)
{
    Timer1Process();
    CCP9Process();

    #if defined(USB_INTERRUPT)
        USBDeviceTasks();
    #endif
}

void Timer1Init(void)
{

    T1CON = 0x00;
    T1CONbits.TMR1CS = 0;   // Timer1 clock source is the instruction clock (FOSC/4)
    T1CONbits.T1CKPS = 3;   // 1:8 Prescale value    
    T1CONbits.RD16 = 1;     // Enables register read/write of Timer1 in one 16-bit operation
    TMR1H = 0;
    TMR1L = 0;
    PIR1bits.TMR1IF = 0;        // Clear flag
    PIE1bits.TMR1IE = 1;        // Enable interrupts
    IPR1bits.TMR1IP = 1;        // High priority
    T1CONbits.TMR1ON = 1;   // Enables Timer1
    //T1CON = 0x33;
   
}

void Timer1Process(void)
{

    if(PIR1bits.TMR1IF)
    {
		// Increment internal high tick counter

		// Reset interrupt flag
        PIR1bits.TMR1IF = 0;
    }
    
}

void CCP9Init(void)
{
    
    //Temp.Val = AppConfig.Interval + AppConfig.IntervalCorrection;
    AppWork.IntervalCounter = AppConfig.Interval;
    AppWork.IntervalCounter_1kk = AppConfig.Interval_1kk;
    AppWork.State = 1; // pulse
    CCP9CON = 0x02; //  Compare mode: 
    CCPR9H = 0;
    CCPR9L = 0;
    Stepper_Init();
    IPR4bits.CCP9IP = 1;
    PIR4bits.CCP9IF = 0;
    PIE4bits.CCP9IE = 1;
    CCPTMRS2bits.C9TSEL0 = 0;
    
}

void CCP9Process(void)
{
    UINT16_VAL Temp;
    //WORD_VAL Temp; 
            
    if(PIR4bits.CCP9IF) {
        if(AppWork.State == 0) {
            Temp.Val = AppWork.IntervalCounter;
            AppWork.IntervalCounter += AppConfig.Interval;
            AppWork.IntervalCounter_1kk += AppConfig.Interval_1kk;
            if(AppWork.IntervalCounter_1kk >= INTERVAL_1KK_MAX){
                AppWork.IntervalCounter++;
                AppWork.IntervalCounter_1kk -= INTERVAL_1KK_MAX;
            }
            AppWork.State = 1;
        } else {
            Temp.byte.LB = CCPR9L;
            Temp.byte.HB = CCPR9H;
            Temp.Val += AppConfig.PulseWidth;
            AppWork.State = 0;
        }   
        CCPR9H = Temp.byte.HB;
        CCPR9L = Temp.byte.LB;        
        PIR4bits.CCP9IF = 0;
    }

}

void LoadCfg(void)
{
    FILEIO_OBJECT file;    
    const char * pathName = "SYSCONF.CFG";
    // Buffer for reading data
    APP_CONFIG Temp;
    FILEIO_FILE_SYSTEM_TYPE fileSystemType;
    FILEIO_DRIVE_PROPERTIES driveProperties;


    RTCCInit();
    
    if (FILEIO_Initialize() == false)
    {
        while(1);
    }
    FILEIO_RegisterTimestampGet (GetTimestamp);
    
    while (FILEIO_MediaDetect (&InternalFlashDrive, NULL) == false);    
    
    FILEIO_DriveMount ('A', &InternalFlashDrive, NULL);
    
    // Get the file system type
    fileSystemType = FILEIO_FileSystemTypeGet('A');
    // Tell the FILEIO_DrivePropertiesGet function that we are making a new request
    driveProperties.new_request = true;

    // Make sure we have at least two clusters free on our drive
    do
    {
        FILEIO_DrivePropertiesGet(&driveProperties, 'A');
    } while ((driveProperties.results.free_clusters < 2) && (driveProperties.properties_status == FILEIO_GET_PROPERTIES_STILL_WORKING));

    if(FILEIO_Open(&file, pathName, FILEIO_OPEN_READ) == FILEIO_RESULT_SUCCESS){
        if (FILEIO_Read (&Temp, 1, sizeof(APP_CONFIG), &file) != sizeof(APP_CONFIG))
        {
            while(1);
        }

        FILEIO_Close (&file);
    } else {
        if(FILEIO_Open(&file, pathName, FILEIO_OPEN_READ | FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE) == FILEIO_RESULT_SUCCESS){
            if (FILEIO_Write (&AppDefault, 1, sizeof(APP_CONFIG), &file) != sizeof(APP_CONFIG)){
                while(1);
            }
            FILEIO_Close (&file);
        }            
    }
    if(FILEIO_Open(&file, pathName, FILEIO_OPEN_READ) == FILEIO_RESULT_SUCCESS){
        if (FILEIO_Read (&AppConfig, 1, sizeof(APP_CONFIG), &file) != sizeof(APP_CONFIG))
        {
            while(1);
        }

        FILEIO_Close (&file);
    }
   
    FILEIO_DriveUnmount('A');
}

// Helper function to initialize the RTCC module.
// This function will use the compiler-generated timestamp to initialize the RTCC.
void RTCCInit (void)
{
    BSP_RTCC_DATETIME dateTime;
    uint8_t weekday;
    uint8_t month;
    uint8_t y;
    uint8_t dateTable[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    dateTime.bcdFormat = true;

    dateTime.second =  (((__TIME__[6]) & 0x0f) << 4) | ((__TIME__[7]) & 0x0f);
    dateTime.minute =  (((__TIME__[3]) & 0x0f) << 4) | ((__TIME__[4]) & 0x0f);
    dateTime.hour = (((__TIME__[0]) & 0x0f) << 4) | ((__TIME__[1]) & 0x0f);
    dateTime.day =  (((__DATE__[4]) & 0x0f) << 4) | ((__DATE__[5]) & 0x0f);
    dateTime.year = (((__DATE__[9]) & 0x0f) << 4) | ((__DATE__[10]) & 0x0f);

    //Set the month
    switch(__DATE__[0])
    {
        case 'J':
            //January, June, or July
            switch(__DATE__[1])
            {
                case 'a':
                    //January
                    month = 0x01;
                    break;
                case 'u':
                    switch(__DATE__[2])
                    {
                        case 'n':
                            //June
                            month = 0x06;
                            break;
                        case 'l':
                            //July
                            month = 0x07;
                            break;
                    }
                    break;
            }
            break;
        case 'F':
            month = 0x02;
            break;
        case 'M':
            //March,May
            switch(__DATE__[2])
            {
                case 'r':
                    //March
                    month = 0x03;
                    break;
                case 'y':
                    //May
                    month = 0x05;
                    break;
            }
            break;
        case 'A':
            //April, August
            switch(__DATE__[1])
            {
                case 'p':
                    //April
                    month = 0x04;
                    break;
                case 'u':
                    //August
                    month = 0x08;
                    break;
            }
            break;
        case 'S':
            month = 0x09;
            break;
        case 'O':
            month = 0x10;
            break;
        case 'N':
            month = 0x11;
            break;
        case 'D':
            month = 0x12;
            break;
    }

    dateTime.month = month;

    // Start with weekday = 6.  This value is valid for this algorithm for this century.
    weekday = 6;
    // y = year
    y = ((dateTime.year >> 4) * 10) + (dateTime.year & 0x0f);
    // Weekday = base day + year + x number of leap days
    weekday += y + (y / 4);
    // If the current year is a leap year but it's not March, subtract 1 from the date
    if (((y % 4) == 0) && (month < 3))
    {
        weekday -= 1;
    }
    // Add an offset based on the current month
    weekday += dateTable[month - 1];
    // Add the current day in the month
    weekday += ((dateTime.day >> 4) * 10) + (dateTime.day & 0x0f);
    weekday = weekday % 7;

    dateTime.weekday = weekday;

    // Initialize the RTCC with the calculated date/time.
    BSP_RTCC_Initialize (&dateTime);
}

void GetTimestamp (FILEIO_TIMESTAMP * timeStamp)
{
    BSP_RTCC_DATETIME dateTime;

    dateTime.bcdFormat = false;

    BSP_RTCC_TimeGet(&dateTime);

    timeStamp->timeMs = 0;
    timeStamp->time.bitfield.hours = dateTime.hour;
    timeStamp->time.bitfield.minutes = dateTime.minute;
    timeStamp->time.bitfield.secondsDiv2 = dateTime.second / 2;

    timeStamp->date.bitfield.day = dateTime.day;
    timeStamp->date.bitfield.month = dateTime.month;
    // Years in the RTCC module go from 2000 to 2099.  Years in the FAT file system go from 1980-2108.
    timeStamp->date.bitfield.year = dateTime.year + 20;;
}

#else
    void YourHighPriorityISRCode();
    void YourLowPriorityISRCode();

    //On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
    //the reset, high priority interrupt, and low priority interrupt
    //vectors.  However, the current Microchip USB bootloader
    //examples are intended to occupy addresses 0x00-0x7FF or
    //0x00-0xFFF depending on which bootloader is used.  Therefore,
    //the bootloader code remaps these vectors to new locations
    //as indicated below.  This remapping is only necessary if you
    //wish to program the hex file generated from this project with
    //the USB bootloader.  If no bootloader is used, edit the
    //usb_config.h file and comment out the following defines:
    //#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
    //#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif

        #pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}

	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	//been defined, but then the output hex file is not programmed with
	//the bootloader, addresses 0x08 and 0x18 would end up programmed with 0xFFFF.
	//As a result, if an actual interrupt was enabled and occured, the PC would jump
	//to 0x08 (or 0x18) and would begin executing "0xFFFF" (unprogrammed space).  This
	//executes as nop instructions, but the PC would eventually reach the REMAPPED_RESET_VECTOR_ADDRESS
	//(0x1000 or 0x800, depending upon bootloader), and would execute the "goto _startup".  This
	//would effective reset the application.

	//To fix this situation, we should always deliberately place a
	//"goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS" at address 0x08, and a
	//"goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS" at address 0x18.  When the output
	//hex file of this project is programmed with the bootloader, these sections do not
	//get bootloaded (as they overlap the bootloader space).  If the output hex file is not
	//programmed using the bootloader, then the below goto instructions do get programmed,
	//and the hex file still works like normal.  The below section is only required to fix this
	//scenario.
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	#pragma code


	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
        #if defined(USB_INTERRUPT)
	        USBDeviceTasks();
        #endif

	}	//This return will be a "retfie fast", since this is in a #pragma interrupt section
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.

	}	//This return will be a "retfie", since this is in a #pragma interruptlow section
#endif     
