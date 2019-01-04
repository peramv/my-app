#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_is_not_allowed_to_trade_in_fund_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_is_not_allowed_to_trade_in_fund_currency() { }
		~CIFast_IFast_ifastcbo_err_tax_type_is_not_allowed_to_trade_in_fund_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_IS_NOT_ALLOWED_TO_TRADE_IN_FUND_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type %TAXTYPE% is not allowed to trade in %FUNDCURRENCY% currency.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Tax Type %TAXTYPE% is not allowed to trade in %FUNDCURRENCY% currency.")); }

        // Actions
	};
}



