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
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data) - (info->header.version < EncryptedKeyFormatVersion ? EncryptionKeyGenerationSize : 0));
            std::memcpy(out->key, block.data, out->size); // fuck std::copy
            return ResultSuccess();
        }

        Result GetCalibInfoAmiiboEcqvCertificate(settings::factory::AmiiboEcqvCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.amiibo_ecqv_certificate_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data));
            std::memcpy(out->cert, block.data, out->size); // fuck std::copy
            return ResultSuccess();
        }

        Result GetCalibInfoAmiiboEcdsaCertificate(settings::factory::AmiiboEcdsaCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.amiibo_ecdsa_certificate_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data));
            std::memcpy(out->cert, block.data, out->size); // fuck std::copy
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
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data) - (info->header.version < EncryptedKeyFormatVersion ? EncryptionKeyGenerationSize : 0));
            std::memcpy(out->key, block.data, out->size); // fuck std::copy
            return ResultSuccess();
        }

        Result GetCalibInfoAmiiboEcqvBlsCertificate(settings::factory::AmiiboEcqvBlsCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.amiibo_ecqv_bls_certificate_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data));
            std::memcpy(out->cert, block.data, out->size); // fuck std::copy
            return ResultSuccess();
        }

        Result GetCalibInfoAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out) {
            /* Ensure output isn't null. */
            AMS_ASSERT(out != nullptr);

            /* Get the calibration info. */
            CalibrationInfo *info = nullptr;
            R_TRY(GetCalibrationInfo(std::addressof(info)));
            AMS_ASSERT(info != nullptr);

            /* Validate the block. */
            auto &block = info->body.amiibo_ecqv_bls_root_certificate_block;
            R_UNLESS(CRC_BLOCK_VALID(block), settings::factory::ResultCalibrationDataCrcError());
            
            /* Output the block. */
            out->size = static_cast<u32>(sizeof(block.data));
            std::memcpy(out->cert, block.data, out->size); // fuck std::copy
            return ResultSuccess();
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
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvBlsCertificate());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvBlsCertificate(out));
    }

    Result GetCalibBinAmiiboEcqvBlsRootCertificate(settings::factory::AmiiboEcqvBlsRootCertificate *out) {
        R_UNLESS(out != nullptr, settings::ResultNullAmiiboEcqvBlsRootCertificate());
        return ConvertFileSystemResult(GetCalibInfoAmiiboEcqvBlsRootCertificate(out));
    }

}
