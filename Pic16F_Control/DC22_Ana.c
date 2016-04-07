/*
		File:   DC22_Ana.c
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
#include "DC22_GlobalVar.h"
#include "Hdw_Adc.h"
#include "DC22_Motor.h"

#define ADC_CURRENT_CHANNEL 8
#define ADC_BATTERY_CHANNEL 9
#define SENSITIVITY 135 // (1024 / 5V * 0,066V) * 10  -> real result 13,51 * 10 135,1
#define FACTOR_BATT  460//((5V*(82K + 10K)/ 10k)*10
#define RESOLUTION 1023
#define BATT_COUNTER_MAX 10

enum DC22_AnaStatus {
    A_START_I,
    A_READ_I,
    A_START_BATT,
    A_READ_BATT
};

u16 u16NullCurrentOffset=0x1FF;
u8 u8BatteryLowCounter=0;
boolean boolBattLow = FALSE;

enum DC22_AnaStatus eDC22_AnaState=A_START_I;

void DC22_AnaProcess(void)
{
    u16 u16Itemp;
    u32 u32Vtemp;

    // launch Motor Current read
    if (eDC22_AnaState==A_START_I)
    {
        Hdw_AdcStartReadChannel(ADC_CURRENT_CHANNEL);
        eDC22_AnaState=A_READ_I;
    }

    // Check end & treat Motor Current
    else if (eDC22_AnaState==A_READ_I)
    {
        // check if read
        if (Hdw_AdcIsOkReadAna())
        {
            // when motor is stopped we read the Current Offset
            if (MotorState == M_STOP)
            {
                u16NullCurrentOffset=Hdw_AdcReadAnaValue();
                u8CourantBatt=0;
            }
            else
            {
                // here we read now the real current
                // the value decrease from the offset down to 0V for 20A
                u16Itemp=Hdw_AdcReadAnaValue();

                // if read value >= I Null Offset current = 0
                if (u16Itemp >= u16NullCurrentOffset)
                {
                    u16Itemp=0; //0 Amps
                }
                else
                {
                    // here we calculate the current
                    u16Itemp= u16NullCurrentOffset-u16Itemp;
                    // after this calculation u16Itemp < 512 
                    // --> so it cant be multiply by 100 --> 51200
                    // after the division by SENSITIVITY we get a value at 1/10A
                    u16Itemp= (u16Itemp*100)/SENSITIVITY;
                }
                u8CourantBatt=u16Itemp;
            }
            eDC22_AnaState=A_START_BATT;
        }
    }

    // Read V Batt
    else if (eDC22_AnaState==A_START_BATT)
    {
        Hdw_AdcStartReadChannel(ADC_BATTERY_CHANNEL);
        eDC22_AnaState=A_READ_BATT;
    }

    else if (eDC22_AnaState==A_READ_BATT)
    {
        // read batt
        u32Vtemp=(u32)Hdw_AdcReadAnaValue();
        // convert in 1/10V
        u32Vtemp*=FACTOR_BATT;
        u32Vtemp/=RESOLUTION;

        // terminate InfoBat calculation
        // boolBattLow is reset @ processor reset time
        // is only set by software is Battery level too low
        if (boolBattLow)
        {
            u16TensionBatterie=(u16)u32Vtemp + 0x8000; // B15 à 1
        }
        else
        {
            u16TensionBatterie=(u16)u32Vtemp; // B15 à 0
        }

        // check if Level Min exists and check Vbat if yes
        if ( (u16SeuilBatterie !=0) && (!boolBattLow) )
        {
            // only if threshold not NULL
            if (u16TensionBatterie < u16SeuilBatterie)
            {
                // battery Low
                u8BatteryLowCounter++;
                if (u8BatteryLowCounter >= BATT_COUNTER_MAX)
                {
                    boolBattLow=TRUE;
                }
            }
            else if (u8BatteryLowCounter != 0)
            {
                // battery OK
                u8BatteryLowCounter--;
            }
        }

        eDC22_AnaState=A_START_I;
    }

}