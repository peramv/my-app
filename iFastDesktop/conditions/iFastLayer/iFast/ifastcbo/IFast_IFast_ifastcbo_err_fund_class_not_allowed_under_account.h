#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_allowed_under_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_allowed_under_account() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_allowed_under_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_ALLOWED_UNDER_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and class is not allowed to trade under the account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce fonds et cette classe ne sont pas autorisés pour les transactions dans ce compte.")); }

        // Actions
	};
}



