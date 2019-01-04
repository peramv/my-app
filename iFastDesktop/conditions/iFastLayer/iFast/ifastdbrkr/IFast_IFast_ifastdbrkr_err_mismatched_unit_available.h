#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mismatched_unit_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mismatched_unit_available() { }
		~CIFast_IFast_ifastdbrkr_err_mismatched_unit_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISMATCHED_UNIT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mismatched units available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mismatched units available.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Mismatched units available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des unités discordantes sont disponibles.")); }

        // Actions
	};
}



