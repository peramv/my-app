#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_switch_settle_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_switch_settle_failed() { }
		~CIFast_IFast_ifastdbrkr_err_switch_settle_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWITCH_SETTLE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("In side of the trade cannot settle prior to Out side.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La partie entrante de la transaction ne peut être réglée avant la partie sortante.")); }

        // Actions
	};
}



