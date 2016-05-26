// --------------------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft Corporation.  All rights reserved.
// --------------------------------------------------------------------------------------------------------------------

#ifndef _MISSIONRECORDSPEC_H_
#define _MISSIONRECORDSPEC_H_

// Boost:
#include <boost/filesystem.hpp>

// STL:
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace malmo
{
    //! Specifies the type of data that should be recorded from the mission.
    struct MissionRecordSpec
    {
        friend class MissionRecord;
        
    public:

        //! Constructs an empty mission record specification, saying that nothing should be recorded.
        MissionRecordSpec();

        //! Constructs a mission record with a target file (e.g. 'data.tgz').
        //! By default, nothing is recorded. Use the other functions to specify what channels should be recorded.
        //! WARNING: You cannot re-use the instance of MissionRecordSpec - make a new one per call to AgentHost.startMission.
        //! \param destination Filename to save to.
        MissionRecordSpec(std::string destination);
               
        //! Requests that video be recorded, at the specified quality.
        //! Ensure that the width of the video requested is divisible by 4, and the height of the video requested is divisible by 2.
        //! \param frames_per_second The number of frames to record per second
        //! \param bit_rate The bit rate to record at. e.g. 400000 for 400kbps.
        void recordMP4(int frames_per_second, int64_t bit_rate);

        //! Requests that observations be recorded.
        void recordObservations();

        //! Requests that rewards be recorded.
        void recordRewards();

        //! Requests that commands be recorded.
        void recordCommands();

        //! Gets the temporary directory for this mission record.
        //! \returns The temporary directory for the mission record.
        std::string getTemporaryDirectory();

    private:

        bool is_recording;
        bool is_recording_mp4;
        bool is_recording_observations;
        bool is_recording_rewards;
        bool is_recording_commands;
        int64_t mp4_bit_rate;
        int mp4_fps;
        std::string mp4_path;
        std::string observations_path;
        std::string rewards_path;
        std::string commands_path;
        std::string mission_init_path;
        boost::filesystem::path temp_dir;
        std::string destination;
    };
}

#endif