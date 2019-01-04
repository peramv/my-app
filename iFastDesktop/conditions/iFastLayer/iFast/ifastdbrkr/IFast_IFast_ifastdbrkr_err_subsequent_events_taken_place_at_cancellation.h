#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_subsequent_events_taken_place_at_cancellation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_subsequent_events_taken_place_at_cancellation() { }
		~CIFast_IFast_ifastdbrkr_err_subsequent_events_taken_place_at_cancellation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUBSEQUENT_EVENTS_TAKEN_PLACE_AT_CANCELLATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to complete transaction. Subsequent events for the Fund/Class must be cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de terminer la transaction. Les événements subséquents pour le fonds/la classe doivent être annulés.")); }

        // Actions
	};
}



