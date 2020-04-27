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

    struct AccelerometerOffset {
        u8 value[0x6];
    };
    static_assert(sizeof(AccelerometerOffset) == 0x6);
    static_assert(std::is_pod<AccelerometerOffset>::value);

    struct AccelerometerScale {
        u8 value[0x6];
    };
    static_assert(sizeof(AccelerometerScale) == 0x6);
    static_assert(std::is_pod<AccelerometerScale>::value);

    struct GyroscopeOffset {
        u8 value[0x6];
    };
    static_assert(sizeof(GyroscopeOffset) == 0x6);
    static_assert(std::is_pod<GyroscopeOffset>::value);

    struct GyroscopeScale {
        u8 value[0x6];
    };
    static_assert(sizeof(GyroscopeScale) == 0x6);
    static_assert(std::is_pod<GyroscopeScale>::value);

    struct ConsoleSixAxisSensorHorizontalOffset {
        u8 value[0x6];
    };
    static_assert(sizeof(ConsoleSixAxisSensorHorizontalOffset) == 0x6);
    static_assert(std::is_pod<ConsoleSixAxisSensorHorizontalOffset>::value);

    Result GetAccelerometerOffset(AccelerometerOffset *out);
    Result GetAccelerometerScale(AccelerometerScale *out);
    Result GetGyroscopeOffset(GyroscopeOffset *out);
    Result GetGyroscopeScale(GyroscopeScale *out);
    Result GetConsoleSixAxisSensorModuleType(u8 *out);
    Result GetConsoleSixAxisSensorMountType(u8 *out);
    Result GetConsoleSixAxisSensorHorizontalOffset(ConsoleSixAxisSensorHorizontalOffset *out);

}
