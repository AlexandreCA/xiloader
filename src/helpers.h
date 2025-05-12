/*
===========================================================================

Copyright (c) 2022 LandSandBoat Dev Teams
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

===========================================================================
*/

#ifndef __HELPERS_H_INCLUDED__
#define __HELPERS_H_INCLUDED__

#include <cstddef>

namespace xiloader
{
    /**
     * @brief Accesses data in a buffer at the given index with the specified type.
     *
     * @param buf   Pointer to the buffer.
     * @param index Index in the buffer to access.
     * @return Reference to the data cast to type T.
     */
    template <typename T, typename U>
    T& ref(U* buf, std::size_t index)
    {
        return *reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(buf) + index);
    }
}

#endif // __HELPERS_H_INCLUDED__
