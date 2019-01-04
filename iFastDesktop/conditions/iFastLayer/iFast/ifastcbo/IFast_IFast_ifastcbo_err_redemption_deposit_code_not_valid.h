#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_deposit_code_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_deposit_code_not_valid() { }
		~CIFast_IFast_ifastcbo_err_redemption_deposit_code_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_DEPOSIT_CODE_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Combination of  Deposit Code %DEP_CODE% Redemption Code %RED_CODE%  is Not Valid .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison code de dépôt %DEP_CODE% et code de rachat %RED_CODE% non valide.")); }

        // Actions
	};
}



