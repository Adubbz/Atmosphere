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
#include "settings_amiibo_impl.hpp"

namespace ams::settings::impl {

    Result GetAmiiboKey(settings::factory::AmiiboKey *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboKey));
        return ::setcalGetAmiiboKey(reinterpret_cast<::SetCalAmiiboKey *>(out));
    }

    Result GetAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboEcqvCertificate));
        return ::setcalGetAmiiboEcqvCertificate(reinterpret_cast<::SetCalAmiiboEcqvCertificate *>(out));
    }

    Result GetAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboEcdsaCertificate));
        return ::setcalGetAmiiboEcdsaCertificate(reinterpret_cast<::SetCalAmiiboEcdsaCertificate *>(out));
    }

    Result GetAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboEcqvBlsKey));
        return ::setcalGetAmiiboEcqvBlsKey(reinterpret_cast<::SetCalAmiiboEcqvBlsKey *>(out));
    }

    Result GetAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboEcqvBlsCertificate));
        return ::setcalGetAmiiboEcqvBlsCertificate(reinterpret_cast<::SetCalAmiiboEcqvBlsCertificate *>(out));
    }

    Result GetAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAmiiboEcqvBlsRootCertificate));
        return ::setcalGetAmiiboEcqvBlsRootCertificate(reinterpret_cast<::SetCalAmiiboEcqvBlsRootCertificate *>(out));
    }

}
