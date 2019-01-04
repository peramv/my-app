#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settlement_rule_pending_trade_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settlement_rule_pending_trade_exists() { }
		~CIFast_IFast_ifastcbo_warn_settlement_rule_pending_trade_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLEMENT_RULE_PENDING_TRADE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pending trade exists.")); }

        // Actions
	};
}