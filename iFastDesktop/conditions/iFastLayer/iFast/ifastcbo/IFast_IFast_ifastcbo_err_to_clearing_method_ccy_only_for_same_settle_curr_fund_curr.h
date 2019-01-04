#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_clearing_method_ccy_only_for_same_settle_curr_fund_curr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_clearing_method_ccy_only_for_same_settle_curr_fund_curr() { }
		~CIFast_IFast_ifastcbo_err_to_clearing_method_ccy_only_for_same_settle_curr_fund_curr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("TO-Clearing Method requires requires Settle Currency and Fund Currency to be the same")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("TO-Clearing Method requires requires Settle Currency and Fund Currency to be the same")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de compensation cible requiert que la monnaie de règlement et la monnaie du compte soient identiques.")); }

        // Actions
	};
}



