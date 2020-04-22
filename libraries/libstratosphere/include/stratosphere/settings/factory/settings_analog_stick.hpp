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

    struct AnalogStickModelParameter {
        u8 value[0x12];
    };
    static_assert(sizeof(AnalogStickModelParameter) == 0x12);
    static_assert(std::is_pod<AnalogStickModelParameter>::value);

    struct AnalogStickFactoryCalibration {
        u8 value[0x9];
    };
    static_assert(sizeof(AnalogStickFactoryCalibration) == 0x9);
    static_assert(std::is_pod<AnalogStickFactoryCalibration>::value);

    Result GetAnalogStickModuleTypeL(u8 *out);
    Result GetAnalogStickModelParameterL(AnalogStickModelParameter *out);
    Result GetAnalogStickFactoryCalibrationL(AnalogStickFactoryCalibration *out);
    Result GetAnalogStickModuleTypeR(u8 *out);
    Result GetAnalogStickModelParameterR(AnalogStickModelParameter *out);
    Result GetAnalogStickFactoryCalibrationR(AnalogStickFactoryCalibration *out);

}
