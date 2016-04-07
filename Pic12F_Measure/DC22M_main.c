/* 
		File:   DC24_main.c
    Copyright (C) 2015-2016  François Trocque
    
    This file is part of HnB_Controller project.

    HnB_Controller is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HnB_Controller is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HnB_Controller.  If not, see <http://www.gnu.org/licenses/>. 2
*/

// 'C' source line config statements

#include <xc.h>
#include "Type.h"
#include "Bio-NetApp.h"
#include "PrjDefine.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#ifdef PIC12F1822

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function is an input
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#endif

#ifdef PIC16F1823

// CONFIG1
#pragma config FOSC = HS    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#endif

#ifdef PIC16F1823_INTERNAL

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#endif

#include <stdio.h>
#include <stdlib.h>
#include "Type.h"
#include "DC22M_GlobalVar.h"
#include "Hdw_Uart.h"
#include "Bio-Net.h"
#include "DC22M_Hdw.h"
#include "Bio-NetApp.h"
#include "DC22M_Ana.h"
#include "Hdw_Adc.h"
#include "DC22M_Pedalage.h"

/*
 * 
 */
// PA1 HALL_A PA4 Pédalage
#define PEDALE_PORT ((PORTA & 0x08) == 0x08)
#define HALLA_PORT  ((PORTA & 0x02) == 0x02)

#define TEMPO500MS 50


int main(int argc, char** argv) {

    u8 ValPort;

    DC24HdwInit();
    Hdw_AdcInit();
    HdwUartInit();
    BioNetInit();

    while (1)
    {
        BioNetProcess();

        // Application
        // TODO --> what is needed by the application process
        //          Fill Read variable
        //          Use written variables

        // for test we only content of Sens in Pedalage
        // just for network test behaviour

        DC22_AnaProcess();

        //********* Pedalage *****************
        // Lit port une seule fois
        if (PEDALE_PORT)
        {
            ValPort=TRUE;
        }
        else
        {
            ValPort=FALSE;
        }

        // detecte tous les fronts
        if ( ValPort != bPedalageLevelPrev)
        {
            // front montant sur pédale
            u8PedalageCpt++;
        }

        bPedalageLevelPrev=ValPort;


         //********* RPM *****************
       // Lit port une seule fois
        if (HALLA_PORT)
        {
            ValPort=TRUE;
        }
        else
        {
            ValPort=FALSE;
        }

        // detecte tous les fronts montants
        if ( (ValPort == TRUE) && (bRPMLevelPrev==FALSE))
        {
            // front montant sur HALL
            u8RPMCpt++;
        }

        bRPMLevelPrev=ValPort;

        // end Application
    };
}

//*******************************************
// Interrupt 1ms for time management
//
void DC24It10ms(void)
{
    // called each 10ms
    // reset prescaler
    u8Prescaler10ms = 0;

    // manage capture toutes les 500ms
    Tempo500ms++;
    if (Tempo500ms >= TEMPO500MS)
    {
        // copie les valeur de compteurs
        u8Pedalage=u8PedalageCpt;
        u8RPM=u8RPMCpt;

        // raz timer
        Tempo500ms=0;

        // raz Compteurs
        u8PedalageCpt=0;
        u8RPMCpt=0;
    }

}

