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

#ifndef __FFXIMAIN_H_INCLUDED__
#define __FFXIMAIN_H_INCLUDED__

#include <xtl.h>

namespace xiloader
{
    /**
     * @brief Interface for Final Fantasy XI main game functionality, adapted for Xbox 360.
     */
    class IGameMain
    {
    public:
        virtual ~IGameMain() {}

        /**
         * @brief Initializes the main FFXI game engine.
         *
         * @param pPol      Pointer to PlayOnline core interface (e.g., IPOLCoreCom).
         * @param pFFXi     Pointer to FFXI-specific data or interface.
         * @return HRESULT  S_OK on success, error code otherwise.
         */
        virtual HRESULT FFXiGameMain(void* pPol, void* pFFXi) = 0;

        /**
         * @brief Retrieves FFXI parameter data.
         *
         * @param pFFXiPara Pointer to store the FFXI parameter data.
         * @return HRESULT  S_OK on success, error code otherwise.
         */
        virtual HRESULT FFXiParaGet(void** pFFXiPara) = 0;

        /**
         * @brief Initializes PlayOnline logout process.
         *
         * @return HRESULT  S_OK on success, error code otherwise.
         */
        virtual HRESULT PolLogoutInit() = 0;

        /**
         * @brief Finalizes PlayOnline logout process.
         *
         * @return HRESULT  S_OK on success, error code otherwise.
         */
        virtual HRESULT PolLogoutEnd() = 0;
    };

}; // namespace xiloader

#endif // __FFXIMAIN_H_INCLUDED__
