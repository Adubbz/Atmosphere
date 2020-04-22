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
        using TypeSizeStruct = struct { _Decl; };                           \
        _Decl;                                                              \
        static_assert(_BlockSize >= sizeof(TypeSizeStruct) + sizeof(u16));  \
        u8 pad[_BlockSize - sizeof(TypeSizeStruct) - sizeof(u16)];          \
        u16 crc;                                                            \
    };                                                                      \
    static_assert(sizeof(_BlockTypeName) == _BlockSize);        
    
    #define DEFINE_CALIBRATION_SHA_BLOCK(_BlockTypeName, _Size, _TypeName, _MemberName) \
    struct _BlockTypeName {                                                             \
        _TypeName _MemberName;                                                          \
        static_assert(Size == sizeof(_TypeName) + sizeof(Sha256Hash));                  \
        Sha256Hash sha256_hash;                                                         \
    };                                                                                  \
    static_assert(sizeof(_BlockTypeName) == _Size);

    // ConfigurationId1Block configuration_id_1_block;
    // WirelessLanCountryCodesBlock wireless_lan_country_codes_block;
    // WirelessLanMacAddressBlock wireless_lan_mac_address_block;
    // BluetoothBdAddressBlock bd_address_block;
    // AccelerometerOffsetBlock accelerometer_offset_block;
    // AccelerometerScaleBlock accelerometer_scale_block;
    // GyroscopeOffsetBlock gyroscope_offset_block;
    // GyroscopeScaleBlock gyroscope_scale_block;
    // SerialNumberBlock serial_number_block;
    // EccP256DeviceKeyBlock ecc_p256_device_key_block;
    // EccP256DeviceCertificateBlock ecc_p256_device_certificate_block;
    // EccB233DeviceKeyBlock ecc_b233_device_key_block;
    // EccB233DeviceCertificateBlock ecc_b233_device_certificate_block;
    // EccP256ETicketKeyBlock ecc_p256_eticket_key_block;
    // EccP256ETicketCertificateBlock ecc_p256_eticket_certificate_block;
    // EccB233ETicketKeyBlock ecc_b233_eticket_key_block;
    // EccB233ETicketCertificateBlock ecc_b233_eticket_certificate_block;
    // SslKeyBlock ssl_key_block;
    // SslCertificateHeaderBlock ssl_certificate_header_block;
    // SslCertificateBlock ssl_certificate_block;
    // RandomNumberBlock random_number_block;
    // GameCardKeyBlock game_card_key_block;
    // GameCardCertificateBlock game_card_certificate_block;
    // Rsa2048ETicketKeyBlock eticket_device_key_block;
    // Rsa2048ETicketCertificateBlock eticket_certificate_block;
    // BatteryLotBlock battery_lot_block;
    // SpeakerParameterBlock speaker_parameter_block;
    // RegionCodeBlock region_code_block;
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboKeyBlock,                    0x60, u8 data[0x54])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvCertificateBlock,        0x20, u8 data[0x14])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcdsaCertificateBlock,       0x80, u8 data[0x70])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsKeyBlock,             0x50, u8 data[0x44])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsCertificateBlock,     0x30, u8 data[0x20])
    DEFINE_CALIBRATION_CRC_BLOCK(AmiiboEcqvBlsRootCertificateBlock, 0xA0, u8 data[0x90])
    // ProductModelBlock product_model_block;
    // HomeMenuSchemeMainColorVariationBlock home_menu_scheme_main_color_variation_block;
    // BacklightBrightnessCoefficientsBlock backlight_brightness_coefficients_block;
    // ExtendedEccB233DeviceKeyBlock extended_ecc_b233_device_key_block;
    // ExtendedEccP256ETicketKeyBlock extended_ecc_p256_eticket_key_block;
    // ExtendedEccB233ETicketKeyBlock extended_ecc_b233_eticket_key_block;
    // ExtendedRsa2048ETicketKeyBlock extended_rsa_2048_eticket_key_block;
    // ExtendedSslKeyBlock extended_ssl_key_block;
    // ExtendedGameCardKeyBlock extended_game_card_key_block;
    // LcdVendorIdBlock lcd_vendor_id_block;
    // Rsa2048DeviceKeyBlock eci_device_key_2_block;
    // Rsa2048DeviceCertificateBlock eci_device_certificate_2_block;
    // UsbTypeCPowerSourceCircuitVersionBlock usb_type_c_power_source_circuit_version_block;
    // HomeMenuSchemeSubColorBlock home_menu_scheme_sub_color_block;
    // HomeMenuSchemeBezelColorBlock home_menu_scheme_bezel_color_block;
    // HomeMenuSchemeMainColor1Block home_menu_scheme_main_color_1_block;
    // HomeMenuSchemeMainColor2Block home_menu_scheme_main_color_2_block;
    // HomeMenuSchemeMainColor3Block home_menu_scheme_main_color_3_block;
    // AnalogStickModuleTypeLBlock analog_stick_module_type_l_block;
    // AnalogStickModelParameterLBlock analog_stick_model_parameter_l_block;
    // AnalogStickFactoryCalibrationLBlock analog_stick_factory_calibration_l_block;
    // AnalogStickModuleTypeRBlock analog_stick_module_type_r_block;
    // AnalogStickModelParameterRBlock analog_stick_model_parameter_r_block;
    // AnalogStickFactoryCalibrationRBlock analog_stick_factory_calibration_r_block;
    // ConsoleSixAxisSensorModuleTypeBlock console_six_axis_sensor_module_type_block;
    // ConsoleSixAxisSensorHorizontalOffsetBlock console_six_axis_sensor_horizontal_offset_block;
    // BatteryVersionBlock battery_version_block;
    // HomeMenuSchemeModelBlock home_menu_scheme_model_block;
    // ConsoleSixAxisSensorMountTypeBlock console_six_axis_sensor_mount_type_block;

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
        // ConfigurationId1Block configuration_id_1_block;
        // u8 reserved_20[32];
        // WirelessLanCountryCodesBlock wireless_lan_country_codes_block;
        // WirelessLanMacAddressBlock wireless_lan_mac_address_block;
        // u8 reserved_1D8[8];
        // BluetoothBdAddressBlock bd_address_block;
        // u8 reserved_1E8[8];
        // AccelerometerOffsetBlock accelerometer_offset_block;
        // AccelerometerScaleBlock accelerometer_scale_block;
        // GyroscopeOffsetBlock gyroscope_offset_block;
        // GyroscopeScaleBlock gyroscope_scale_block;
        // SerialNumberBlock serial_number_block;
        // EccP256DeviceKeyBlock ecc_p256_device_key_block;
        // EccP256DeviceCertificateBlock ecc_p256_device_certificate_block;
        // EccB233DeviceKeyBlock ecc_b233_device_key_block;
        // EccB233DeviceCertificateBlock ecc_b233_device_certificate_block;
        // EccP256ETicketKeyBlock ecc_p256_eticket_key_block;
        // EccP256ETicketCertificateBlock ecc_p256_eticket_certificate_block;
        // EccB233ETicketKeyBlock ecc_b233_eticket_key_block;
        // EccB233ETicketCertificateBlock ecc_b233_eticket_certificate_block;
        // SslKeyBlock ssl_key_block;
        // SslCertificateHeaderBlock ssl_certificate_header_block;
        // SslCertificateBlock ssl_certificate_block;
        // RandomNumberBlock random_number_block;
        // GameCardKeyBlock game_card_key_block;
        // GameCardCertificateBlock game_card_certificate_block;
        // Rsa2048ETicketKeyBlock eticket_device_key_block;
        // Rsa2048ETicketCertificateBlock eticket_certificate_block;
        // BatteryLotBlock battery_lot_block;
        // SpeakerParameterBlock speaker_parameter_block;
        // RegionCodeBlock region_code_block;
        AmiiboKeyBlock ecqv_ecdsa_amiibo_key_block;
        AmiiboEcqvCertificateBlock amiibo_ecqv_certificate_block;
        AmiiboEcdsaCertificateBlock amiibo_ecdsa_certificate_block;
        AmiiboEcqvBlsKeyBlock amiibo_ecqv_bls_key_block;
        AmiiboEcqvBlsCertificateBlock amiibo_ecqv_bls_certificate_block;
        AmiiboEcqvBlsRootCertificateBlock amiibo_ecqv_bls_root_certificate_block;
        // ProductModelBlock product_model_block;
        // HomeMenuSchemeMainColorVariationBlock home_menu_scheme_main_color_variation_block;
        // BacklightBrightnessCoefficientsBlock backlight_brightness_coefficients_block;
        // ExtendedEccB233DeviceKeyBlock extended_ecc_b233_device_key_block;
        // ExtendedEccP256ETicketKeyBlock extended_ecc_p256_eticket_key_block;
        // ExtendedEccB233ETicketKeyBlock extended_ecc_b233_eticket_key_block;
        // ExtendedRsa2048ETicketKeyBlock extended_rsa_2048_eticket_key_block;
        // ExtendedSslKeyBlock extended_ssl_key_block;
        // ExtendedGameCardKeyBlock extended_game_card_key_block;
        // LcdVendorIdBlock lcd_vendor_id_block;
        // Rsa2048DeviceKeyBlock eci_device_key_2_block;
        // Rsa2048DeviceCertificateBlock eci_device_certificate_2_block;
        // UsbTypeCPowerSourceCircuitVersionBlock usb_type_c_power_source_circuit_version_block;
        // HomeMenuSchemeSubColorBlock home_menu_scheme_sub_color_block;
        // HomeMenuSchemeBezelColorBlock home_menu_scheme_bezel_color_block;
        // HomeMenuSchemeMainColor1Block home_menu_scheme_main_color_1_block;
        // HomeMenuSchemeMainColor2Block home_menu_scheme_main_color_2_block;
        // HomeMenuSchemeMainColor3Block home_menu_scheme_main_color_3_block;
        // AnalogStickModuleTypeLBlock analog_stick_module_type_l_block;
        // AnalogStickModelParameterLBlock analog_stick_model_parameter_l_block;
        // AnalogStickFactoryCalibrationLBlock analog_stick_factory_calibration_l_block;
        // AnalogStickModuleTypeRBlock analog_stick_module_type_r_block;
        // AnalogStickModelParameterRBlock analog_stick_model_parameter_r_block;
        // AnalogStickFactoryCalibrationRBlock analog_stick_factory_calibration_r_block;
        // ConsoleSixAxisSensorModuleTypeBlock console_six_axis_sensor_module_type_block;
        // ConsoleSixAxisSensorHorizontalOffsetBlock console_six_axis_sensor_horizontal_offset_block;
        // BatteryVersionBlock battery_version_block;
        // u8 reserved_42E0[16];
        // HomeMenuSchemeModelBlock home_menu_scheme_model_block;
        // ConsoleSixAxisSensorMountTypeBlock console_six_axis_sensor_mount_type_block;
        // u8 reserved_4310[15532];
    };
    /* TODO: static_assert(sizeof(CalibrationInfoBody) == CalibrationInfoBodySizeMax); */

    struct CalibrationInfo {
        CalibrationInfoHeader header;
        CalibrationInfoBody body;
    };
    /* TODO: static_assert(sizeof(CalibrationInfo) == CalibrationBinarySize); */

    Result GetCalibBinAmiiboKey(settings::factory::AmiiboKey *out);
    Result GetCalibBinAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out);
    Result GetCalibBinAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out);
    Result GetCalibBinAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out);
    Result GetCalibBinAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out);
    Result GetCalibBinAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out);

}
