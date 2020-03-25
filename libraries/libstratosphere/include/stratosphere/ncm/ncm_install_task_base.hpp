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
#include <stratosphere/ncm/ncm_install_task_data.hpp>
#include <stratosphere/ncm/ncm_install_task_occupied_size.hpp>

namespace ams::ncm {

    enum class ListContentMetaKeyFilter : u8 {
        All          = 0,
        Committed    = 1,
        NotCommitted = 2,
    };

    enum InstallConfig {
        InstallConfig_None                   = (0 << 0),
        InstallConfig_SystemUpdate           = (1 << 2),
        InstallConfig_RequiresExFatDriver    = (1 << 3),
        InstallConfig_IgnoreTicket           = (1 << 4),
    };

    struct InstallThroughput {
        s64 installed;
        TimeSpan elapsed_time;
    };

    struct InstallContentMetaInfo {
        ContentId content_id;
        s64 content_size;
        ContentMetaKey key;
        bool verify_digest;
        bool has_key;
        Digest digest;

        static constexpr InstallContentMetaInfo MakeVerifiable(const ContentId &cid, s64 sz, const ContentMetaKey &ky, const Digest &d) {
            return {
                .content_id    = cid,
                .content_size  = sz,
                .key           = ky,
                .verify_digest = true,
                .has_key       = true,
                .digest        = d,
            };
        }

        static constexpr InstallContentMetaInfo MakeUnverifiable(const ContentId &cid, s64 sz, const ContentMetaKey &ky) {
            return {
                .content_id    = cid,
                .content_size  = sz,
                .key           = ky,
                .verify_digest = false,
                .has_key       = true,
            };
        }

        static constexpr InstallContentMetaInfo MakeUnverifiable(const ContentId &cid, s64 sz) {
            return {
                .content_id    = cid,
                .content_size  = sz,
                .verify_digest = false,
                .has_key       = false,
            };
        }
    };

    static_assert(sizeof(InstallContentMetaInfo) == 0x50);

    class InstallTaskBase {
        private:
            crypto::Sha256Generator sha256_generator;
            StorageId install_storage;
            InstallTaskDataBase *data;
            InstallProgress progress;
            os::Mutex progress_mutex;
            u32 config;
            os::Mutex cancel_mutex;
            bool cancel_requested;
            InstallThroughput throughput;
            TimeSpan throughput_start_time;
            os::Mutex throughput_mutex;
            FirmwareVariationId firmware_variation_id;
        public:
            virtual ~InstallTaskBase() { /* ... */ };
        private:
            ALWAYS_INLINE Result SetLastResultOnFailure(Result result) {
                if (R_FAILED(result)) {
                    this->SetLastResult(result);
                }
                return result;
            }
        private:
            Result PrepareImpl();
            Result CleanupOne(const InstallContentMeta &content_meta);
            Result ExecuteImpl();
            Result CommitImpl(const StorageContentMetaKey *keys, s32 num_keys);
            InstallContentInfo MakeInstallContentInfoFrom(const InstallContentMetaInfo &info, const PlaceHolderId &placeholder_id, std::optional<bool> is_temporary);
            Result ReadContentMetaInfoList(s32 *out_count, std::unique_ptr<ContentMetaInfo[]> *out_meta_infos, const ContentMetaKey &key);
            Result ListRightsIdsByInstallContentMeta(s32 *out_count, Span<RightsId> out_span, const InstallContentMeta &content_meta, s32 offset);
        protected:
            Result Initialize(StorageId install_storage, InstallTaskDataBase *data, u32 config);
            Result CountInstallContentMetaData(s32 *out_count);
            Result GetInstallContentMetaData(InstallContentMeta *out_content_meta, s32 index);
            Result WritePlaceHolderBuffer(InstallContentInfo *content_info, const void *data, size_t data_size);
            Result WriteContentMetaToPlaceHolder(InstallContentInfo *out_install_content_info, ContentStorage *storage, const InstallContentMetaInfo &meta_info, std::optional<bool> is_temporary);
            Result PrepareContentMeta(const InstallContentMetaInfo &meta_info, std::optional<ContentMetaKey> key, std::optional<u32> source_version);
            Result GetInstallContentMetaDataFromPath(AutoBuffer *out, const Path &path, const InstallContentInfo &content_info, std::optional<u32> source_version);
            Result PrepareContentMeta(ContentId content_id, s64 size, ContentMetaType meta_type, AutoBuffer *buffer);
            void PrepareAgain();
            Result PrepareSystemUpdateDependency();
            Result PrepareContentMetaIfLatest(const ContentMetaKey &key);
            Result GetSystemUpdateTaskApplyInfo(SystemUpdateTaskApplyInfo *out);
            Result DeleteInstallContentMetaData(const ContentMetaKey *keys, s32 num_keys);
            Result CanContinue();
        public:
            bool IsCancelRequested();
            Result Prepare();
            void SetLastResult(Result last_result);
            Result GetPreparedPlaceHolderPath(Path *out_path, u64 id, ContentMetaType meta_type, ContentType type);
            Result CalculateRequiredSize(size_t *out_size);
            void ResetThroughputMeasurement();
            void SetProgressState(InstallProgressState state);
            void IncrementProgress(s64 size);
            void UpdateThroughputMeasurement(s64 throughput);
            bool IsNecessaryInstallTicket(const fs::RightsId &rights_id);
            void SetTotalSize(s64 size);
            Result PreparePlaceHolder();
            Result Cleanup();
            void CleanupProgress();
            Result ListContentMetaKey(s32 *out_keys_written, StorageContentMetaKey *out_keys, s32 out_keys_count, s32 offset, ListContentMetaKeyFilter filter);
            Result ListApplicationContentMetaKey(s32 *out_keys_written, ApplicationContentMetaKey *out_keys, s32 out_keys_count, s32 offset);
            Result Execute();
            void StartThroughputMeasurement(); 
            Result WritePlaceHolder(const ContentMetaKey &key, InstallContentInfo *content_info);
            Result PrepareAndExecute();
            Result VerifyAllNotCommitted(const StorageContentMetaKey *keys, s32 num_keys);
            Result Commit(const StorageContentMetaKey *keys, s32 num_keys);
            Result IncludesExFatDriver(bool *out);
            Result IsNewerThanInstalled(bool *out, const ContentMetaKey &key);
            void ResetLastResult();
            s64 GetThroughput();
            Result CalculateContentsSize(s64 *out_size, const ContentMetaKey &key, StorageId storage_id);
            Result FindMaxRequiredApplicationVersion(u32 *out);
            Result FindMaxRequiredSystemVersion(u32 *out);
            Result ListOccupiedSize(s32 *out_written, InstallTaskOccupiedSize *out_list, s32 out_list_size, s32 offset);
            void SetFirmwareVariationId(FirmwareVariationId id);
            Result ListRightsIds(s32 *out_count, Span<RightsId> out_span, const ContentMetaKey &key, s32 offset);
        protected:
            virtual Result OnPrepareComplete();
            virtual Result PrepareDependency();
        public:
            virtual void Cancel();
            virtual void ResetCancel();
            virtual InstallProgress GetProgress();
            virtual Result PrepareInstallContentMetaData() = 0;
            virtual Result GetInstallContentMetaInfo(InstallContentMetaInfo *out_info, const ContentMetaKey &key);
            virtual Result GetLatestVersion(std::optional<u32> *out_version, u64 id);
            virtual Result CheckInstallable();
            virtual Result OnExecuteComplete();
            virtual Result OnWritePlaceHolder(const ContentMetaKey &key, InstallContentInfo *content_info) = 0;
            virtual Result InstallTicket(const fs::RightsId &rights_id, ContentMetaType meta_type) = 0;
    };

}