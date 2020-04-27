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
#pragma once
#include <vapours.hpp>

namespace ams::settings::factory {

    struct GameCardKey {
        u32 size;
        u8 data[0x134];
    };
    static_assert(sizeof(GameCardKey) == 0x138);
    static_assert(std::is_pod<GameCardKey>::value);

    struct GameCardCertificate {
        u8 cert[0x400];
    };
    static_assert(sizeof(GameCardCertificate) == 0x400);
    static_assert(std::is_pod<GameCardCertificate>::value);

    Result GetGameCardKey(GameCardKey *out);
    Result GetGameCardCertificate(GameCardCertificate *out);

}
