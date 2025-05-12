/*
===========================================================================

Copyright (c) 2010-2014 Darkstar Dev Teams
Copyright (c) 2023-2025 Fox_Mulder (adaptation Xbox 360)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

This file is part of DarkStar-server source code, adapted for Xbox 360.

===========================================================================
*/

#ifndef __XILOADER_DEFINES_H_INCLUDED__
#define __XILOADER_DEFINES_H_INCLUDED__

#include <stdint.h>
#include <string>

#include "polcore.h"
#include "ffxi.h"
#include "ffximain.h"

namespace xiloader
{
    /**
     * @brief PlayOnline language enumeration.
     */
    enum Language
    {
        Japanese = 0,
        English = 1,
        European = 2
    };

}; // namespace xiloader

#endif // __XILOADER_DEFINES_H_INCLUDED__
