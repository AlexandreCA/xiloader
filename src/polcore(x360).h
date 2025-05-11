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

#ifndef __POLCORE_H_INCLUDED__
#define __POLCORE_H_INCLUDED__

#include <xtl.h>
#include <string>

namespace xiloader
{
    /**
     * @brief Interface for PlayOnline core functionality, adapted for Xbox 360.
     */
    class IPOLCoreCom
    {
    public:
        virtual ~IPOLCoreCom() {}

        /**
         * @brief Gets the instance handle (not used on Xbox 360, placeholder).
         *
         * @param hInstance     Pointer to store the instance handle.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GethInstance(void** hInstance) = 0;

        /**
         * @brief Gets the command line arguments (ANSI).
         *
         * @param lpCmdLine     Pointer to store the command line string.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GetlpCmdLine(std::string* lpCmdLine) = 0;

        /**
         * @brief Sets the initial parameters (instance and command line).
         *
         * @param hInstance     Instance handle (placeholder).
         * @param lpCmdLine     Command line arguments.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT SetParamInit(void* hInstance, const std::string& lpCmdLine) = 0;

        /**
         * @brief Executes the PlayOnline viewer (used to launch FFXI).
         *
         * @param inFunc        Function identifier or parameter.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT PolViewerExec(unsigned long* inFunc) = 0;

        /**
         * @brief Creates input handling for the game (uses XInput on Xbox 360).
         *
         * @param inWnd         Window handle (placeholder, not used on Xbox 360).
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT CreateInput(void* inWnd) = 0;

        /**
         * @brief Updates the input state (XInput).
         *
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT UpdateInputState() = 0;

        /**
         * @brief Gets the repeat state of a controller button.
         *
         * @param inPadNum      Controller number (0-3).
         * @param outState      Pointer to store the repeat state.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GetPadRepeat(unsigned long inPadNum, unsigned long* outState) = 0;

        /**
         * @brief Gets the pressed state of a controller button.
         *
         * @param inPadNum      Controller number (0-3).
         * @param outState      Pointer to store the pressed state.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GetPadOn(unsigned long inPadNum, unsigned long* outState) = 0;

        /**
         * @brief Performs final cleanup (closes resources).
         *
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FinalCleanup() = 0;

        /**
         * @brief Sets the initial parameters (Unicode, placeholder).
         *
         * @param hInstance     Instance handle (placeholder).
         * @param lpCmdLine     Command line arguments (Unicode).
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT SetParamInitW(void* hInstance, const std::wstring& lpCmdLine) = 0;

        /**
         * @brief Gets the command line arguments (Unicode).
         *
         * @param lpCmdLine     Pointer to store the command line string.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GetlpCmdLineW(std::wstring* lpCmdLine) = 0;

        /**
         * @brief Sets the area code for the game region.
         *
         * @param inAreaCode    Area code (e.g., Japan, NA, EU).
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT SetAreaCode(long inAreaCode) = 0;

        /**
         * @brief Gets the area code for the game region.
         *
         * @param outAreaCode   Pointer to store the area code.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GetAreaCode(long* outAreaCode) = 0;
    };

}; // namespace xiloader

#endif // __POLCORE_H_INCLUDED__
