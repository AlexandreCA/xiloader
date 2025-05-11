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

#include "network.h"
#include <xtl.h>
#include <string>
#include <stdarg.h>

namespace xiloader::console
{
    /**
     * @brief Outputs a formatted message to a log file on Xbox 360.
     *
     * @param c         The color to associate with the message (currently ignored).
     * @param format    The format string for the message.
     * @param ...       Variable arguments for the format string.
     */
    void output(color c, const char* format, ...)
    {
        // Buffer pour le message formaté
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);

        // Ouvrir ou créer le fichier de log
        HANDLE file = CreateFile(
            "game:\\xiloader.log",
            GENERIC_WRITE,
            FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (file != INVALID_HANDLE_VALUE)
        {
            // Se positionner à la fin du fichier
            SetFilePointer(file, 0, NULL, FILE_END);

            // Ajouter un saut de ligne
            std::string message = std::string(buffer) + "\n";

            // Écrire dans le fichier
            DWORD bytesWritten;
            WriteFile(file, message.c_str(), message.length(), &bytesWritten, NULL);

            // Fermer le fichier
            CloseHandle(file);
        }
    }

}; // namespace xiloader::console
