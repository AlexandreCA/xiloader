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

#ifndef __XILOADER_FUNCTIONS_H_INCLUDED__
#define __XILOADER_FUNCTIONS_H_INCLUDED__

#include <xtl.h>
#include <string>

namespace xiloader
{
    /**
     * @brief Functions class containing helper functions for various tasks.
     */
    class functions
    {
        /**
         * @brief Compares a pattern against a given memory pointer.
         *
         * @param lpDataPtr     The live data to compare with.
         * @param lpPattern     The pattern of bytes to compare with.
         * @param pszMask       The mask to compare against.
         *
         * @return True if pattern was found, false otherwise.
         */
        static bool MaskCompare(const unsigned char* lpDataPtr, const unsigned char* lpPattern, const char* pszMask);

    public:

        /**
         * @brief Locates a signature of bytes using the given mask within a memory range.
         *
         * @param startAddress  The starting address to begin the search.
         * @param size          The size of the memory range to search.
         * @param lpPattern     The pattern of bytes to compare with.
         * @param pszMask       The mask to compare against.
         *
         * @return Start address of where the pattern was found, 0 otherwise.
         */
        static unsigned long FindPattern(unsigned long startAddress, unsigned long size, const unsigned char* lpPattern, const char* pszMask);

        /**
         * @brief Obtains the PlayOnline registry key equivalent for Xbox 360.
         *
         * @param lang          The language id the loader was started with.
         *
         * @return Fixed configuration path or key name.
         */
        static std::string GetRegistryPlayOnlineKey(int lang);

        /**
         * @brief Obtains the PlayOnline language id for Xbox 360.
         *
         * @param lang          The language id the loader was started with.
         *
         * @return The language id, defaults to 1 (English) if not specified.
         */
        static int GetRegistryPlayOnlineLanguage(int lang);

        /**
         * @brief Obtains the PlayOnline installation folder equivalent for Xbox 360.
         *
         * @param lang          The language id the loader was started with.
         *
         * @return Fixed installation folder path (e.g., "game:\\PlayOnline").
         */
        static std::string GetRegistryPlayOnlineInstallFolder(int lang);
    };

}; // namespace xiloader

#endif // __XILOADER_FUNCTIONS_H_INCLUDED__
