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
#include "settings_calibration_binary_database.hpp"
#include "settings_crc16.hpp"

namespace ams::settings::impl {

    namespace {

        constexpr const char                      DefaultConfigurationId1[6] = {};
        constexpr settings::factory::SerialNumber DefaultSerialNumber        = {};
        constexpr settings::BatteryLot            DefaultBatteryLot          = {};
        constexpr s32                             DefaultProductModel        = 0;

        constexpr u32 EncryptedKeyFormatVersion = 9;
        constexpr size_t EncryptionKeyGenerationSize = 4;

        Result ConvertFileSystemResult(Result result) {
            R_TRY_CATCH(result) {
                R_CONVERT(fs::ResultDataCorrupted,       settings::factory::ResultCalibrationDataFileSystemCorrupted())
                R_CONVERT(fs::ResultPartitionNotFound,   settings::factory::ResultCalibrationDataFileSystemCorrupted())
            } R_END_TRY_CATCH;
            return ResultSuccess();
        }

        CalibrationInfo g_calibration_info;
        os::SdkMutex g_calibration_info_mutex;

        Result GetCalibrationInfo(CalibrationInfo **out) {
            static bool s_calibration_read = false;
            std::scoped_lock lk(g_calibration_info_mutex);

            /* Calibration data has already been read. */
            if (s_calibration_read) {
                *out = std::addressof(g_calibration_info);
                return ResultSuccess();
            }

            /* Open the calibration binary. */
            std::unique_ptr<fs::IStorage> storage;
            R_TRY(fs::OpenBisPartition(std::addressof(storage), fs::BisPartitionId::CalibrationBinary));

            /* Read the calibration binary. */
            R_TRY(storage->Read(0, std::addressof(g_calibration_info), CalibrationBinarySize));

            /* Mark the calibration binary as read. */
            s_calibration_read = true;
            return ResultSuccess();
        }

        #define CRC_BLOCK_DATA_SIZE(block) sizeof(block) - sizeof(block.crc)
        #define CRC_BLOCK_VALID(block) GetCrc16(std::addressof(block), CRC_BLOCK_DATA_SIZE(block)) == block.crc

        #define CALIB_INFO_BASIC_IMPL(_Name, _Type, _Block, _Field) \
            Result _Name(_Type *out) {                                                                \
                /* Ensure output isn't null. */                                                       \
                AMS_ASSERT(out != nullptr);                                                           \
                                                                                                      \
                /* Get the calibration info. */                                                       \
                CalibrationInfo *info = nullptr;                                                      \
                R_TRY(GetCalibrationInfo(std::addressof(info)));                                      \
                AMS_ASSERT(info != nullptr);                                                          \
                                                                                                      \
                /* Validate the block. */                                                             \
                auto &block = info->body._Block;                                                      \
                R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError()); \
                                                                                                      \
                /* Output the data. */                                                                \
                *out = block._Field;                                                                  \
                return ResultSuccess();                                                               \
            }

        #define CALIB_INFO_SIZED_IMPL(_Name, _Type, _Block, _Field, _OutField) \
            Result _Name(_Type *out) {                                                                \
                /* Ensure output isn't null. */                                                       \
                AMS_ASSERT(out != nullptr);                                                           \
                                                                                                      \
                /* Get the calibration info. */                                                       \
                CalibrationInfo *info = nullptr;                                                      \
                R_TRY(GetCalibrationInfo(std::addressof(info)));                                      \
                AMS_ASSERT(info != nullptr);                                                          \
                                                                                                      \
                /* Validate the block. */                                                             \
                auto &block = info->body._Block;                                                      \
                R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError()); \
                                                                                                      \
                /* Output the data. */                                                                \
                out->size = static_cast<u32>(sizeof(block._Field));                                   \
                std::memcpy(out->_OutField, block._Field, out->size);                                 \
                return ResultSuccess();                                                               \
            }

        CALIB_INFO_SIZED_IMPL(GetCalibInfoAmiiboEcqvCertificate,                      settings::factory::AmiiboEcqvCertificate,                amiibo_ecqv_certificate_block,                   data, cert)
        CALIB_INFO_SIZED_IMPL(GetCalibInfoAmiiboEcdsaCertificate,                     settings::factory::AmiiboEcdsaCertificate,               amiibo_ecdsa_certificate_block,                  data, cert)
        CALIB_INFO_SIZED_IMPL(GetCalibInfoAmiiboEcqvBlsCertificate,                   settings::factory::AmiiboEcqvBlsCertificate,             amiibo_ecqv_bls_certificate_block,               data, cert)
        CALIB_INFO_SIZED_IMPL(GetCalibInfoAmiiboEcqvBlsRootCertificate,               settings::factory::AmiiboEcqvBlsRootCertificate,         amiibo_ecqv_bls_root_certificate_block,          data, cert)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickModuleTypeL,                     u8,                                                      analog_stick_module_type_l_block,                module_type)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickModelParameterL,                 settings::factory::AnalogStickModelParameter,            analog_stick_model_parameter_l_block,            model_parameter)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickFactoryCalibrationL,             settings::factory::AnalogStickFactoryCalibration,        analog_stick_factory_calibration_l_block,        calibration)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickModuleTypeR,                     u8,                                                      analog_stick_module_type_r_block,                module_type)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickModelParameterR,                 settings::factory::AnalogStickModelParameter,            analog_stick_model_parameter_r_block,            model_parameter)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAnalogStickFactoryCalibrationR,             settings::factory::AnalogStickFactoryCalibration,        analog_stick_factory_calibration_r_block,        calibration)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoBluetoothBdAddress,                         settings::factory::BdAddress,                            bd_address_block,                                bd_address)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoConfigurationId1,                           settings::factory::ConfigurationId1,                     configuration_id_1_block,                        id)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAccelerometerOffset,                        settings::factory::AccelerometerOffset,                  accelerometer_offset_block,                      accelerometer_offset)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoAccelerometerScale,                         settings::factory::AccelerometerScale,                   accelerometer_scale_block,                       accelerometer_scale)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoGyroscopeOffset,                            settings::factory::GyroscopeOffset,                      gyroscope_offset_block,                          gyroscope_offset)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoGyroscopeScale,                             settings::factory::GyroscopeScale,                       gyroscope_scale_block,                           gyroscope_scale)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoConsoleSixAxisSensorModuleType,             u8,                                                      console_six_axis_sensor_module_type_block,       module_type)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoConsoleSixAxisSensorMountType,              u8,                                                      console_six_axis_sensor_mount_type_block,        mount_type)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoConsoleSixAxisSensorHorizontalOffset,       settings::factory::ConsoleSixAxisSensorHorizontalOffset, console_six_axis_sensor_horizontal_offset_block, offset)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoSerialNumber,                               settings::factory::SerialNumber,                         serial_number_block,                             serial_number)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoWirelessLanMacAddress,                      settings::factory::MacAddress,                           wireless_lan_mac_address_block,                  mac_address)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoWirelessLanCountryCodeCount,                s32,                                                     wireless_lan_country_codes_block,                count)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoBatteryLot,                                 settings::BatteryLot,                                    battery_lot_block,                               battery_lot)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoBatteryVersion,                             u8,                                                      battery_version_block,                           version)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoSpeakerParameter,                           settings::factory::SpeakerParameter,                     speaker_parameter_block,                         speaker_parameter)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoEccB233DeviceCertificate,                   settings::factory::EccB233DeviceCertificate,             ecc_b233_device_certificate_block,               certificate)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoRsa2048DeviceCertificate,                   settings::factory::Rsa2048DeviceCertificate,             rsa_2048_device_certificate_block,               certificate)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoRsa2048ETicketCertificate,                  settings::factory::Rsa2048DeviceCertificate,             rsa_2048_eticket_certificate_block,              certificate)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoProductModel,                               s32,                                                     product_model_block,                             model)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeMainColorVariation,           s32,                                                     home_menu_scheme_main_color_variation_block,     color_variation)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeSubColor,                     util::Unorm8x4,                                          home_menu_scheme_sub_color_block,                color)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeBezelColor,                   util::Unorm8x4,                                          home_menu_scheme_bezel_color_block,              color)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeMainColor1,                   util::Unorm8x4,                                          home_menu_scheme_main_color_1_block,             color)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeMainColor2,                   util::Unorm8x4,                                          home_menu_scheme_main_color_2_block,             color)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeMainColor3,                   util::Unorm8x4,                                          home_menu_scheme_main_color_3_block,             color)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoHomeMenuSchemeModel,                        u32,                                                     home_menu_scheme_model_block,                    model)
        CALIB_INFO_SIZED_IMPL(GetCalibInfoRsa2048DeviceKey,                           settings::factory::Rsa2048DeviceKey,                     rsa_2048_device_key_block,                       data, data)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoBacklightBrightnessCoefficients,            util::Float3,                                            backlight_brightness_coefficients_block,         coefficients)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoLcdVendorId,                                u32,                                                     lcd_vendor_id_block,                             vendor_id)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoUsbTypeCPowerSourceCircuitVersion,          u8,                                                      usb_type_c_power_source_circuit_version_block,   version)
        CALIB_INFO_BASIC_IMPL(GetCalibInfoRegionCode,                                 settings::factory::RegionCode,                           region_code_block,                               region_code)

        Result GetCalibInfoAmiiboKey(settings::factory::AmiiboKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.ecqv_ecdsa_amiibo_key_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            out->size = static_cast<u32>(sizeof(block.data) - (info->header.version < EncryptedKeyFormatVersion ? EncryptionKeyGenerationSize : 0));
            std::memcpy(out->data, block.data, out->size);
            return ResultSuccess();
        }

        Result GetCalibInfoAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.amiibo_ecqv_bls_key_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            out->size = static_cast<u32>(sizeof(block.data) - (info->header.version < EncryptedKeyFormatVersion ? EncryptionKeyGenerationSize : 0));
            std::memcpy(out->data, block.data, out->size);
            return ResultSuccess();
        }

        Result GetCalibInfoWirelessLanCountryCodes(s32 *out_count, settings::factory::CountryCode * const out, size_t num_codes) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.wireless_lan_country_codes_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            const s32 count = static_cast<u32>(std::min<size_t>(block.count, num_codes));
            *out_count = count;
            std::memcpy(out, block.country_codes, count * sizeof(settings::factory::CountryCode));
            return ResultSuccess();
        }

        template <typename T>
        Result GetCalibInfoSslKey(settings::factory::SslKey *out, const T &block) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Validate the block. */
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            const auto size = static_cast<u32>(sizeof(block.data));
            out->size = size;
            std::memcpy(out->data, block.data, size);
            return ResultSuccess();
        }

        Result GetCalibInfoSslKey(settings::factory::SslKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            const CalibrationInfoBody &body = info->body;
            /* Attempt to use the extended block. */
            if (R_SUCCEEDED(GetCalibInfoSslKey(out, body.extended_ssl_key_block))) {
                const CalibrationInfoHeader &header = info->header;

                /* Clear key generation if unused. */
                if (header.version < EncryptedKeyFormatVersion) {
                    const auto size = EncryptionKeyGenerationSize;
                    const auto ofs  = sizeof(out->data) - size;
                    std::memset(std::addressof(out->data[ofs]), 0, size);
                }
                return ResultSuccess();
            } else {
                /* Fallback on the standard block. */
                return GetCalibInfoSslKey(out, body.ssl_key_block);
            }
        }

        Result GetCalibInfoSslCertificate(settings::factory::SslCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the size block. */
            auto &size_block = info->body.ssl_certificate_size_block;
            auto &block = info->body.ssl_certificate_block;
            R_UNLESS(CRC_BLOCK_VALID(size_block), settings::factory::ResultCalibrationDataCrcError());

            const size_t size = std::min(size_block.size, sizeof(block.data));
            Sha256Hash hash = {};

            /* Validate the hash for the block. */
            crypto::Sha256Generator gen;
            gen.Initialize();
            gen.Update(block.data, size);
            gen.GetHash(hash.data, crypto::Sha256Generator::HashSize);
            R_UNLESS(std::memcmp(block.sha256_hash.data, hash.data, crypto::Sha256Generator::HashSize) == 0, settings::factory::ResultCalibrationDataShaError());

            /* Output the data. */
            out->size = size;
            std::memcpy(out->cert, block.data, size);
            std::memset(std::addressof(out->cert[size]), 0, sizeof(block.data) - size);
            return ResultSuccess();
        }

        template <typename T>
        Result GetCalibInfoGameCardKey(settings::factory::GameCardKey *out, const T &block) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Validate the block. */
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            const auto size = static_cast<u32>(sizeof(block.data));
            out->size = size;
            std::memcpy(out->data, block.data, size);
            return ResultSuccess();
        }

        Result GetCalibInfoGameCardKey(settings::factory::GameCardKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            const CalibrationInfoBody &body = info->body;
            /* Attempt to use the extended block. */
            if (R_SUCCEEDED(GetCalibInfoGameCardKey(out, body.extended_game_card_key_block))) {
                const CalibrationInfoHeader &header = info->header;

                /* Clear key generation if unused. */
                if (header.version < EncryptedKeyFormatVersion) {
                    const auto size = EncryptionKeyGenerationSize;
                    const auto ofs  = sizeof(out->data) - size;
                    std::memset(std::addressof(out->data[ofs]), 0, size);
                }
                return ResultSuccess();
            } else {
                /* Fallback on the standard block. */
                return GetCalibInfoGameCardKey(out, body.game_card_key_block);
            }
        }

        Result GetCalibInfoGameCardCertificate(settings::factory::GameCardCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            auto &block = info->body.game_card_certificate_block;
            Sha256Hash hash = {};

            /* Validate the hash for the block. */
            crypto::Sha256Generator gen;
            gen.Initialize();
            gen.Update(block.certificate.cert, sizeof(block.certificate));
            gen.GetHash(hash.data, crypto::Sha256Generator::HashSize);
            R_UNLESS(std::memcmp(block.sha256_hash.data, hash.data, crypto::Sha256Generator::HashSize) == 0, settings::factory::ResultCalibrationDataShaError());

            /* Output the data. */
            std::memcpy(out->cert, block.certificate.cert, sizeof(block.certificate));
            return ResultSuccess();
        }

        template <typename T>
        Result GetCalibInfoEccB233DeviceKey(settings::factory::EccB233DeviceKey *out, const T &block) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Validate the block. */
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            const auto size = static_cast<u32>(sizeof(block.data));
            out->size = size;
            std::memcpy(out->data, block.data, size);
            return ResultSuccess();
        }

        Result GetCalibInfoEccB233DeviceKey(settings::factory::EccB233DeviceKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            const CalibrationInfoBody &body = info->body;
            /* Attempt to use the extended block. */
            if (R_SUCCEEDED(GetCalibInfoEccB233DeviceKey(out, body.extended_ecc_b233_device_key_block))) {
                const CalibrationInfoHeader &header = info->header;

                /* Clear key generation if unused. */
                if (header.version < EncryptedKeyFormatVersion) {
                    const auto size = EncryptionKeyGenerationSize;
                    const auto ofs  = sizeof(out->data) - size;
                    std::memset(std::addressof(out->data[ofs]), 0, size);
                }
                return ResultSuccess();
            } else {
                /* Fallback on the standard block. */
                return GetCalibInfoEccB233DeviceKey(out, body.ecc_b233_device_key_block);
            }
        }

        template <typename T>
        Result GetCalibInfoRsa2048ETicketKey(settings::factory::Rsa2048DeviceKey *out, const T &block) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Validate the block. */
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());

            /* Output the data. */
            const auto size = static_cast<u32>(sizeof(block.data));
            out->size = size;
            std::memcpy(out->data, block.data, size);
            return ResultSuccess();
        }

        Result GetCalibInfoRsa2048ETicketKey(settings::factory::Rsa2048DeviceKey *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            const CalibrationInfoBody &body = info->body;
            /* Attempt to use the extended block. */
            if (R_SUCCEEDED(GetCalibInfoRsa2048ETicketKey(out, body.extended_rsa_2048_eticket_key_block))) {
                const CalibrationInfoHeader &header = info->header;

                /* Clear key generation if unused. */
                if (header.version < EncryptedKeyFormatVersion) {
                    const auto size = EncryptionKeyGenerationSize;
                    const auto ofs  = sizeof(out->data) - size;
                    std::memset(std::addressof(out->data[ofs]), 0, size);
                }
                return ResultSuccess();
            } else {
                /* Fallback on the standard block. */
                return GetCalibInfoRsa2048ETicketKey(out, body.rsa_2048_eticket_key_block);
            }
        }

    }

    Result GetCalibBinAmiiboKey(settings::factory::AmiiboKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboKey(out));
    }

    Result GetCalibBinAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvCertificate(out));
    }

    Result GetCalibBinAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcdsaCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcdsaCertificate(out));
    }

    Result GetCalibBinAmiiboEcqvBlsKey(settings::factory::AmiiboEcqvBlsKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvBlsKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvBlsKey(out));
    }

    Result GetCalibBinAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvBlsCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvBlsCertificate(out));
    }

    Result GetCalibBinAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvBlsRootCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvBlsRootCertificate(out));
    }

    Result GetCalibBinAnalogStickModuleTypeL(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickModuleTypeBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickModuleTypeL(out));
    }

    Result GetCalibBinAnalogStickModelParameterL(settings::factory::AnalogStickModelParameter *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickModelParameterBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickModelParameterL(out));
    }

    Result GetCalibBinAnalogStickFactoryCalibrationL(settings::factory::AnalogStickFactoryCalibration *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickFactoryCalibrationBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickFactoryCalibrationL(out));
    }

    Result GetCalibBinAnalogStickModuleTypeR(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickModuleTypeBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickModuleTypeR(out));
    }

    Result GetCalibBinAnalogStickModelParameterR(settings::factory::AnalogStickModelParameter *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickModelParameterBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickModelParameterR(out));
    }

    Result GetCalibBinAnalogStickFactoryCalibrationR(settings::factory::AnalogStickFactoryCalibration *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAnalogStickFactoryCalibrationBuffer());
        return ConvertFileSystemResult(GetCalibInfoAnalogStickFactoryCalibrationR(out));
    }

    Result GetCalibBinBluetoothBdAddress(settings::factory::BdAddress *out) {
        return ConvertFileSystemResult(GetCalibInfoBluetoothBdAddress(out));
    }

    Result GetCalibBinConfigurationId1(settings::factory::ConfigurationId1 *out) {
        if (R_FAILED(GetCalibInfoConfigurationId1(out))) {
            std::strcpy(out->id, DefaultConfigurationId1); /* N uses strcpy, which only copies a single null byte. */
        }
        return ResultSuccess();
    }

    Result GetCalibBinAccelerometerOffset(settings::factory::AccelerometerOffset *out) {
        return ConvertFileSystemResult(GetCalibInfoAccelerometerOffset(out));
    }

    Result GetCalibBinAccelerometerScale(settings::factory::AccelerometerScale *out) {
        return ConvertFileSystemResult(GetCalibInfoAccelerometerScale(out));
    }

    Result GetCalibBinGyroscopeOffset(settings::factory::GyroscopeOffset *out) {
        return ConvertFileSystemResult(GetCalibInfoGyroscopeOffset(out));
    }

    Result GetCalibBinGyroscopeScale(settings::factory::GyroscopeScale *out) {
        return ConvertFileSystemResult(GetCalibInfoGyroscopeScale(out));
    }

    Result GetCalibBinConsoleSixAxisSensorModuleType(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullConsoleSixAxisSensorModuleTypeBuffer());
        return ConvertFileSystemResult(GetCalibInfoConsoleSixAxisSensorModuleType(out));
    }

    Result GetCalibBinConsoleSixAxisSensorMountType(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullConsoleSixAxisSensorMountTypeBuffer());
        return ConvertFileSystemResult(GetCalibInfoConsoleSixAxisSensorMountType(out));
    }

    Result GetCalibBinConsoleSixAxisSensorHorizontalOffset(settings::factory::ConsoleSixAxisSensorHorizontalOffset *out) {
        R_UNLESS(out != nullptr, settings::ResultNullConsoleSixAxisSensorHorizontalOffsetBuffer());
        return ConvertFileSystemResult(GetCalibInfoConsoleSixAxisSensorHorizontalOffset(out));
    }

    Result GetCalibBinSerialNumber(settings::factory::SerialNumber *out) {
        return ConvertFileSystemResult(GetCalibInfoSerialNumber(out));
    }

    Result GetCalibBinSerialNumberForSystemSettings(settings::system::SerialNumber *out) {
        R_UNLESS(out != nullptr, settings::ResultNullSerialNumberBuffer());
        settings::factory::SerialNumber serial_number = {};
        if (R_FAILED(GetCalibInfoSerialNumber(std::addressof(serial_number)))) {
            serial_number = DefaultSerialNumber;
        }
        util::Strlcpy<char>(out->str, serial_number.str, sizeof(settings::system::SerialNumber));
        return ResultSuccess();
    }

    Result GetCalibBinWirelessLanMacAddress(settings::factory::MacAddress *out) {
        return ConvertFileSystemResult(GetCalibInfoWirelessLanMacAddress(out));
    }

    Result GetCalibBinWirelessLanCountryCodeCount(s32 *out) {
        return ConvertFileSystemResult(GetCalibInfoWirelessLanCountryCodeCount(out));
    }

    Result GetCalibBinWirelessLanCountryCodes(s32 *out_count, settings::factory::CountryCode * const out, size_t num_codes) {
        return ConvertFileSystemResult(GetCalibInfoWirelessLanCountryCodes(out_count, out, num_codes));
    }

    Result GetCalibBinBatteryLot(settings::BatteryLot *out) {
        R_UNLESS(out != nullptr, settings::ResultNullBatteryLotBuffer());
        return ConvertFileSystemResult(GetCalibInfoBatteryLot(out));
    }

    Result GetCalibBinBatteryLotForSystemSettings(settings::BatteryLot *out) {
        R_UNLESS(out != nullptr, settings::ResultNullBatteryLotBuffer());
        settings::BatteryLot battery_lot = {};
        if (R_FAILED(GetCalibInfoBatteryLot(std::addressof(battery_lot)))) {
            battery_lot = DefaultBatteryLot;
        }
        util::Strlcpy<u8>(out->value, battery_lot.value, sizeof(settings::BatteryLot));
        return ResultSuccess();
    }

    Result GetCalibBinBatteryVersion(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullBatteryVersionBuffer());
        return ConvertFileSystemResult(GetCalibInfoBatteryVersion(out));
    }

    Result GetCalibBinSpeakerParameter(settings::factory::SpeakerParameter *out) {
        R_UNLESS(out != nullptr, settings::ResultNullSpeakerParameterBuffer());
        return ConvertFileSystemResult(GetCalibInfoSpeakerParameter(out));
    }

    Result GetCalibBinEccB233DeviceCertificate(settings::factory::EccB233DeviceCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullDeviceCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoEccB233DeviceCertificate(out));
    }

    Result GetCalibBinRsa2048DeviceCertificate(settings::factory::Rsa2048DeviceCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullDeviceCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoRsa2048DeviceCertificate(out));
    }

    Result GetCalibBinRsa2048ETicketCertificate(settings::factory::Rsa2048DeviceCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullETicketCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoRsa2048ETicketCertificate(out));
    }

    Result GetCalibBinProductModelForSystemSettings(s32 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullProductModelBuffer());
        if (R_FAILED(GetCalibInfoProductModel(out))) {
            *out = DefaultProductModel;
        }
        return ResultSuccess();
    }

    Result GetCalibBinHomeMenuSchemeMainColorVariation(s32 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeMainColorVariationBuffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeMainColorVariation(out));
    }

    Result GetCalibBinHomeMenuSchemeSubColor(util::Unorm8x4 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeSubColorBuffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeSubColor(out));
    }

    Result GetCalibBinHomeMenuSchemeBezelColor(util::Unorm8x4 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeBezelColorBuffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeBezelColor(out));
    }

    Result GetCalibBinHomeMenuSchemeMainColor1(util::Unorm8x4 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeMainColor1Buffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeMainColor1(out));
    }

    Result GetCalibBinHomeMenuSchemeMainColor2(util::Unorm8x4 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeMainColor2Buffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeMainColor2(out));
    }

    Result GetCalibBinHomeMenuSchemeMainColor3(util::Unorm8x4 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeMainColor3Buffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeMainColor3(out));
    }

    Result GetCalibBinHomeMenuSchemeModel(u32 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullHomeMenuSchemeModelBuffer());
        return ConvertFileSystemResult(GetCalibInfoHomeMenuSchemeModel(out));
    }

    Result GetCalibBinSslKey(settings::factory::SslKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullSslKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoSslKey(out));
    }

    Result GetCalibBinSslCertificate(settings::factory::SslCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullSslCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoSslCertificate(out));
    }

    Result GetCalibBinGameCardKey(settings::factory::GameCardKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullGameCardKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoGameCardKey(out));
    }

    Result GetCalibBinGameCardCertificate(settings::factory::GameCardCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullGameCardCertificateBuffer());
        return ConvertFileSystemResult(GetCalibInfoGameCardCertificate(out));
    }

    Result GetCalibBinEccB233DeviceKey(settings::factory::EccB233DeviceKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullDeviceKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoEccB233DeviceKey(out));
    }

    Result GetCalibBinRsa2048DeviceKey(settings::factory::Rsa2048DeviceKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullDeviceKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoRsa2048DeviceKey(out));
    }

    Result GetCalibBinRsa2048ETicketKey(settings::factory::Rsa2048DeviceKey *out) {
        R_UNLESS(out != nullptr, settings::ResultNullETicketKeyBuffer());
        return ConvertFileSystemResult(GetCalibInfoRsa2048ETicketKey(out));
    }

    Result GetCalibBinBacklightBrightnessCoefficientsForInternal(util::Float3 *out) {
        AMS_ASSERT(out != nullptr);
        return ConvertFileSystemResult(GetCalibInfoBacklightBrightnessCoefficients(out));
    }

    Result GetCalibBinLcdVendorId(u32 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullLcdVendorIdBuffer());
        return ConvertFileSystemResult(GetCalibInfoLcdVendorId(out));
    }

    Result GetCalibBinUsbTypeCPowerSourceCircuitVersion(u8 *out) {
        R_UNLESS(out != nullptr, settings::ResultNullUsbTypeCPowerSourceCircuitVersionBuffer());
        return ConvertFileSystemResult(GetCalibInfoUsbTypeCPowerSourceCircuitVersion(out));
    }

    Result GetCalibBinRegionCode(settings::factory::RegionCode *out) {
        R_UNLESS(out != nullptr, settings::ResultNullRegionCodeBuffer());
        return ConvertFileSystemResult(GetCalibInfoRegionCode(out));
    }

}
