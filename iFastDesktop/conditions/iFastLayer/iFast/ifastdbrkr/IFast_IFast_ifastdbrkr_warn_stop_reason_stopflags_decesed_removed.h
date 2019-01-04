#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_decesed_removed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_decesed_removed() { }
		~CIFast_IFast_ifastdbrkr_warn_stop_reason_stopflags_decesed_removed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOP_REASON_STOPFLAGS_DECESED_REMOVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account stop flags and stop reason Deceased (System) are removed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les signaux d'arrêt du compte et la raison d'arrêt Décédé (système) ont été retirés.")); }

        // Actions
	};
}



