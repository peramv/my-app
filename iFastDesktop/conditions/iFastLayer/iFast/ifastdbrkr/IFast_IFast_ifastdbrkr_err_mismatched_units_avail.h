#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mismatched_units_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mismatched_units_avail() { }
		~CIFast_IFast_ifastdbrkr_err_mismatched_units_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISMATCHED_UNITS_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mismatched units avail.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mismatched units avail.")); }

        // Actions
	};
}



