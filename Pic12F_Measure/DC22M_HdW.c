/*
		File:   DC24_Hdw.c
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

/**************************************************************
 * Hardware description of HW3
 *
 * RA3 --> Capteur de pédalage
 * RA0 --> Vbatt Pont 82K 10K --> 0,1087 ou / 9,2
 * RA1 --> Hall A
 * RA2 --> IMOT Courant Négatif à partir de 2,5V
***************************************************************/

void DC24HdwInit(void)
{
#ifdef PIC12F1822
    ANSA1=0;
#endif

#ifdef PIC16F1823
    TRISC3=0; // RC3 Output
    TRISC1=0; // RC1 Output
#endif

#ifdef PIC16F1823_INTERNAL
    TRISC3=0; // RC3 Output
    TRISC1=0; // RC1 Output
#endif

}