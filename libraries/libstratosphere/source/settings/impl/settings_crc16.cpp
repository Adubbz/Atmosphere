/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>
        
namespace ams::settings::impl {

    namespace {

        constexpr inline u16 Crc16InitialValue = 0x55AA;

        constexpr inline u16 Crc16Table[] = {
            0x0000, 0xCC01, 0xD801, 0x1400,
            0xF001, 0x3C00, 0x2800, 0xE401,
            0xA001, 0x6C00, 0x7800, 0xB401,
            0x5000, 0x9C01, 0x8801, 0x4400,
        };

    }

    u16 GetCrc16(const void *data, size_t size) {
        AMS_ASSERT(data != nullptr);
        AMS_ASSERT(size > 0);

        const u8 *src = static_cast<const u8 *>(data);

        u16 crc = Crc16InitialValue;

        u16 tmp = 0;
        while ((size--) > 0) {
            tmp = Crc16Table[crc & 0xF];
            crc = ((crc >> 4) & 0x0FFF) ^ tmp ^ Crc16Table[*src & 0xF];
            tmp = Crc16Table[crc & 0xF];
            crc = ((crc >> 4) & 0x0FFF) ^ tmp ^ Crc16Table[(*(src++) >> 4) & 0xF];
        }
        return crc;
    }

}
