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
#include "settings_amiibo_impl.hpp"

namespace ams::settings::impl {

    Result GetAmiiboKey(settings::factory::AmiiboKey *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboKey(out);
    }

    Result GetAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboEcqvCertificate(out);
    }

    Result GetAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboEcdsaCertificate(out);
    }

    Result GetAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboEcqvBlsKey(out);
    }

    Result GetAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboEcqvBlsCertificate(out);
    }

    Result GetAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAmiiboEcqvBlsRootCertificate(out);
    }

}
