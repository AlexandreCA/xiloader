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

#ifndef __FFXI_H_INCLUDED__
#define __FFXI_H_INCLUDED__

#include <xtl.h>

namespace xiloader
{
    /**
     * @brief Structure for file data used by the file manager.
     */
    struct FX_FILE_DATA
    {
        unsigned short FileNo;   // File number
        unsigned char* pBufAddr; // Buffer address
    };

    /**
     * @brief Interface for FFXI file management, adapted for Xbox 360.
     */
    class IFxFileManager
    {
    public:
        virtual ~IFxFileManager() {}

        /**
         * @brief Initializes the file system with a name file.
         *
         * @param pNameFile     Pointer to the name file data.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxFileSystemInit(unsigned char* pNameFile) = 0;

        /**
         * @brief Terminates the file system.
         *
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxFileSystemExit() = 0;

        /**
         * @brief Reads a file into a buffer.
         *
         * @param FileNo        File number to read.
         * @param pBufAddr      Buffer to store the file data.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxRead(unsigned short FileNo, unsigned char* pBufAddr) = 0;

        /**
         * @brief Reads a file into a buffer (alternative method).
         *
         * @param FileNo        File number to read.
         * @param pBufAddr      Buffer to store the file data.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxReadA(unsigned short FileNo, unsigned char* pBufAddr) = 0;

        /**
         * @brief Reads multiple files into buffers.
         *
         * @param FileData      Array of file data structures.
         * @param FileDataNum   Number of files to read.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxReadM(FX_FILE_DATA* FileData, unsigned int FileDataNum) = 0;

        /**
         * @brief Reads a file with extended options.
         *
         * @param FileNo        File number to read.
         * @param StartOffset   Starting offset in the file.
         * @param CtrlFunc      Control function pointer (implementation-specific).
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxReadEx(unsigned short FileNo, unsigned long StartOffset, void* CtrlFunc) = 0;

        /**
         * @brief Writes data to a file.
         *
         * @param FileNo        File number to write.
         * @param WriteLength   Length of data to write.
         * @param pBufAddr      Buffer containing the data.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxWrite(unsigned short FileNo, unsigned long WriteLength, unsigned char* pBufAddr) = 0;

        /**
         * @brief Seeks to a position in a file.
         *
         * @param FileNo        File number to seek.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxSeek(unsigned short FileNo) = 0;

        /**
         * @brief Gets the size of a file.
         *
         * @param FileNo        File number to query.
         * @param FileLength    Pointer to store the file size.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxGetFileSize(unsigned short FileNo, unsigned long* FileLength) = 0;

        /**
         * @brief Tests the size of a file.
         *
         * @param FileNo        File number to query.
         * @param FileLength    Pointer to store the file size.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxTestFileSize(unsigned short FileNo, unsigned long* FileLength) = 0;

        /**
         * @brief Checks if a file operation is finished.
         *
         * @param FileNo        File number to check.
         * @param bFinishedFlg  Pointer to store the finished flag.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxFinishedCheck(unsigned short FileNo, unsigned char* bFinishedFlg) = 0;

        /**
         * @brief Checks if a buffer operation is finished.
         *
         * @param pBufAddr      Buffer address to check.
         * @param bFinishedFlg  Pointer to store the finished flag.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxFinishedCheckB(unsigned char* pBufAddr, unsigned char* bFinishedFlg) = 0;

        /**
         * @brief Waits for file operations to complete.
         *
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxWait() = 0;

        /**
         * @brief Performs periodic checks on the file system.
         *
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxPeriodicCheck() = 0;

        /**
         * @brief Gets the file system status.
         *
         * @param Status        Pointer to store the status.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT FxGetFileSysteStatus(long* Status) = 0;
    };

    /**
     * @brief Interface for FFXI game entry point, adapted for Xbox 360.
     */
    class IFFXiEntry
    {
    public:
        virtual ~IFFXiEntry() {}

        /**
         * @brief Starts the FFXI game.
         *
         * @param pPol          Pointer to PlayOnline core interface (e.g., IPOLCoreCom).
         * @param pFFXiMessage  Pointer to store FFXI message data.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT GameStart(void* pPol, void** pFFXiMessage) = 0;

        /**
         * @brief Gets the file manager interface.
         *
         * @param pVal          Pointer to store the file manager interface.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT get_FxFileManager(IFxFileManager** pVal) = 0;

        /**
         * @brief Gets the FFXI version.
         *
         * @param pVal          Pointer to store the version number.
         * @return HRESULT      S_OK on success, error code otherwise.
         */
        virtual HRESULT getVersion(unsigned long* pVal) = 0;
    };

}; // namespace xiloader

#endif // __FFXI_H_INCLUDED__
