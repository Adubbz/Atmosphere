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
#include "settings_wireless_lan_impl.hpp"

namespace ams::settings::impl {

    Result GetWirelessLanMacAddress(settings::factory::MacAddress *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetWirelessLanMacAddress(out);
    }

    Result GetWirelessLanCountryCodeCount(s32 *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetWirelessLanCountryCodeCount(out);
    }

    Result GetWirelessLanCountryCodes(s32 *out_count, settings::factory::CountryCode *out_codes, s32 num_codes) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetWirelessLanCountryCodes(out_count, sf::OutArray<settings::factory::CountryCode>(out_codes, num_codes));
    }

}
