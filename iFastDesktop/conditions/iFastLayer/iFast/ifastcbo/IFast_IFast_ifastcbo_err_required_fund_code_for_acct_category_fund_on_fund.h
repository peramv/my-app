#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_required_fund_code_for_acct_category_fund_on_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_required_fund_code_for_acct_category_fund_on_fund() { }
		~CIFast_IFast_ifastcbo_err_required_fund_code_for_acct_category_fund_on_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REQUIRED_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund code is required for Fund on Fund Category")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fonds est requis pour la catégorie de fonds sur fonds.")); }

        // Actions
	};
}



