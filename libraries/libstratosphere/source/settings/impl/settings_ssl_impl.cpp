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
#include <stratosphere.hpp>
#include "settings_ssl_impl.hpp"

namespace ams::settings::impl {

    Result GetSslKey(settings::factory::SslKey *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetSslKey(out);
    }

    Result GetSslCertificate(settings::factory::SslCertificate *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetSslCertificate(out);
    }

}
