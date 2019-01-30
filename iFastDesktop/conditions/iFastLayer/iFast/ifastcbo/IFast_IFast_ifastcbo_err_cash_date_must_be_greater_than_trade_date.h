#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_date_must_be_greater_than_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_date_must_be_greater_than_trade_date() { }
		~CIFast_IFast_ifastcbo_err_cash_date_must_be_greater_than_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_DATE_MUST_BE_GREATER_THAN_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Overridden cash date should be greater than or equal to trade date.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Overridden cash date should be greater than or equal to trade date.")); }
		
        // Actions
	};
}



