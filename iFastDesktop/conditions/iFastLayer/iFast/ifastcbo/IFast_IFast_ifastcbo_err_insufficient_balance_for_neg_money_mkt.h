#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_insufficient_balance_for_neg_money_mkt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_insufficient_balance_for_neg_money_mkt() { }
		~CIFast_IFast_ifastcbo_err_insufficient_balance_for_neg_money_mkt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUFFICIENT_BALANCE_FOR_NEG_MONEY_MKT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient balance for negative money market interest.\nNegative Dividend Units: %UNITS% Balance Units: %ACCTUNITS% Deff: %DEFFDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Insufficient balance for negative money market interest.\nNegative Dividend Units: %UNITS% Balance Units: %ACCTUNITS% Deff: %DEFFDATE%")); }

        // Actions
	};
}



