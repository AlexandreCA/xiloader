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

#include "functions.h"
#include "network.h" // Pour console::output

namespace xiloader
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
    bool functions::MaskCompare(const unsigned char* lpDataPtr, const unsigned char* lpPattern, const char* pszMask)
    {
        for (; *pszMask; ++pszMask, ++lpDataPtr, ++lpPattern)
        {
            if (*pszMask == 'x' && *lpDataPtr != *lpPattern)
                return false;
        }
        return (*pszMask) == '\0';
    }

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
    unsigned long functions::FindPattern(unsigned long startAddress, unsigned long size, const unsigned char* lpPattern, const char* pszMask)
    {
        // TODO: Implémenter la recherche dans la plage mémoire [startAddress, startAddress + size]
        // Exemple : Scanner la mémoire du .xex
        console::output(console::color::warning, "FindPattern: Not implemented for Xbox 360. Specify memory range [0x%08X, 0x%08X].", startAddress, startAddress + size);
        return 0; // Retourne 0 si non trouvé
    }

    /**
     * @brief Obtains the PlayOnline registry key equivalent for Xbox 360.
     *
     * @param lang          The language id the loader was started with.
     *
     * @return Fixed configuration path or key name.
     */
    std::string functions::GetRegistryPlayOnlineKey(int lang)
    {
        static const char* RegistryKeys[3] =
        {
            "PlayOnline",    // lang = 0 (Japanese)
            "PlayOnlineUS",  // lang = 1 (English)
            "PlayOnlineEU"   // lang = 2 (European)
        };

        if (lang < 0)
            lang = 0;
        if (lang > 2)
            lang = 2;

        return std::string(RegistryKeys[lang]);
    }

    /**
     * @brief Obtains the PlayOnline language id for Xbox 360.
     *
     * @param lang          The language id the loader was started with.
     *
     * @return The language id, defaults to 1 (English) if not specified.
     */
    int functions::GetRegistryPlayOnlineLanguage(int lang)
    {
        // Pas de registre sur Xbox 360, retourner la langue basée sur l'input ou défaut
        if (lang < 0 || lang > 2)
            lang = 1; // Anglais par défaut
        return lang;
    }

    /**
     * @brief Obtains the PlayOnline installation folder equivalent for Xbox 360.
     *
     * @param lang          The language id the loader was started with.
     *
     * @return Fixed installation folder path (e.g., "game:\\PlayOnline").
     */
    std::string functions::GetRegistryPlayOnlineInstallFolder(int lang)
    {
        // Pas de registre, retourner un chemin fixe
        return "game:\\PlayOnline";
    }

}; // namespace xiloader
