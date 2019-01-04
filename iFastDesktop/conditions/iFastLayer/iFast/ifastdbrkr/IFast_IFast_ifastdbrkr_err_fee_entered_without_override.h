#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_entered_without_override : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_entered_without_override() { }
		~CIFast_IFast_ifastdbrkr_err_fee_entered_without_override() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_ENTERED_WITHOUT_OVERRIDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Entered Without An Override.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision ohne Außer-Kraft-Setzen eingegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo una comisión sin un Over-ride")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Frais saisis sans modification")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn kosten ingevoerd zonder vervanging")); }

        // Actions
	};
}



