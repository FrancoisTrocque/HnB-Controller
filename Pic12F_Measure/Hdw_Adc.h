/* 
		File:   Hdw_Adc.h
    Copyright (C) 2015-2016  Fran�ois Trocque
    
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

#ifndef HDW_ADC_H
#define	HDW_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif


void Hdw_AdcInit(void);
void Hdw_AdcStartReadChannel(u8 Channel);
boolean Hdw_AdcIsOkReadAna(void);
u16 Hdw_AdcReadAnaValue(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HDW_ADC_H */

