#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_passed_fund_cutoff_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_passed_fund_cutoff_time() { }
		~CIFast_IFast_ifastcbo_warn_trade_passed_fund_cutoff_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_PASSED_FUND_CUTOFF_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade passed Fund Cut-Off Time")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a dépassé l'heure limite du fonds.")); }

        // Actions
	};
}



