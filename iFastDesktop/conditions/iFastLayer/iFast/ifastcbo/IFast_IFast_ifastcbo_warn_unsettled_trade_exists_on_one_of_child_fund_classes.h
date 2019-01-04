#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_unsettled_trade_exists_on_one_of_child_fund_classes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_unsettled_trade_exists_on_one_of_child_fund_classes() { }
		~CIFast_IFast_ifastcbo_warn_unsettled_trade_exists_on_one_of_child_fund_classes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UNSETTLED_TRADE_EXISTS_ON_ONE_OF_CHILD_FUND_CLASSES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An unsettled trade exists on one of the child fund classes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("An unsettled trade exists on one of the child fund classes.")); }

        // Actions
	};
}