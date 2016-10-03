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

#define _XTAL_FREQ 48000000

#define LED_D1_LAT LATAbits.LATA0
#define LED_D2_LAT LATAbits.LATA1

#define LED_D1_TRIS TRISAbits.TRISA0
#define LED_D2_TRIS TRISAbits.TRISA1

#define LED_ON  1
#define LED_OFF 0

#define PIN_INPUT  1
#define PIN_OUTPUT 0

#define SM_DRV_ENABLE_AN_TRIS   TRISAbits.TRISA2     
#define SM_DRV_RESET_RST_TRIS   TRISBbits.TRISB2
#define SM_DRV_SLEEP_CS_TRIS    TRISBbits.TRISB3
#define SM_DRV_DIRECTION_INT_TRIS TRISDbits.TRISD4
#define SM_DRV_STEP_PWM_TRIS    TRISCbits.TRISC6 

#define SM_DRV_ENABLE_AN        LATAbits.LATA2     
#define SM_DRV_RESET_RST        LATBbits.LATB2
#define SM_DRV_SLEEP_CS         LATBbits.LATB3
#define SM_DRV_DIRECTION_INT    LATDbits.LATD4
#define SM_DRV_STEP_PWM         LATCbits.LATC6 


void Stepper_Enable(void)
{
    SM_DRV_ENABLE_AN = 0;
}
void Stepper_Disable(void)
{
    SM_DRV_ENABLE_AN = 1;
}

void Stepper_Wake(void)
{
    SM_DRV_SLEEP_CS = 1;
}
void Stepper_Sleep(void)
{
    SM_DRV_SLEEP_CS = 0;
}

void Stepper_Set_Direction(bool dir)
{
    SM_DRV_DIRECTION_INT = dir;
}

void Stepper_Reset(void)
{
    SM_DRV_RESET_RST = 0;
    __delay_us(1);
    SM_DRV_RESET_RST = 1;
    __delay_ms(1);
}

void Stepper_Init(void){
    SM_DRV_ENABLE_AN_TRIS = PIN_OUTPUT;
    SM_DRV_RESET_RST_TRIS = PIN_OUTPUT;
    SM_DRV_SLEEP_CS_TRIS = PIN_OUTPUT;
    SM_DRV_DIRECTION_INT_TRIS = PIN_OUTPUT;
    SM_DRV_STEP_PWM_TRIS = PIN_OUTPUT;

    Stepper_Wake();
    Stepper_Enable();
    Stepper_Set_Direction(1);
    Stepper_Reset();
}