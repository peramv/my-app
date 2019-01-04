#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_eft_red_currency_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_eft_red_currency_missing() { }
		~CIFast_IFast_ifastcbo_warn_eft_red_currency_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EFT_RED_CURRENCY_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EFT Redemption bank instructions for %cur% do not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions bancaires de rachat TEF pour %cur% sont inexistantes.")); }

        // Actions
	};
}



