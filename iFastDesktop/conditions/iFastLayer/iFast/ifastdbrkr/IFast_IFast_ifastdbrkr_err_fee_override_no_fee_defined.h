#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fee_override_no_fee_defined : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fee_override_no_fee_defined() { }
		~CIFast_IFast_ifastdbrkr_err_fee_override_no_fee_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_OVERRIDE_NO_FEE_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Override - No Fee Defined.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision außer Kraft – Keine Provision definiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Reemplazo de omisión predeterminada. No se ha definido una comisión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Exemption de frais – aucuns frais définis")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervanging kosten - Er zijn geen kosten gedefinieerd")); }

        // Actions
	};
}



