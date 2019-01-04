#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_illegal_redemption_code_for_acct_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_illegal_redemption_code_for_acct_tax_type() { }
		~CIFast_IFast_ifastcbo_err_illegal_redemption_code_for_acct_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ILLEGAL_REDEMPTION_CODE_FOR_ACCT_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Withdrawal Code illegal for the Account's tax type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de retrait illégal pour le type d'imposition du compte")); }

        // Actions
	};
}



