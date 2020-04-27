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
#include <stratosphere.hpp>

namespace ams::settings::impl {

    class RemoteFactorySettingsServer final : public IFactorySettingsServer {
        public:
            RemoteFactorySettingsServer() { /* ... */ }

            ~RemoteFactorySettingsServer() { ::setcalExit(); }
        public:
            virtual Result GetBluetoothBdAddress(sf::Out<factory::BdAddress> out) override;
            virtual Result GetConfigurationId1(sf::Out<factory::ConfigurationId1> out) override;
            virtual Result GetAccelerometerOffset(sf::Out<factory::AccelerometerOffset> out) override;
            virtual Result GetAccelerometerScale(sf::Out<factory::AccelerometerScale> out) override;
            virtual Result GetGyroscopeOffset(sf::Out<factory::GyroscopeOffset> out) override;
            virtual Result GetGyroscopeScale(sf::Out<factory::GyroscopeScale> out) override;
            virtual Result GetWirelessLanMacAddress(sf::Out<factory::MacAddress> out) override;
            virtual Result GetWirelessLanCountryCodeCount(sf::Out<s32> out) override;
            virtual Result GetWirelessLanCountryCodes(sf::Out<s32> out_count, sf::OutArray<factory::CountryCode> out) override;
            virtual Result GetSerialNumber(sf::Out<factory::SerialNumber> out) override;
            virtual Result SetInitialSystemAppletProgramId(ncm::ProgramId id) override;
            virtual Result SetOverlayDispProgramId(ncm::ProgramId id) override;
            virtual Result GetBatteryLot(sf::Out<BatteryLot> out) override;
            virtual Result GetEciDeviceCertificate(sf::Out<factory::EccB233DeviceCertificate> out) override;
            virtual Result GetEticketDeviceCertificate(sf::Out<factory::Rsa2048DeviceCertificate> out) override;
            virtual Result GetSslKey(sf::Out<factory::SslKey> out) override;
            virtual Result GetSslCertificate(sf::Out<factory::SslCertificate> out) override;
            virtual Result GetGameCardKey(sf::Out<factory::GameCardKey> out) override;
            virtual Result GetGameCardCertificate(sf::Out<factory::GameCardCertificate> out) override;
            virtual Result GetEciDeviceKey(sf::Out<factory::EccB233DeviceKey> out) override;
            virtual Result GetEticketDeviceKey(sf::Out<factory::Rsa2048DeviceKey> out) override;
            virtual Result GetSpeakerParameter(sf::Out<factory::SpeakerParameter> out) override;
            virtual Result GetLcdVendorId(sf::Out<u32> out) override;
            virtual Result GetEciDeviceCertificate2(sf::Out<factory::Rsa2048DeviceCertificate> out) override;
            virtual Result GetEciDeviceKey2(sf::Out<factory::Rsa2048DeviceKey> out) override;
            virtual Result GetAmiiboKey(sf::Out<factory::AmiiboKey> out) override;
            virtual Result GetAmiiboEcqvCertificate(sf::Out<factory::AmiiboEcqvCertificate> out) override;
            virtual Result GetAmiiboEcdsaCertificate(sf::Out<factory::AmiiboEcdsaCertificate> out) override;
            virtual Result GetAmiiboEcqvBlsKey(sf::Out<factory::AmiiboEcqvBlsKey> out) override;
            virtual Result GetAmiiboEcqvBlsCertificate(sf::Out<factory::AmiiboEcqvBlsCertificate> out) override;
            virtual Result GetAmiiboEcqvBlsRootCertificate(sf::Out<factory::AmiiboEcqvBlsRootCertificate> out) override;
            virtual Result GetUsbTypeCPowerSourceCircuitVersion(sf::Out<u8> out) override;
            virtual Result GetAnalogStickModuleTypeL(sf::Out<u8> out) override;
            virtual Result GetAnalogStickModelParameterL(sf::Out<factory::AnalogStickModelParameter> out) override;
            virtual Result GetAnalogStickFactoryCalibrationL(sf::Out<factory::AnalogStickFactoryCalibration> out) override;
            virtual Result GetAnalogStickModuleTypeR(sf::Out<u8> out) override;
            virtual Result GetAnalogStickModelParameterR(sf::Out<factory::AnalogStickModelParameter> out) override;
            virtual Result GetAnalogStickFactoryCalibrationR(sf::Out<factory::AnalogStickFactoryCalibration> out) override;
            virtual Result GetConsoleSixAxisSensorModuleType(sf::Out<u8> out) override;
            virtual Result GetConsoleSixAxisSensorHorizontalOffset(sf::Out<factory::ConsoleSixAxisSensorHorizontalOffset> out) override;
            virtual Result GetBatteryVersion(sf::Out<u8> out) override;
            virtual Result GetDeviceId(sf::Out<u64> out) override;
            virtual Result GetConsoleSixAxisSensorMountType(sf::Out<u8> out) override;
    };

}
