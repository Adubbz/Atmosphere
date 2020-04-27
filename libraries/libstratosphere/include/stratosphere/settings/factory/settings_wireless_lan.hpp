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

    struct MacAddress {
        u8 value[0x6];
    };
    static_assert(sizeof(MacAddress) == 0x6);
    static_assert(std::is_pod<MacAddress>::value);

    struct CountryCode {
        char str[0x3];
    };
    static_assert(sizeof(CountryCode) == 0x3);
    static_assert(std::is_pod<CountryCode>::value);

    Result GetWirelessLanMacAddress(MacAddress *out);
    Result GetWirelessLanCountryCodeCount(s32 *out);
    Result GetWirelessLanCountryCodes(s32 *out_count, CountryCode *out_codes, s32 num_codes);

}
