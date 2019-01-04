#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_code_is_applicable_for_sibling_only_accounts : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_code_is_applicable_for_sibling_only_accounts() { }
		~CIFast_IFast_ifastcbo_err_deposit_code_is_applicable_for_sibling_only_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_CODE_IS_APPLICABLE_FOR_SIBLING_ONLY_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%CODE_TYPE% is applicable for Sibling Only accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de code %CODE_TYPE% est applicable aux comptes Frère/sœur seulement.")); }

        // Actions
	};
}



