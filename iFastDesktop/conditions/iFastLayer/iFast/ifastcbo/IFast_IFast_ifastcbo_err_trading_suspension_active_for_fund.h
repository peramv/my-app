#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trading_suspension_active_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trading_suspension_active_for_fund() { }
		~CIFast_IFast_ifastcbo_err_trading_suspension_active_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_SUSPENSION_ACTIVE_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading Suspension is active for fund %FUND_CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trading Suspension is active for fund %FUND_CODE%.")); }

        // Actions
	};
}



