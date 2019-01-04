#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pending_trade_exist_on_parent_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pending_trade_exist_on_parent_fund_class() { }
		~CIFast_IFast_ifastcbo_warn_pending_trade_exist_on_parent_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PENDING_TRADE_EXIST_ON_PARENT_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A pending trade exists on the parent fund class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("A pending trade exists on the parent fund class.")); }

        // Actions
	};
}