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

    struct SslKey {
        u32 size;
        u8 data[0x134];
    };
    static_assert(sizeof(SslKey) == 0x138);
    static_assert(std::is_pod<SslKey>::value);

    struct SslCertificate {
        u32 size;
        u8 cert[0x800];
    };
    static_assert(sizeof(SslCertificate) == 0x804);
    static_assert(std::is_pod<SslCertificate>::value);

    Result GetSslKey(SslKey *out);
    Result GetSslCertificate(SslCertificate *out);

}
