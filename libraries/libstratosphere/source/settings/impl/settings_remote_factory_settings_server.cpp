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
#include "settings_remote_factory_settings_server.hpp"

namespace ams::settings::impl {

    namespace {

        std::atomic<bool> g_initialized = false;
        os::SdkMutex g_init_mutex;
        std::shared_ptr<IFactorySettingsServer> g_intf;

        Result CreateFactorySettingsServerProxyByHipc(std::shared_ptr<IFactorySettingsServer> *out) {
            if (AMS_UNLIKELY(!g_initialized)) {
                std::scoped_lock lk(g_init_mutex);
                if (!g_initialized) {
                    sm::DoWithSession([&]() {
                        R_ABORT_UNLESS(setcalInitialize());
                    });

                    g_intf = std::make_shared<RemoteFactorySettingsServer>();
                    g_initialized = true;
                }
            }

            *out = g_intf;
            return ResultSuccess();
        }

    }
    
    Result WEAK_SYMBOL CreateFactorySettingsServerProxy(std::shared_ptr<IFactorySettingsServer> *out) {
        return CreateFactorySettingsServerProxyByHipc(out);
    }

    Result RemoteFactorySettingsServer::GetBluetoothBdAddress(sf::Out<factory::BdAddress> out) {
        static_assert(sizeof(factory::BdAddress) == sizeof(::SetCalBdAddress));
        return setcalGetBdAddress(reinterpret_cast<::SetCalBdAddress *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetConfigurationId1(sf::Out<factory::ConfigurationId1> out) {
        static_assert(sizeof(factory::ConfigurationId1) == sizeof(::SetCalConfigurationId1));
        return setcalGetConfigurationId1(reinterpret_cast<::SetCalConfigurationId1 *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAccelerometerOffset(sf::Out<factory::AccelerometerOffset> out) {
        static_assert(sizeof(factory::AccelerometerOffset) == sizeof(::SetCalAccelerometerOffset));
        return setcalGetAccelerometerOffset(reinterpret_cast<::SetCalAccelerometerOffset *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAccelerometerScale(sf::Out<factory::AccelerometerScale> out) {
        static_assert(sizeof(factory::AccelerometerScale) == sizeof(::SetCalAccelerometerScale));
        return setcalGetAccelerometerScale(reinterpret_cast<::SetCalAccelerometerScale *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetGyroscopeOffset(sf::Out<factory::GyroscopeOffset> out) {
        static_assert(sizeof(factory::GyroscopeOffset) == sizeof(::SetCalGyroscopeOffset));
        return setcalGetGyroscopeOffset(reinterpret_cast<::SetCalGyroscopeOffset *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetGyroscopeScale(sf::Out<factory::GyroscopeScale> out) {
        static_assert(sizeof(factory::GyroscopeScale) == sizeof(::SetCalGyroscopeScale));
        return setcalGetGyroscopeScale(reinterpret_cast<::SetCalGyroscopeScale *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetWirelessLanMacAddress(sf::Out<factory::MacAddress> out) {
        static_assert(sizeof(factory::MacAddress) == sizeof(::SetCalMacAddress));
        return setcalGetWirelessLanMacAddress(reinterpret_cast<::SetCalMacAddress *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetWirelessLanCountryCodeCount(sf::Out<s32> out) {
        return setcalGetWirelessLanCountryCodeCount(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetWirelessLanCountryCodes(sf::Out<s32> out_count, sf::OutArray<factory::CountryCode> out) {
        static_assert(sizeof(factory::CountryCode) == sizeof(::SetCalCountryCode));
        return setcalGetWirelessLanCountryCodes(out_count.GetPointer(), reinterpret_cast<::SetCalCountryCode *>(out.GetPointer()), out.GetSize());
    }

    Result RemoteFactorySettingsServer::GetSerialNumber(sf::Out<factory::SerialNumber> out) {
        static_assert(sizeof(factory::SerialNumber) == sizeof(::SetCalSerialNumber));
        return setcalGetSerialNumber(reinterpret_cast<::SetCalSerialNumber *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::SetInitialSystemAppletProgramId(ncm::ProgramId id) {
        return setcalSetInitialSystemAppletProgramId(id.value);
    }

    Result RemoteFactorySettingsServer::SetOverlayDispProgramId(ncm::ProgramId id) {
        return setcalSetOverlayDispProgramId(id.value);
    }

    Result RemoteFactorySettingsServer::GetBatteryLot(sf::Out<BatteryLot> out) {
        static_assert(sizeof(BatteryLot) == sizeof(::SetBatteryLot));
        return setcalGetBatteryLot(reinterpret_cast<::SetBatteryLot *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetEciDeviceCertificate(sf::Out<factory::EccB233DeviceCertificate> out) {
        static_assert(sizeof(factory::EccB233DeviceCertificate) == sizeof(::SetCalEccB233DeviceCertificate));
        return setcalGetEciDeviceCertificate(reinterpret_cast<::SetCalEccB233DeviceCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetEticketDeviceCertificate(sf::Out<factory::Rsa2048DeviceCertificate> out) {
        static_assert(sizeof(factory::Rsa2048DeviceCertificate) == sizeof(::SetCalRsa2048DeviceCertificate));
        return setcalGetEticketDeviceCertificate(reinterpret_cast<::SetCalRsa2048DeviceCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetSslKey(sf::Out<factory::SslKey> out) {
        static_assert(sizeof(factory::SslKey) == sizeof(::SetCalSslKey));
        return setcalGetSslKey(reinterpret_cast<::SetCalSslKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetSslCertificate(sf::Out<factory::SslCertificate> out) {
        static_assert(sizeof(factory::SslCertificate) == sizeof(::SetCalSslCertificate));
        return setcalGetSslCertificate(reinterpret_cast<::SetCalSslCertificate *>(out.GetPointer()));
    }
    
    Result RemoteFactorySettingsServer::GetGameCardKey(sf::Out<factory::GameCardKey> out) {
        static_assert(sizeof(factory::GameCardKey) == sizeof(::SetCalGameCardKey));
        return setcalGetGameCardKey(reinterpret_cast<::SetCalGameCardKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetGameCardCertificate(sf::Out<factory::GameCardCertificate> out) {
        static_assert(sizeof(factory::GameCardCertificate) == sizeof(::SetCalGameCardCertificate));
        return setcalGetGameCardCertificate(reinterpret_cast<::SetCalGameCardCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetEciDeviceKey(sf::Out<factory::EccB233DeviceKey> out) {
        static_assert(sizeof(factory::EccB233DeviceKey) == sizeof(::SetCalEccB233DeviceKey));
        return setcalGetEciDeviceKey(reinterpret_cast<::SetCalEccB233DeviceKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetEticketDeviceKey(sf::Out<factory::Rsa2048DeviceKey> out) {
        static_assert(sizeof(factory::Rsa2048DeviceKey) == sizeof(::SetCalRsa2048DeviceKey));
        return setcalGetEticketDeviceKey(reinterpret_cast<::SetCalRsa2048DeviceKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetSpeakerParameter(sf::Out<factory::SpeakerParameter> out) {
        static_assert(sizeof(factory::SpeakerParameter) == sizeof(::SetCalSpeakerParameter));
        return setcalGetSpeakerParameter(reinterpret_cast<::SetCalSpeakerParameter *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetLcdVendorId(sf::Out<u32> out) {
        return setcalGetLcdVendorId(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetEciDeviceCertificate2(sf::Out<factory::Rsa2048DeviceCertificate> out) {
        static_assert(sizeof(factory::Rsa2048DeviceCertificate) == sizeof(::SetCalRsa2048DeviceCertificate));
        return setcalGetEciDeviceCertificate2(reinterpret_cast<::SetCalRsa2048DeviceCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetEciDeviceKey2(sf::Out<factory::Rsa2048DeviceKey> out) {
        static_assert(sizeof(factory::Rsa2048DeviceKey) == sizeof(::SetCalRsa2048DeviceKey));
        return setcalGetEciDeviceKey2(reinterpret_cast<::SetCalRsa2048DeviceKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAmiiboKey(sf::Out<factory::AmiiboKey> out) {
        static_assert(sizeof(factory::AmiiboKey) == sizeof(::SetCalAmiiboKey));
        return setcalGetAmiiboKey(reinterpret_cast<::SetCalAmiiboKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAmiiboEcqvCertificate(sf::Out<factory::AmiiboEcqvCertificate> out) {
        static_assert(sizeof(factory::AmiiboEcqvCertificate) == sizeof(::SetCalAmiiboEcqvCertificate));
        return setcalGetAmiiboEcqvCertificate(reinterpret_cast<::SetCalAmiiboEcqvCertificate *>(out.GetPointer()));
    }
    
    Result RemoteFactorySettingsServer::GetAmiiboEcdsaCertificate(sf::Out<factory::AmiiboEcdsaCertificate> out) {
        static_assert(sizeof(factory::AmiiboEcdsaCertificate) == sizeof(::SetCalAmiiboEcdsaCertificate));
        return setcalGetAmiiboEcdsaCertificate(reinterpret_cast<::SetCalAmiiboEcdsaCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAmiiboEcqvBlsKey(sf::Out<factory::AmiiboEcqvBlsKey> out) {
        static_assert(sizeof(factory::AmiiboEcqvBlsKey) == sizeof(::SetCalAmiiboEcqvBlsKey));
        return setcalGetAmiiboEcqvBlsKey(reinterpret_cast<::SetCalAmiiboEcqvBlsKey *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAmiiboEcqvBlsCertificate(sf::Out<factory::AmiiboEcqvBlsCertificate> out) {
        static_assert(sizeof(factory::AmiiboEcqvBlsCertificate) == sizeof(::SetCalAmiiboEcqvBlsCertificate));
        return setcalGetAmiiboEcqvBlsCertificate(reinterpret_cast<::SetCalAmiiboEcqvBlsCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAmiiboEcqvBlsRootCertificate(sf::Out<factory::AmiiboEcqvBlsRootCertificate> out) {
        static_assert(sizeof(factory::AmiiboEcqvBlsRootCertificate) == sizeof(::SetCalAmiiboEcqvBlsRootCertificate));
        return setcalGetAmiiboEcqvBlsRootCertificate(reinterpret_cast<::SetCalAmiiboEcqvBlsRootCertificate *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetUsbTypeCPowerSourceCircuitVersion(sf::Out<u8> out) {
        return setcalGetUsbTypeCPowerSourceCircuitVersion(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetAnalogStickModuleTypeL(sf::Out<u8> out) {
        return setcalGetAnalogStickModuleTypeL(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetAnalogStickModelParameterL(sf::Out<factory::AnalogStickModelParameter> out) {
        static_assert(sizeof(factory::AnalogStickModelParameter) == sizeof(::SetCalAnalogStickModelParameter));
        return setcalGetAnalogStickModelParameterL(reinterpret_cast<::SetCalAnalogStickModelParameter *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAnalogStickFactoryCalibrationL(sf::Out<factory::AnalogStickFactoryCalibration> out) {
        static_assert(sizeof(factory::AnalogStickFactoryCalibration) == sizeof(::SetCalAnalogStickFactoryCalibration));
        return setcalGetAnalogStickFactoryCalibrationL(reinterpret_cast<::SetCalAnalogStickFactoryCalibration *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetAnalogStickModuleTypeR(sf::Out<u8> out) {
        return setcalGetAnalogStickModuleTypeR(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetAnalogStickModelParameterR(sf::Out<factory::AnalogStickModelParameter> out) {
        static_assert(sizeof(factory::AnalogStickModelParameter) == sizeof(::SetCalAnalogStickModelParameter));
        return setcalGetAnalogStickModelParameterR(reinterpret_cast<::SetCalAnalogStickModelParameter *>(out.GetPointer()));
    }
    
    Result RemoteFactorySettingsServer::GetAnalogStickFactoryCalibrationR(sf::Out<factory::AnalogStickFactoryCalibration> out) {
        static_assert(sizeof(factory::AnalogStickFactoryCalibration) == sizeof(::SetCalAnalogStickFactoryCalibration));
        return setcalGetAnalogStickFactoryCalibrationR(reinterpret_cast<::SetCalAnalogStickFactoryCalibration *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetConsoleSixAxisSensorModuleType(sf::Out<u8> out) {
        return setcalGetConsoleSixAxisSensorModuleType(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetConsoleSixAxisSensorHorizontalOffset(sf::Out<factory::ConsoleSixAxisSensorHorizontalOffset> out) {
        static_assert(sizeof(factory::ConsoleSixAxisSensorHorizontalOffset) == sizeof(::SetCalConsoleSixAxisSensorHorizontalOffset));
        return setcalGetConsoleSixAxisSensorHorizontalOffset(reinterpret_cast<::SetCalConsoleSixAxisSensorHorizontalOffset *>(out.GetPointer()));
    }

    Result RemoteFactorySettingsServer::GetBatteryVersion(sf::Out<u8> out) {
        return setcalGetBatteryVersion(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetDeviceId(sf::Out<u64> out) {
        return setcalGetDeviceId(out.GetPointer());
    }

    Result RemoteFactorySettingsServer::GetConsoleSixAxisSensorMountType(sf::Out<u8> out) {
        return setcalGetConsoleSixAxisSensorMountType(out.GetPointer());
    }

}
