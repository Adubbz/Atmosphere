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

#pragma once
#include <vapours/results/results_common.hpp>

namespace ams::settings {

    R_DEFINE_NAMESPACE_RESULT_MODULE(105);

    R_DEFINE_ERROR_RESULT(SettingsItemNotFound,                 11);

    R_DEFINE_ERROR_RANGE(InternalError, 100, 149);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyAllocationFailed,   101);
        R_DEFINE_ERROR_RESULT(SettingsItemValueAllocationFailed, 102);

    R_DEFINE_ERROR_RANGE(InvalidArgument, 200, 399);
        R_DEFINE_ERROR_RESULT(SettingsNameNull,                 201);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyNull,              202);
        R_DEFINE_ERROR_RESULT(SettingsItemValueNull,            203);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyBufferNull,        204);
        R_DEFINE_ERROR_RESULT(SettingsItemValueBufferNull,      205);

        R_DEFINE_ERROR_RESULT(SettingsNameEmpty,                221);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyEmpty,             222);

        R_DEFINE_ERROR_RESULT(SettingsNameTooLong,              241);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyTooLong,           242);

        R_DEFINE_ERROR_RESULT(SettingsNameInvalidFormat,        261);
        R_DEFINE_ERROR_RESULT(SettingsItemKeyInvalidFormat,     262);
        R_DEFINE_ERROR_RESULT(SettingsItemValueInvalidFormat,   263);

    R_DEFINE_ERROR_RANGE(RegionError, 600, 609);
        R_DEFINE_ERROR_RESULT(NullRegionCodeBuffer,                        601);

    R_DEFINE_ERROR_RANGE(UsbError, 770, 779);
        R_DEFINE_ERROR_RESULT(NullUsbTypeCPowerSourceCircuitVersionBuffer, 772);
    R_DEFINE_ERROR_RANGE(BatteryError, 780, 789);
        R_DEFINE_ERROR_RESULT(NullBatteryLotBuffer,                        781);
        R_DEFINE_ERROR_RESULT(NullBatteryVersionBuffer,                    782);
    R_DEFINE_ERROR_RANGE(SerialNumberError, 790, 799);
        R_DEFINE_ERROR_RESULT(NullSerialNumberBuffer,                      791);

    R_DEFINE_ERROR_RANGE(ProductModelError, 1020, 1029);
        R_DEFINE_ERROR_RESULT(NullProductModelBuffer,                         1021);

    R_DEFINE_ERROR_RANGE(CertificateError, 1040, 1049);
        R_DEFINE_ERROR_RESULT(NullDeviceCertificateBuffer,                    1041);
        R_DEFINE_ERROR_RESULT(NullETicketCertificateBuffer,                   1042);

    R_DEFINE_ERROR_RANGE(SslError, 1080, 1089);
        R_DEFINE_ERROR_RESULT(NullSslKeyBuffer,                               1081);
        R_DEFINE_ERROR_RESULT(NullSslCertificateBuffer,                       1082);

    R_DEFINE_ERROR_RANGE(GameCardError, 1100, 1109);
        R_DEFINE_ERROR_RESULT(NullGameCardKeyBuffer,                          1101);
        R_DEFINE_ERROR_RESULT(NullGameCardCertificateBuffer,                  1102);
    R_DEFINE_ERROR_RANGE(KeyError, 1120, 1129);
        R_DEFINE_ERROR_RESULT(NullDeviceKeyBuffer,                            1121);
        R_DEFINE_ERROR_RESULT(NullETicketKeyBuffer,                           1122);
    R_DEFINE_ERROR_RANGE(SpeakerError, 1130, 1139);
        R_DEFINE_ERROR_RESULT(NullSpeakerParameterBuffer,                     1131);

    R_DEFINE_ERROR_RANGE(LcdError, 1220, 1229);
        R_DEFINE_ERROR_RESULT(NullLcdVendorIdBuffer,                          1221);

    R_DEFINE_ERROR_RANGE(AmiiboError, 1270, 1279);
        R_DEFINE_ERROR_RESULT(NullAmiiboKeyBuffer,                            1271);
        R_DEFINE_ERROR_RESULT(NullAmiiboEcqvCertificateBuffer,                1272);
        R_DEFINE_ERROR_RESULT(NullAmiiboEcdsaCertificateBuffer,               1273);
        R_DEFINE_ERROR_RESULT(NullAmiiboEcqvBlsKeyBuffer,                     1274);
        R_DEFINE_ERROR_RESULT(NullAmiiboEcqvBlsCertificateBuffer,             1275);
        R_DEFINE_ERROR_RESULT(NullAmiiboEcqvBlsRootCertificateBuffer,         1276);

    R_DEFINE_ERROR_RANGE(AnalogStickError, 1300, 1309);
        R_DEFINE_ERROR_RESULT(NullAnalogStickModuleTypeBuffer,                1301);
        R_DEFINE_ERROR_RESULT(NullAnalogStickModelParameterBuffer,            1302);
        R_DEFINE_ERROR_RESULT(NullAnalogStickFactoryCalibrationBuffer,        1303);

    R_DEFINE_ERROR_RANGE(ConsoleSixAxisSensorError, 1320, 1329);
        R_DEFINE_ERROR_RESULT(NullConsoleSixAxisSensorModuleTypeBuffer,       1321);
        R_DEFINE_ERROR_RESULT(NullConsoleSixAxisSensorHorizontalOffsetBuffer, 1322);
        R_DEFINE_ERROR_RESULT(NullConsoleSixAxisSensorMountTypeBuffer,        1323);

    R_DEFINE_ERROR_RANGE(HomeMenuSchemeError, 1420, 1429);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeMainColorVariationBuffer,     1422);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeSubColorBuffer,               1423);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeBezelColorBuffer,             1424);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeMainColor1Buffer,             1425);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeMainColor2Buffer,             1426);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeMainColor3Buffer,             1427);
        R_DEFINE_ERROR_RESULT(NullHomeMenuSchemeModelBuffer,                  1428);

    namespace factory {

        R_DEFINE_ERROR_RANGE(CalibrationDataError, 580, 599);
            R_DEFINE_ERROR_RESULT(CalibrationDataFileSystemCorrupted, 581);
            R_DEFINE_ERROR_RESULT(CalibrationDataCrcError,            582);
            R_DEFINE_ERROR_RESULT(CalibrationDataShaError,            583);

    }

}
