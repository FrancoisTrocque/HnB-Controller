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
#include "DC22M_GlobalVar.h"
#include "Hdw_Adc.h"

#define ADC_BATTERY_CHANNEL 0
#define ADC_CURRENT_CHANNEL 2

enum DC22_AnaStatus {
    A_START_I,
    A_READ_I,
    A_START_BATT,
    A_READ_BATT
};


enum DC22_AnaStatus eDC22_AnaState=A_START_I;

void DC22_AnaProcess(void)
{

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
            // here we read now the real current
            // the value decrease from the offset down to 0V for 20A
            u16CourantBatt=Hdw_AdcReadAnaValue();

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
         // check if read
        if (Hdw_AdcIsOkReadAna())
        {
           u16TensionBatterie=Hdw_AdcReadAnaValue();

           eDC22_AnaState=A_START_I;
        }
    }

}