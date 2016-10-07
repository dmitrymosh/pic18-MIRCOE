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

#include <Stepper.h>
#include <stdbool.h>
#include <xc.h>

#include "system.h"

//#define _XTAL_FREQ 48000000

#define LED_D1_LAT LATAbits.LATA0
#define LED_D2_LAT LATAbits.LATA1

#define LED_D1_TRIS TRISAbits.TRISA0
#define LED_D2_TRIS TRISAbits.TRISA1

#define LED_ON  1
#define LED_OFF 0

#define PIN_INPUT  1
#define PIN_OUTPUT 0

#define SM_DRV_ENABLE_AN_TRIS       TRISAbits.TRISA2     
#define SM_DRV_RESET_RST_TRIS       TRISBbits.TRISB2
#define SM_DRV_SLEEP_CS_TRIS        TRISBbits.TRISB3
#define SM_DRV_DIRECTION_INT_TRIS   TRISDbits.TRISD4
#define SM_DRV_STEP_PWM_TRIS        TRISCbits.TRISC6 

#define SM_DRV_ENABLE_AN_LAT        LATAbits.LATA2     
#define SM_DRV_RESET_RST_LAT        LATBbits.LATB2
#define SM_DRV_SLEEP_CS_LAT         LATBbits.LATB3
#define SM_DRV_DIRECTION_INT_LAT    LATDbits.LATD4
#define SM_DRV_STEP_PWM_LAT         LATCbits.LATC6 

#define SM_DRV_ENABLE_AN_PORT       PORTAbits.RA2     
#define SM_DRV_RESET_RST_PORT       PORTBbits.RB2
#define SM_DRV_SLEEP_CS_PORT        PORTBbits.RB3
#define SM_DRV_DIRECTION_INT_PORT   PORTDbits.RD4
#define SM_DRV_STEP_PWM_PORT        PORTCbits.RC6 


void Stepper_Enable(void)
{
    SM_DRV_ENABLE_AN_LAT = 0;
}
void Stepper_Disable(void)
{
    SM_DRV_ENABLE_AN_LAT = 1;
}

void Stepper_Wake(void)
{
    SM_DRV_SLEEP_CS_LAT = 1;
}
void Stepper_Sleep(void)
{
    SM_DRV_SLEEP_CS_LAT = 0;
}

void Stepper_Set_Direction(bool dir)
{
    SM_DRV_DIRECTION_INT_LAT = dir;
}

void Stepper_Reset(void)
{
    SM_DRV_RESET_RST_LAT = 0;
    __delay_us(1);
    SM_DRV_RESET_RST_LAT = 1;
    __delay_ms(1);
}

void Stepper_Init(STATUS_FLAGS * Flags){
    Stepper_Disable();
    
    SM_DRV_ENABLE_AN_TRIS = PIN_OUTPUT;
    SM_DRV_RESET_RST_TRIS = PIN_OUTPUT;
    SM_DRV_SLEEP_CS_TRIS = PIN_OUTPUT;
    SM_DRV_DIRECTION_INT_TRIS = PIN_OUTPUT;
    SM_DRV_STEP_PWM_TRIS = PIN_OUTPUT;
    
    SM_DRV_SLEEP_CS_LAT = Flags->bits.SLEEP;
    SM_DRV_ENABLE_AN_LAT = Flags->bits.ENABLE;
    Stepper_Set_Direction(Flags->bits.DIR);
    
    Stepper_Reset();
}

void GetStatusFlags(STATUS_FLAGS * Flags)
{
    Flags->bits.ENABLE = SM_DRV_ENABLE_AN_LAT;
    Flags->bits.RESET = SM_DRV_RESET_RST_LAT;
    Flags->bits.DIR = SM_DRV_DIRECTION_INT_LAT;
    Flags->bits.SLEEP = SM_DRV_SLEEP_CS_LAT;
}