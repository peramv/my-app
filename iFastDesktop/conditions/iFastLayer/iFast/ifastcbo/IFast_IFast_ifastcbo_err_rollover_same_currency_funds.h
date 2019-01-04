#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rollover_same_currency_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rollover_same_currency_funds() { }
		~CIFast_IFast_ifastcbo_err_rollover_same_currency_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ROLLOVER_SAME_CURRENCY_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Funds should be in the same currency")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Funds should be in the same currency")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les fonds doivent être dans la même monnaie.")); }

        // Actions
	};
}



