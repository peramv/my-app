#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_guar_adj : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_guar_adj() { }
		~CIFast_IFast_ifastcbo_warn_trade_guar_adj() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_GUAR_ADJ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%WarningTradeGuarAdj%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%WarningTradeGuarAdj%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%WarningTradeGuarAdj%")); }

        // Actions
	};
}



