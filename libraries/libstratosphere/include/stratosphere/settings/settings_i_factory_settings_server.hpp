/*
 * Copyright (c) 2019-2020 Adubbz, Atmosphère-NX
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
#include <stratosphere/sf.hpp>
#include <stratosphere/ncm/ncm_program_id.hpp>
#include <stratosphere/settings/factory/settings_amiibo.hpp>
#include <stratosphere/settings/factory/settings_analog_stick.hpp>
#include <stratosphere/settings/factory/settings_bluetooth.hpp>
#include <stratosphere/settings/factory/settings_configuration_id.hpp>
#include <stratosphere/settings/factory/settings_device_certificate.hpp>
#include <stratosphere/settings/factory/settings_device_key.hpp>
#include <stratosphere/settings/factory/settings_game_card.hpp>
#include <stratosphere/settings/factory/settings_motion_sensor.hpp>
#include <stratosphere/settings/factory/settings_serial_number.hpp>
#include <stratosphere/settings/factory/settings_speaker.hpp>
#include <stratosphere/settings/factory/settings_ssl.hpp>
#include <stratosphere/settings/factory/settings_wireless_lan.hpp>

namespace ams::settings {

    class IFactorySettingsServer : public sf::IServiceObject {
        protected:
            enum class CommandId {
                GetBluetoothBdAddress                      = 0,
                GetConfigurationId1                        = 1,
                GetAccelerometerOffset                     = 2,
                GetAccelerometerScale                      = 3,
                GetGyroscopeOffset                         = 4,
                GetGyroscopeScale                          = 5,
                GetWirelessLanMacAddress                   = 6,
                GetWirelessLanCountryCodeCount             = 7,
                GetWirelessLanCountryCodes                 = 8,
                GetSerialNumber                            = 9,
                SetInitialSystemAppletProgramId            = 10,
                SetOverlayDispProgramId                    = 11,
                GetBatteryLot                              = 12,
                GetEciDeviceCertificate                    = 14,
                GetEticketDeviceCertificate                = 15,
                GetSslKey                                  = 16,
                GetSslCertificate                          = 17,
                GetGameCardKey                             = 18,
                GetGameCardCertificate                     = 19,
                GetEciDeviceKey                            = 20,
                GetEticketDeviceKey                        = 21,
                GetSpeakerParameter                        = 22,
                GetLcdVendorId                             = 23,
                GetEciDeviceCertificate2                   = 24,
                GetEciDeviceKey2                           = 25,
                GetAmiiboKey                               = 26,
                GetAmiiboEcqvCertificate                   = 27,
                GetAmiiboEcdsaCertificate                  = 28,
                GetAmiiboEcqvBlsKey                        = 29,
                GetAmiiboEcqvBlsCertificate                = 30,
                GetAmiiboEcqvBlsRootCertificate            = 31,
                GetUsbTypeCPowerSourceCircuitVersion       = 32,
                GetAnalogStickModuleTypeL                  = 33,
                GetAnalogStickModelParameterL              = 34,
                GetAnalogStickFactoryCalibrationL          = 35,
                GetAnalogStickModuleTypeR                  = 36,
                GetAnalogStickModelParameterR              = 37,
                GetAnalogStickFactoryCalibrationR          = 38,
                GetConsoleSixAxisSensorModuleType          = 39,
                GetConsoleSixAxisSensorHorizontalOffset    = 40,
                GetBatteryVersion                          = 41,
                GetDeviceId                                = 42,
                GetConsoleSixAxisSensorMountType           = 43,
            };
        public:
            virtual Result GetBluetoothBdAddress(sf::Out<factory::BdAddress> out) = 0;
            virtual Result GetConfigurationId1(sf::Out<factory::ConfigurationId1> out) = 0;
            virtual Result GetAccelerometerOffset(sf::Out<factory::AccelerometerOffset> out) = 0;
            virtual Result GetAccelerometerScale(sf::Out<factory::AccelerometerScale> out) = 0;
            virtual Result GetGyroscopeOffset(sf::Out<factory::GyroscopeOffset> out) = 0;
            virtual Result GetGyroscopeScale(sf::Out<factory::GyroscopeScale> out) = 0;
            virtual Result GetWirelessLanMacAddress(sf::Out<factory::MacAddress> out) = 0;
            virtual Result GetWirelessLanCountryCodeCount(sf::Out<s32> out) = 0;
            virtual Result GetWirelessLanCountryCodes(sf::Out<s32> out_count, sf::OutArray<factory::CountryCode> out) = 0;
            virtual Result GetSerialNumber(sf::Out<factory::SerialNumber> out) = 0;
            virtual Result SetInitialSystemAppletProgramId(ncm::ProgramId id) = 0;
            virtual Result SetOverlayDispProgramId(ncm::ProgramId id) = 0;
            virtual Result GetBatteryLot(sf::Out<BatteryLot> out) = 0;
            virtual Result GetEciDeviceCertificate(sf::Out<factory::EccB233DeviceCertificate> out) = 0;
            virtual Result GetEticketDeviceCertificate(sf::Out<factory::Rsa2048DeviceCertificate> out) = 0;
            virtual Result GetSslKey(sf::Out<factory::SslKey> out) = 0;
            virtual Result GetSslCertificate(sf::Out<factory::SslCertificate> out) = 0;
            virtual Result GetGameCardKey(sf::Out<factory::GameCardKey> out) = 0;
            virtual Result GetGameCardCertificate(sf::Out<factory::GameCardCertificate> out) = 0;
            virtual Result GetEciDeviceKey(sf::Out<factory::EccB233DeviceKey> out) = 0;
            virtual Result GetEticketDeviceKey(sf::Out<factory::Rsa2048DeviceKey> out) = 0;
            virtual Result GetSpeakerParameter(sf::Out<factory::SpeakerParameter> out) = 0;
            virtual Result GetLcdVendorId(sf::Out<u32> out) = 0;
            virtual Result GetEciDeviceCertificate2(sf::Out<factory::Rsa2048DeviceCertificate> out) = 0;
            virtual Result GetEciDeviceKey2(sf::Out<factory::Rsa2048DeviceKey> out) = 0;
            virtual Result GetAmiiboKey(sf::Out<factory::AmiiboKey> out) = 0;
            virtual Result GetAmiiboEcqvCertificate(sf::Out<factory::AmiiboEcqvCertificate> out) = 0;
            virtual Result GetAmiiboEcdsaCertificate(sf::Out<factory::AmiiboEcdsaCertificate> out) = 0;
            virtual Result GetAmiiboEcqvBlsKey(sf::Out<factory::AmiiboEcqvBlsKey> out) = 0;
            virtual Result GetAmiiboEcqvBlsCertificate(sf::Out<factory::AmiiboEcqvBlsCertificate> out) = 0;
            virtual Result GetAmiiboEcqvBlsRootCertificate(sf::Out<factory::AmiiboEcqvBlsRootCertificate> out) = 0;
            virtual Result GetUsbTypeCPowerSourceCircuitVersion(sf::Out<u8> out) = 0;
            virtual Result GetAnalogStickModuleTypeL(sf::Out<u8> out) = 0;
            virtual Result GetAnalogStickModelParameterL(sf::Out<factory::AnalogStickModelParameter> out) = 0;
            virtual Result GetAnalogStickFactoryCalibrationL(sf::Out<factory::AnalogStickFactoryCalibration> out) = 0;
            virtual Result GetAnalogStickModuleTypeR(sf::Out<u8> out) = 0;
            virtual Result GetAnalogStickModelParameterR(sf::Out<factory::AnalogStickModelParameter> out) = 0;
            virtual Result GetAnalogStickFactoryCalibrationR(sf::Out<factory::AnalogStickFactoryCalibration> out) = 0;
            virtual Result GetConsoleSixAxisSensorModuleType(sf::Out<u8> out) = 0;
            virtual Result GetConsoleSixAxisSensorHorizontalOffset(sf::Out<factory::ConsoleSixAxisSensorHorizontalOffset> out) = 0;
            virtual Result GetBatteryVersion(sf::Out<u8> out) = 0;
            virtual Result GetDeviceId(sf::Out<u64> out) = 0;
            virtual Result GetConsoleSixAxisSensorMountType(sf::Out<u8> out) = 0;
        public:
            DEFINE_SERVICE_DISPATCH_TABLE {
                MAKE_SERVICE_COMMAND_META(GetBluetoothBdAddress),
                MAKE_SERVICE_COMMAND_META(GetConfigurationId1),
                MAKE_SERVICE_COMMAND_META(GetAccelerometerOffset),
                MAKE_SERVICE_COMMAND_META(GetAccelerometerScale),
                MAKE_SERVICE_COMMAND_META(GetGyroscopeOffset),
                MAKE_SERVICE_COMMAND_META(GetGyroscopeScale),
                MAKE_SERVICE_COMMAND_META(GetWirelessLanMacAddress),
                MAKE_SERVICE_COMMAND_META(GetWirelessLanCountryCodeCount),
                MAKE_SERVICE_COMMAND_META(GetWirelessLanCountryCodes),
                MAKE_SERVICE_COMMAND_META(GetSerialNumber),
                MAKE_SERVICE_COMMAND_META(SetInitialSystemAppletProgramId),
                MAKE_SERVICE_COMMAND_META(SetOverlayDispProgramId),
                MAKE_SERVICE_COMMAND_META(GetBatteryLot),
                MAKE_SERVICE_COMMAND_META(GetEciDeviceCertificate),
                MAKE_SERVICE_COMMAND_META(GetEticketDeviceCertificate),
                MAKE_SERVICE_COMMAND_META(GetSslKey),
                MAKE_SERVICE_COMMAND_META(GetSslCertificate),
                MAKE_SERVICE_COMMAND_META(GetGameCardKey),
                MAKE_SERVICE_COMMAND_META(GetGameCardCertificate),
                MAKE_SERVICE_COMMAND_META(GetEciDeviceKey),
                MAKE_SERVICE_COMMAND_META(GetEticketDeviceKey),
                MAKE_SERVICE_COMMAND_META(GetSpeakerParameter),
                MAKE_SERVICE_COMMAND_META(GetLcdVendorId,                             hos::Version_4_0_0),
                MAKE_SERVICE_COMMAND_META(GetEciDeviceCertificate2,                   hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetEciDeviceKey2,                           hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboKey,                               hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboEcqvCertificate,                   hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboEcdsaCertificate,                  hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboEcqvBlsKey,                        hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboEcqvBlsCertificate,                hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAmiiboEcqvBlsRootCertificate,            hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetUsbTypeCPowerSourceCircuitVersion,       hos::Version_5_0_0),
                MAKE_SERVICE_COMMAND_META(GetAnalogStickModuleTypeL,                  hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetAnalogStickModelParameterL,              hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetAnalogStickFactoryCalibrationL,          hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetAnalogStickModuleTypeR,                  hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetAnalogStickModelParameterR,              hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetAnalogStickFactoryCalibrationR,          hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetConsoleSixAxisSensorModuleType,          hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetConsoleSixAxisSensorHorizontalOffset,    hos::Version_8_1_0), /* Actually 8.1.1. */
                MAKE_SERVICE_COMMAND_META(GetBatteryVersion,                          hos::Version_6_0_0),
                MAKE_SERVICE_COMMAND_META(GetDeviceId,                                hos::Version_10_0_0),
                MAKE_SERVICE_COMMAND_META(GetConsoleSixAxisSensorMountType,           hos::Version_10_0_0),
            };
    };

    Result CreateFactorySettingsServerProxy(std::shared_ptr<IFactorySettingsServer> *out);

}
