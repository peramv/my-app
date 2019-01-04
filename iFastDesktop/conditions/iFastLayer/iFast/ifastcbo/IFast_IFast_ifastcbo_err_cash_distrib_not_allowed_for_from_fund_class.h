#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_distrib_not_allowed_for_from_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_distrib_not_allowed_for_from_fund_class() { }
		~CIFast_IFast_ifastcbo_err_cash_distrib_not_allowed_for_from_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_DISTRIB_NOT_ALLOWED_FOR_FROM_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash distributions not allowed for this fund/class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Distribution en argent non autorisée pour ce fonds/cette classe")); }

        // Actions
	};
}



