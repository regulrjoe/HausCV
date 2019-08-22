#ifndef FD_TIMERS_HPP
#define FD_TIMERS_HPP

#include <cstdint>
#include <ctime>

namespace hcv
{
	class FDTimers
	{
		//// Methods
		public:
			FDTimers(const FDTimers& i_FDTimers);

			FDTimers(const uint8_t& i_seconds_to_start_alarm = 10, 
					const uint8_t& i_seconds_to_stop_alarm = 10, 
					const uint8_t& i_seconds_to_stop_recording = 10);


			~FDTimers();

			void UpdateLastBodyTimers();

			void UpdateLastBodyLastDetectedTimer();
		
			bool IsTimeToStartAlarm();

			bool IsTimeToStopAlarm();

			bool IsTimeToStopRecording();

		//// Data
		public:
			time_t m_last_body_first_detected;
			
			time_t m_last_body_last_detected;

			uint8_t m_seconds_to_start_alarm;

			uint8_t m_seconds_to_stop_alarm;

			uint8_t m_seconds_to_stop_recording;
	};

} // namespace hcv

#endif // FD_TIMERS_HPP
