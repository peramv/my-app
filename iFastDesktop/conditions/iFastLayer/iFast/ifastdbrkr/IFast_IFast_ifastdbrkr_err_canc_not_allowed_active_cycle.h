#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_canc_not_allowed_active_cycle : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_canc_not_allowed_active_cycle() { }
		~CIFast_IFast_ifastdbrkr_err_canc_not_allowed_active_cycle() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANC_NOT_ALLOWED_ACTIVE_CYCLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cancellation not allowed, Active Cycle.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Annulation non autorisée, cycle actif")); }

        // Actions
	};
}



