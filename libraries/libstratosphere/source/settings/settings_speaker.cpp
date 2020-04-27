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
#include "impl/settings_speaker_impl.hpp"

namespace ams::settings::factory {

    Result GetSpeakerParameter(SpeakerParameter *out) {
        /* Non calibration data errors represent fundamental system failure. */
        R_TRY_CATCH(settings::impl::GetSpeakerParameter(out)) {
            R_CATCH_RETHROW(settings::factory::ResultCalibrationDataFileSystemCorrupted)
            R_CATCH_RETHROW(settings::factory::ResultCalibrationDataCrcError)
        } R_END_TRY_CATCH_WITH_ABORT_UNLESS;
        return ResultSuccess();
    }
}
