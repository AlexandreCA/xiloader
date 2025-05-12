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

#ifndef __XILOADER_CONSOLE_H_INCLUDED__
#define __XILOADER_CONSOLE_H_INCLUDED__

namespace xiloader::console
{
    /**
     * @brief Console color enumeration for Xbox 360 logging.
     */
    enum class color
    {
        info,    // Informational messages
        warning, // Warning messages
        error    // Error messages
    };

    /**
     * @brief Outputs a formatted message to a log file.
     *
     * @param c         The color to associate with the message (currently ignored).
     * @param format    The format string for the message.
     * @param ...       Variable arguments for the format string.
     */
    void output(color c, const char* format, ...);

}; // namespace xiloader::console

#endif // __XILOADER_CONSOLE_H_INCLUDED__
