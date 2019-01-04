#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_include_pending_trades_for_online_rebalalancing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_include_pending_trades_for_online_rebalalancing() { }
		~CIFast_IFast_ifastcbo_err_cannot_include_pending_trades_for_online_rebalalancing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_INCLUDE_PENDING_TRADES_FOR_ONLINE_REBALALANCING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For Online rebalancing, Pending Trades can be included in Report mode only.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("For Online rebalancing, Pending Trades can be included in Report mode only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour le rebalancement en ligne, les transactions en suspens ne peuvent être comprise qu'en mode rapport.")); }

        // Actions
	};
}



