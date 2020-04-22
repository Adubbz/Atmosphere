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

    struct AmiiboKey {
        u32 size;
        u8 key[0x50];
        u32 generation;
    };
    static_assert(sizeof(AmiiboKey) == 0x58);
    static_assert(std::is_pod<AmiiboKey>::value);

    struct AmiiboEcqvCertificate {
        u32 size;
        u8 cert[0x14];
    };
    static_assert(sizeof(AmiiboEcqvCertificate) == 0x18);
    static_assert(std::is_pod<AmiiboEcqvCertificate>::value);

    struct AmiiboEcdsaCertificate {
        u32 size;
        u8 cert[0x70];
    };
    static_assert(sizeof(AmiiboEcdsaCertificate) == 0x74);
    static_assert(std::is_pod<AmiiboEcdsaCertificate>::value);

    struct AmiiboEcqvBlsKey {
        u32 size;
        u8 key[0x40];
        u32 generation;
    };
    static_assert(sizeof(AmiiboEcqvBlsKey) == 0x48);
    static_assert(std::is_pod<AmiiboEcqvBlsKey>::value);

    struct AmiiboEcqvBlsCertificate {
        u32 size;
        u8 cert[0x20];
    };
    static_assert(sizeof(AmiiboEcqvBlsCertificate) == 0x24);
    static_assert(std::is_pod<AmiiboEcqvBlsCertificate>::value);

    struct AmiiboEcqvBlsRootCertificate {
        u32 size;
        u8 cert[0x90];
    };
    static_assert(sizeof(AmiiboEcqvBlsRootCertificate) == 0x94);
    static_assert(std::is_pod<AmiiboEcqvBlsRootCertificate>::value);

    Result GetAmiiboKey(AmiiboKey *out);
    Result GetAmiiboEcqvCertificate(AmiiboEcqvCertificate *out);
    Result GetAmiiboEcdsaCertificate(AmiiboEcdsaCertificate *out);
    Result GetAmiiboEcqvBlsKey(AmiiboEcqvBlsKey *out);
    Result GetAmiiboEcqvBlsCertificate(AmiiboEcqvBlsCertificate *out);
    Result GetAmiiboEcqvBlsRootCertificate(AmiiboEcqvBlsRootCertificate *out);

}
