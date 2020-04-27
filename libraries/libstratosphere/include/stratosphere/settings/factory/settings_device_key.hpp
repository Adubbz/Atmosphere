/*
 * Copyright (c) 2018-2020 Adubbz, Atmosphère-NX
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
#pragma once
#include <vapours.hpp>

namespace ams::settings::factory {

    /* TODO: This is unused and may need verification. */
    struct EccP256DeviceKey {
        u32 size;
        u8 data[0x30];
    };
    static_assert(sizeof(EccP256DeviceKey) == 0x34);
    static_assert(std::is_pod<EccP256DeviceKey>::value);

    struct EccB233DeviceKey {
        u32 size;
        u8 data[0x54];
    };
    static_assert(sizeof(EccB233DeviceKey) == 0x58);
    static_assert(std::is_pod<EccB233DeviceKey>::value);

    struct Rsa2048DeviceKey {
        u32 size;
        u8 data[0x244];
    };
    static_assert(sizeof(Rsa2048DeviceKey) == 0x248);
    static_assert(std::is_pod<Rsa2048DeviceKey>::value);

    Result GetEciDeviceKey(EccB233DeviceKey *out);
    Result GetEciDeviceKey(Rsa2048DeviceKey *out);
    Result GetEticketDeviceKey(Rsa2048DeviceKey *out);

}
