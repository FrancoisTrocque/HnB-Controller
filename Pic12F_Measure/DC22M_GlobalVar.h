/* 
		File:   DC24_GlobalVar.h
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

#ifndef DC24_GLOBALVAR_H
#define	DC24_GLOBALVAR_H

#ifdef	__cplusplus
extern "C" {
#endif

// Network variable
extern  u8 Tempo500ms;

extern  u8 u8Pedalage;
extern  u8 u8PedalageCpt;
extern  boolean bPedalageLevelPrev;

extern  u8 u8RPM;
extern  u8 u8RPMCpt;
extern  boolean bRPMLevelPrev;


extern  u16 u16TensionBatterie;
extern  u16 u16CourantBatt;

#ifdef	__cplusplus
}
#endif

#endif	/* DC24_GLOBALVAR_H */

