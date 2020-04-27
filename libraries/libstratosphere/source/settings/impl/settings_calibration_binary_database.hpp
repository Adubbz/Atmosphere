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
#include <stratosphere.hpp>

namespace ams::settings::impl {

    struct Sha256Hash {
        u8 data[crypto::Sha256Generator::HashSize];
    };

    #define DEFINE_CALIBRATION_CRC_BLOCK(_BlockTypeName, _BlockSize, _Decl) \
    struct _BlockTypeName {                                                 \
        using TypeSizeStruct = struct PACKED { _Decl; };                           \
        _Decl;                                                              \
        static_assert(_BlockSize >= sizeof(TypeSizeStruct) + sizeof(u16));  \
        u8 pad[_BlockSize - sizeof(TypeSizeStruct) - sizeof(u16)];          \
        u16 crc;                                                            \
    };                                                                      \
    static_assert(sizeof(_BlockTypeName) == _BlockSize);        
    
    #define DEFINE_CALIBRATION_SHA_BLOCK(_BlockTypeName, _BlockSize, _Decl) \
    struct _BlockTypeName {                                                       \
        using TypeSizeStruct = struct PACKED { _Decl; };                                 \
        _Decl;                                                                    \
        static_assert(_BlockSize == sizeof(TypeSizeStruct) + sizeof(Sha256Hash)); \
        Sha256Hash sha256_hash;                                                   \
    };                                                                            \
    static_assert(sizeof(_BlockTypeName) == _BlockSize);

    DEFINE_CALIBRATION_CRC_BLOCK(ConfigurationId1Block,                     0x20,   settings::factory::ConfigurationId1                        id)
    DEFINE_CALIBRATION_CRC_BLOCK(WirelessLanCountryCodesBlock,              0x190,  u32 count; u32 reserved_04; settings::factory::CountryCode country_codes[130])
    DEFINE_CALIBRATION_CRC_BLOCK(WirelessLanMacAddressBlock,                0x8,    settings::factory::MacAddress                              mac_address)
    DEFINE_CALIBRATION_CRC_BLOCK(BluetoothBdAddressBlock,                   0x8,    settings::factory::BdAddress                               bd_address)
    DEFINE_CALIBRATION_CRC_BLOCK(AccelerometerOffsetBlock,                  0x8,    settings::factory::AccelerometerOffset                     accelerometer_offset)
    DEFINE_CALIBRATION_CRC_BLOCK(AccelerometerScaleBlock,                   0x8,    settings::factory::AccelerometerScale                      accelerometer_scale)
    DEFINE_CALIBRATION_CRC_BLOCK(GyroscopeOffsetBlock,                      0x8,    settings::factory::GyroscopeOffset                         gyroscope_offset)
    DEFINE_CALIBRATION_CRC_BLOCK(GyroscopeScaleBlock,                       0x8,    settings::factory::GyroscopeScale                          gyroscope_scale)
    DEFINE_CALIBRATION_CRC_BLOCK(SerialNumberBlock,                         0x20,   settings::factory::SerialNumber                            serial_number)
    DEFINE_CALIBRATION_CRC_BLOCK(EccP256DeviceKeyBlock,                     0x40,   u8                                                         data[0x30])
    DEFINE_CALIBRATION_CRC_BLOCK(EccP256DeviceCertificateBlock,             0x190,  settings::factory::EccP256DeviceCertificate                certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(EccB233DeviceKeyBlock,                     0x40,   u8                                                         data[0x30])
    DEFINE_CALIBRATION_CRC_BLOCK(EccB233DeviceCertificateBlock,             0x190,  settings::factory::EccB233DeviceCertificate                certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(EccP256ETicketKeyBlock,                    0x40,   u8                                                         data[0x30])
    DEFINE_CALIBRATION_CRC_BLOCK(EccP256ETicketCertificateBlock,            0x190,  settings::factory::EccP256DeviceCertificate                certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(EccB233ETicketKeyBlock,                    0x40,   u8                                                         data[0x30])
    DEFINE_CALIBRATION_CRC_BLOCK(EccB233ETicketCertificateBlock,            0x190,  settings::factory::EccB233DeviceCertificate                certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(SslKeyBlock,                               0x120,  u8                                                         data[0x110])
    DEFINE_CALIBRATION_CRC_BLOCK(SslCertificateSizeBlock,                   0x10,   u64                                                        size)
    DEFINE_CALIBRATION_SHA_BLOCK(SslCertificateBlock,                       0x820,  u8                                                         data[0x800])
    DEFINE_CALIBRATION_SHA_BLOCK(RandomNumberBlock,                         0x1020, u8                                                         data[0x1000])
    DEFINE_CALIBRATION_CRC_BLOCK(GameCardKeyBlock,                          0x120,  u8                                                         data[0x110])
    DEFINE_CALIBRATION_SHA_BLOCK(GameCardCertificateBlock,                  0x420,  settings::factory::GameCardCertificate                     certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(Rsa2048ETicketKeyBlock,                    0x230,  u8                                                         data[0x220])
    DEFINE_CALIBRATION_CRC_BLOCK(Rsa2048ETicketCertificateBlock,            0x250,  settings::factory::Rsa2048DeviceCertificate                certificate)
    DEFINE_CALIBRATION_CRC_BLOCK(BatteryLotBlock,                           0x20,   settings::BatteryLot                                       battery_lot)
    DEFINE_CALIBRATION_CRC_BLOCK(SpeakerParameterBlock,                     0x810,  settings::factory::SpeakerParameter                        speaker_parameter)
    DEFINE_CALIBRATION_CRC_BLOCK(RegionCodeBlock,                           0x10,   settings::factory::RegionCode                              region_code)
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboKeyBlock,                            0x60,   u8                                                         data[0x54])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvCertificateBlock,                0x20,   u8                                                         data[0x14])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcdsaCertificateBlock,               0x80,   u8                                                         data[0x70])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsKeyBlock,                     0x50,   u8                                                         data[0x44])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsCertificateBlock,             0x30,   u8                                                         data[0x20])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsRootCertificateBlock,         0xA0,   u8                                                         data[0x90])
    DEFINE_CALIBRATION_CRC_BLOCK(ProductModelBlock,                         0x10,   u32                                                        model)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeMainColorVariationBlock,     0x10,   s32                                                        color_variation)
    DEFINE_CALIBRATION_CRC_BLOCK(BacklightBrightnessCoefficientsBlock,      0x10,   util::Float3                                               coefficients)
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedEccB233DeviceKeyBlock,             0x60,   u8                                                         data[0x50])
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedEccP256ETicketKeyBlock,            0x60,   u8                                                         data[0x50])
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedEccB233ETicketKeyBlock,            0x60,   u8                                                         data[0x50])
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedRsa2048ETicketKeyBlock,            0x250,  u8                                                         data[0x240])
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedSslKeyBlock,                       0x140,  u8                                                         data[0x130])
    DEFINE_CALIBRATION_CRC_BLOCK(ExtendedGameCardKeyBlock,                  0x140,  u8                                                         data[0x130])
    DEFINE_CALIBRATION_CRC_BLOCK(LcdVendorIdBlock,                          0x10,   u32                                                        vendor_id)
    DEFINE_CALIBRATION_CRC_BLOCK(Rsa2048DeviceKeyBlock,                     0x250,  u8                                                         data[0x240])
    DEFINE_CALIBRATION_CRC_BLOCK(Rsa2048DeviceCertificateBlock,             0x250,  u8                                                         data[0x240])
    DEFINE_CALIBRATION_CRC_BLOCK(UsbTypeCPowerSourceCircuitVersionBlock,    0x10,   u8                                                         version)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeSubColorBlock,               0x10,   util::Unorm8x4                                             color)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeBezelColorBlock,             0x10,   util::Unorm8x4                                             color)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeMainColor1Block,             0x10,   util::Unorm8x4                                             color)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeMainColor2Block,             0x10,   util::Unorm8x4                                             color)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeMainColor3Block,             0x10,   util::Unorm8x4                                             color)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickModuleTypeLBlock,               0x10,   u8                                                         module_type)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickModelParameterLBlock,           0x20,   settings::factory::AnalogStickModelParameter               model_parameter)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickFactoryCalibrationLBlock,       0x10,   settings::factory::AnalogStickFactoryCalibration           calibration)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickModuleTypeRBlock,               0x10,   u8                                                         module_type)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickModelParameterRBlock,           0x20,   settings::factory::AnalogStickModelParameter               model_parameter)
    DEFINE_CALIBRATION_CRC_BLOCK(AnalogStickFactoryCalibrationRBlock,       0x10,   settings::factory::AnalogStickFactoryCalibration           calibration)
    DEFINE_CALIBRATION_CRC_BLOCK(ConsoleSixAxisSensorModuleTypeBlock,       0x10,   u8                                                         module_type)
    DEFINE_CALIBRATION_CRC_BLOCK(ConsoleSixAxisSensorHorizontalOffsetBlock, 0x10,   settings::factory::ConsoleSixAxisSensorHorizontalOffset    offset)
    DEFINE_CALIBRATION_CRC_BLOCK(BatteryVersionBlock,                       0x10,   u8                                                         version)
    DEFINE_CALIBRATION_CRC_BLOCK(HomeMenuSchemeModelBlock,                  0x10,   u32                                                        model)
    DEFINE_CALIBRATION_CRC_BLOCK(ConsoleSixAxisSensorMountTypeBlock,        0x10,   u8                                                         mount_type)

    #undef DEFINE_CALIBRATION_CRC_BLOCK
    #undef DEFINE_CALIBRATION_SHA_BLOCK

    constexpr inline size_t CalibrationBinarySize = 0x8000;
    constexpr inline u32 CalibrationMagic = util::FourCC<'C','A','L','0'>::Code;

    struct CalibrationInfoHeader {
        u32 magic;
        u32 version;
        u32 body_size;
        u16 model;
        u16 update_count;
        u8  pad[0xE];
        u16 crc;
        Sha256Hash body_hash;
    };
    static_assert(sizeof(CalibrationInfoHeader) == 0x40);

    constexpr inline size_t CalibrationInfoBodySizeMax = CalibrationBinarySize - sizeof(CalibrationInfoHeader);

    struct CalibrationInfoBody {
        ConfigurationId1Block configuration_id_1_block;
        u8 reserved_20[32];
        WirelessLanCountryCodesBlock wireless_lan_country_codes_block;
        WirelessLanMacAddressBlock wireless_lan_mac_address_block;
        u8 reserved_1D8[8];
        BluetoothBdAddressBlock bd_address_block;
        u8 reserved_1E8[8];
        AccelerometerOffsetBlock accelerometer_offset_block;
        AccelerometerScaleBlock accelerometer_scale_block;
        GyroscopeOffsetBlock gyroscope_offset_block;
        GyroscopeScaleBlock gyroscope_scale_block;
        SerialNumberBlock serial_number_block;
        EccP256DeviceKeyBlock ecc_p256_device_key_block;
        EccP256DeviceCertificateBlock ecc_p256_device_certificate_block;
        EccB233DeviceKeyBlock ecc_b233_device_key_block;
        EccB233DeviceCertificateBlock ecc_b233_device_certificate_block;
        EccP256ETicketKeyBlock ecc_p256_eticket_key_block;
        EccP256ETicketCertificateBlock ecc_p256_eticket_certificate_block;
        EccB233ETicketKeyBlock ecc_b233_eticket_key_block;
        EccB233ETicketCertificateBlock ecc_b233_eticket_certificate_block;
        SslKeyBlock ssl_key_block;
        SslCertificateSizeBlock ssl_certificate_size_block;
        SslCertificateBlock ssl_certificate_block;
        RandomNumberBlock random_number_block;
        GameCardKeyBlock game_card_key_block;
        GameCardCertificateBlock game_card_certificate_block;
        Rsa2048ETicketKeyBlock eticket_device_key_block;
        Rsa2048ETicketCertificateBlock eticket_certificate_block;
        BatteryLotBlock battery_lot_block;
        SpeakerParameterBlock speaker_parameter_block;
        RegionCodeBlock region_code_block;
        AmiiboKeyBlock ecqv_ecdsa_amiibo_key_block;
        AmiiboEcqvCertificateBlock amiibo_ecqv_certificate_block;
        AmiiboEcdsaCertificateBlock amiibo_ecdsa_certificate_block;
        AmiiboEcqvBlsKeyBlock amiibo_ecqv_bls_key_block;
        AmiiboEcqvBlsCertificateBlock amiibo_ecqv_bls_certificate_block;
        AmiiboEcqvBlsRootCertificateBlock amiibo_ecqv_bls_root_certificate_block;
        ProductModelBlock product_model_block;
        HomeMenuSchemeMainColorVariationBlock home_menu_scheme_main_color_variation_block;
        BacklightBrightnessCoefficientsBlock backlight_brightness_coefficients_block;
        ExtendedEccB233DeviceKeyBlock extended_ecc_b233_device_key_block;
        ExtendedEccP256ETicketKeyBlock extended_ecc_p256_eticket_key_block;
        ExtendedEccB233ETicketKeyBlock extended_ecc_b233_eticket_key_block;
        ExtendedRsa2048ETicketKeyBlock extended_rsa_2048_eticket_key_block;
        ExtendedSslKeyBlock extended_ssl_key_block;
        ExtendedGameCardKeyBlock extended_game_card_key_block;
        LcdVendorIdBlock lcd_vendor_id_block;
        Rsa2048DeviceKeyBlock eci_device_key_2_block;
        Rsa2048DeviceCertificateBlock eci_device_certificate_2_block;
        UsbTypeCPowerSourceCircuitVersionBlock usb_type_c_power_source_circuit_version_block;
        HomeMenuSchemeSubColorBlock home_menu_scheme_sub_color_block;
        HomeMenuSchemeBezelColorBlock home_menu_scheme_bezel_color_block;
        HomeMenuSchemeMainColor1Block home_menu_scheme_main_color_1_block;
        HomeMenuSchemeMainColor2Block home_menu_scheme_main_color_2_block;
        HomeMenuSchemeMainColor3Block home_menu_scheme_main_color_3_block;
        AnalogStickModuleTypeLBlock analog_stick_module_type_l_block;
        AnalogStickModelParameterLBlock analog_stick_model_parameter_l_block;
        AnalogStickFactoryCalibrationLBlock analog_stick_factory_calibration_l_block;
        AnalogStickModuleTypeRBlock analog_stick_module_type_r_block;
        AnalogStickModelParameterRBlock analog_stick_model_parameter_r_block;
        AnalogStickFactoryCalibrationRBlock analog_stick_factory_calibration_r_block;
        ConsoleSixAxisSensorModuleTypeBlock console_six_axis_sensor_module_type_block;
        ConsoleSixAxisSensorHorizontalOffsetBlock console_six_axis_sensor_horizontal_offset_block;
        BatteryVersionBlock battery_version_block;
        u8 reserved_42E0[16];
        HomeMenuSchemeModelBlock home_menu_scheme_model_block;
        ConsoleSixAxisSensorMountTypeBlock console_six_axis_sensor_mount_type_block;
        u8 reserved_4310[15532];
    };
    static_assert(offsetof(CalibrationInfoBody, reserved_20)   == 0x20);
    static_assert(offsetof(CalibrationInfoBody, reserved_1D8)  == 0x1D8);
    static_assert(offsetof(CalibrationInfoBody, reserved_1E8)  == 0x1E8);
    static_assert(offsetof(CalibrationInfoBody, reserved_42E0) == 0x42E0);
    static_assert(offsetof(CalibrationInfoBody, reserved_4310) == 0x4310);
    static_assert(sizeof(CalibrationInfoBody) == CalibrationInfoBodySizeMax);

    struct CalibrationInfo {
        CalibrationInfoHeader header;
        CalibrationInfoBody body;
    };
    static_assert(sizeof(CalibrationInfo) == CalibrationBinarySize);

    Result GetCalibBinAmiiboKey(settings::factory::AmiiboKey *out);
    Result GetCalibBinAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out);
    Result GetCalibBinAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out);
    Result GetCalibBinAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out);
    Result GetCalibBinAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out);
    Result GetCalibBinAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out);
    Result GetCalibBinAnalogStickModuleTypeL(u8 *out);
    Result GetCalibBinAnalogStickModelParameterL(settings::factory::AnalogStickModelParameter *out);
    Result GetCalibBinAnalogStickFactoryCalibrationL(settings::factory::AnalogStickFactoryCalibration *out);
    Result GetCalibBinAnalogStickModuleTypeR(u8 *out);
    Result GetCalibBinAnalogStickModelParameterR(settings::factory::AnalogStickModelParameter *out);
    Result GetCalibBinAnalogStickFactoryCalibrationR(settings::factory::AnalogStickFactoryCalibration *out);

}
