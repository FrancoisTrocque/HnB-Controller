/*
		File:   DC24_GlobalVar.c
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

#include <stdio.h>
#include <stdlib.h>
#include "Type.h"

u8 Tempo500ms=0;

u8 u8Pedalage=0;
u8 u8PedalageCpt=0;
boolean bPedalageLevelPrev=FALSE;

u8 u8RPM=0;
u8 u8RPMCpt=0;
boolean bRPMLevelPrev=FALSE;

u16 u16TensionBatterie=0;
u16 u16CourantBatt=0;

