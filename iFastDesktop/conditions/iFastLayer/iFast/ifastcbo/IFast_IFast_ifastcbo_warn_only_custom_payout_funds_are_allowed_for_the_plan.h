#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_only_custom_payout_funds_are_allowed_for_the_plan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_only_custom_payout_funds_are_allowed_for_the_plan() { }
		~CIFast_IFast_ifastcbo_warn_only_custom_payout_funds_are_allowed_for_the_plan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Custom Payout funds are allowed in the fund allocations of a Custom Payout SWP Plan.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Only Custom Payout funds are allowed in the fund allocations of a Custom Payout SWP Plan.")); }

        // Actions
	};
}