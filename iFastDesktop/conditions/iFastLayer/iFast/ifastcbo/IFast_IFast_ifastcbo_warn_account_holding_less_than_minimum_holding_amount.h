#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_holding_less_than_minimum_holding_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_holding_less_than_minimum_holding_amount() { }
		~CIFast_IFast_ifastcbo_warn_account_holding_less_than_minimum_holding_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_HOLDING_LESS_THAN_MINIMUM_HOLDING_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account holding is less than Minimum Holding Amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Account holding is less than Minimum Holding Amount.")); }

        // Actions
	};
}



