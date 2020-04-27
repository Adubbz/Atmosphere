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
#include "settings_motion_sensor_impl.hpp"

namespace ams::settings::impl {

    Result GetAccelerometerOffset(settings::factory::AccelerometerOffset *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAccelerometerOffset(out);
    }

    Result GetAccelerometerScale(settings::factory::AccelerometerScale *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetAccelerometerScale(out);
    }

    Result GetGyroscopeOffset(settings::factory::GyroscopeOffset *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetGyroscopeOffset(out);
    }

    Result GetGyroscopeScale(settings::factory::GyroscopeScale *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetGyroscopeScale(out);
    }

    Result GetConsoleSixAxisSensorModuleType(u8 *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetConsoleSixAxisSensorModuleType(out);
    }

    Result GetConsoleSixAxisSensorMountType(u8 *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetConsoleSixAxisSensorMountType(out);
    }

    Result GetConsoleSixAxisSensorHorizontalOffset(settings::factory::ConsoleSixAxisSensorHorizontalOffset *out) {
        std::shared_ptr<IFactorySettingsServer> intf;
        R_TRY(CreateFactorySettingsServerProxy(std::addressof(intf)));
        return intf->GetConsoleSixAxisSensorHorizontalOffset(out);
    }

}
