#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cash_dividend_paid_after : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cash_dividend_paid_after() { }
		~CIFast_IFast_ifastcbo_warn_cash_dividend_paid_after() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CASH_DIVIDEND_PAID_AFTER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A CASH distribution has been paid after. A manual adjustment will be required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("A CASH distribution has been paid after. A manual adjustment will be required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une distribution COMPTANT a été payée après. Un ajustement manuel sera requis.")); }

        // Actions
	};
}



