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

namespace ams::util {

    struct Uint8x4 {
        u8 value[4];
    };
    static_assert(sizeof(Uint8x4) == 0x4);

    struct Unorm8x4 {
        u8 value[4];
    };
    static_assert(sizeof(Unorm8x4) == 0x4);

    struct Float2 {
        union {
            float value[2];
            struct {
                float x;
                float y;
            };
        };
    };
    static_assert(sizeof(Float2) == 0x8);

    struct Float3 {
        union {
            float value[3];
            struct {
                float x;
                float y;
                float z;
            };
        };
    };
    static_assert(sizeof(Float3) == 0xC);

    struct Float4 {
        union {
            float value[4];
            struct {
                float x;
                float y;
                float z;
                float w;
            };
        };
    };
    static_assert(sizeof(Float4) == 0x10);

}
