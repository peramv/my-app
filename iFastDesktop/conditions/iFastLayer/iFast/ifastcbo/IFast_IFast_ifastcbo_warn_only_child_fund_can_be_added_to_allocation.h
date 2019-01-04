#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation() { }
		~CIFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only a global model child fund can be added to the allocation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Only a global model child fund can be added to the allocation.")); }

        // Actions
	};
}