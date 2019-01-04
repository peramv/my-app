#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_neg_money_market_interest_not_applicable_for_this_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_neg_money_market_interest_not_applicable_for_this_fund() { }
		~CIFast_IFast_ifastcbo_err_neg_money_market_interest_not_applicable_for_this_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEG_MONEY_MARKET_INTEREST_NOT_APPLICABLE_FOR_THIS_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative money market interest not applicable for this fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Negative money market interest not applicable for this fund.")); }

        // Actions
	};
}



