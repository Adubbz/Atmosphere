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
#include "settings_analog_stick_impl.hpp"

namespace ams::settings::impl {

    Result GetAnalogStickModuleTypeL(u8 *out) {
        return ::setcalGetAnalogStickModuleTypeL(out);
    }

    Result GetAnalogStickModelParameterL(settings::factory::AnalogStickModelParameter *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAnalogStickModelParameter));
        return ::setcalGetAnalogStickModelParameterL(reinterpret_cast<::SetCalAnalogStickModelParameter *>(out));
    }

    Result GetAnalogStickFactoryCalibrationL(settings::factory::AnalogStickFactoryCalibration *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAnalogStickFactoryCalibration));
        return ::setcalGetAnalogStickFactoryCalibrationL(reinterpret_cast<::SetCalAnalogStickFactoryCalibration *>(out));
    }

    Result GetAnalogStickModuleTypeR(u8 *out) {
        return ::setcalGetAnalogStickModuleTypeR(out);
    }

    Result GetAnalogStickModelParameterR(settings::factory::AnalogStickModelParameter *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAnalogStickModelParameter));
        return ::setcalGetAnalogStickModelParameterR(reinterpret_cast<::SetCalAnalogStickModelParameter *>(out));
    }

    Result GetAnalogStickFactoryCalibrationR(settings::factory::AnalogStickFactoryCalibration *out) {
        static_assert(sizeof(*out) == sizeof(::SetCalAnalogStickFactoryCalibration));
        return ::setcalGetAnalogStickFactoryCalibrationR(reinterpret_cast<::SetCalAnalogStickFactoryCalibration *>(out));
    }

}
