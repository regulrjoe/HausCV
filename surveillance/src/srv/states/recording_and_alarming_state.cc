#include "srv/states.hpp"

#include "utils/macros.hpp"
#include "utils/rcode.hpp"

namespace hcv
{
	namespace srv
	{

		/////////////////////////////
		RecordingAndAlarmingState* RecordingAndAlarmingState::singleton = 0;

		/////////////////////////////
		ISRVState* RecordingAndAlarmingState::Instance()
		{
			if (singleton == 0)
				singleton = new RecordingAndAlarmingState();
			return singleton;
		}

		/////////////////////////////
		void RecordingAndAlarmingState::HandleMotion(SRVSystem* i_system)
		{
			try
			{
				i_system->GetTimer()->UpdateLastMotionTimestamp();
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}

		}

		/////////////////////////////
		void RecordingAndAlarmingState::HandleNoMotion(SRVSystem* i_system)
		{
			try
			{
				if (i_system->GetTimer()->IsTimeToStopRecording() && i_system->GetTimer()->IsTimeToStopAlarm())
				{
					stopRecording(i_system);
					stopAlarm(i_system);
					changeCurrentState(i_system, i_system->GetBaseState());
				}
				else if (i_system->GetTimer()->IsTimeToStopRecording())
				{
					stopRecording(i_system);
					changeCurrentState(i_system, AlarmingState::Instance());
				}
				else if (i_system->GetTimer()->IsTimeToStopAlarm())
				{
					stopAlarm(i_system);
					changeCurrentState(i_system, RecordingState::Instance());
				}
			}
			catch (const RCode& rc)
			{
				printERROR(RCMsg(rc));
				throw rc;
			}
			catch (const exception& e)
			{
				printERROR(e.what());
				throw e;
			}
		}

	} // namespace srv
} // namespace hcv