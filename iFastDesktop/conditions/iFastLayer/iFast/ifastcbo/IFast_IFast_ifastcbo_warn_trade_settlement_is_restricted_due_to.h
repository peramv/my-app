#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_settlement_is_restricted_due_to : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_settlement_is_restricted_due_to() { }
		~CIFast_IFast_ifastcbo_warn_trade_settlement_is_restricted_due_to() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_SETTLEMENT_IS_RESTRICTED_DUE_TO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Settlement is Restricted due to %REASON%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Règlement de la transaction est limitée en raison %REASON%.")); }

        // Actions
	};
}



