/*
		File:   Hdw_Adc.c
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

#include <xc.h>
#include "Type.h"
#include "PrjDefine.h"

void Hdw_AdcInit(void)
{
#ifdef PIC16F1509

    // initialized Motor courant analog input
    TRISC6=1;
    ANSC6=1;

    // initialized Batterie analog input
    TRISC7=1;
    ANSC7=1;

    ADCON1=0xA0;
    //ADFM=1;    B7right justify
    //ADCS0=0;   B6Fosc/32
    //ADCS1=1;   B5
    //ADCS2=0;   B4
    //ADPREF0=0; B1 // Ref = Vcc
    //ADPREF1=0; B0

    TRIGSEL0=0; // no auto trig
    TRIGSEL1=0;
    TRIGSEL2=0;

    // start ADC module
    ADON=1;


#endif
}

//*************************************************
// Start the Channel read
// Input Channel number 0 --> 11
void Hdw_AdcStartReadChannel(u8 Channel)
{
    // set channel and Keep ADON=1
    ADCON0=(Channel<<2)+1;

    // start conversion
    ADGO=1;
}

//*************************************************
// Check if Analog read finished
// Input none
// Output TRUE --> finished
boolean Hdw_AdcIsOkReadAna(void)
{
    // check if Analog channel read is finished
    if (ADGO==0)
    {
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }

}

//*************************************************
// Read the Analog value read
// Input none
// Output TRUE --> finished
u16 Hdw_AdcReadAnaValue(void)
{
    u16 temp;
    temp = (u16)(ADRESH & 0x3);
    temp <<= 8;
    temp += ADRESL;

    return (temp);
}