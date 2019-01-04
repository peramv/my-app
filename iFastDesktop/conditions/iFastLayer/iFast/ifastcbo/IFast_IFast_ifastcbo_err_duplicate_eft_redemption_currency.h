#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_eft_redemption_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_eft_redemption_currency() { }
		~CIFast_IFast_ifastcbo_err_duplicate_eft_redemption_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_EFT_REDEMPTION_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("EFT Redemption with the same currency already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un rachat TEF dans la même monnaie existe déjà.")); }

        // Actions
	};
}



