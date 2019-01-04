#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_fund_not_puev_capable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_fund_not_puev_capable() { }
		~CIFast_IFast_ifastcbo_err_account_fund_not_puev_capable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_FUND_NOT_PUEV_CAPABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Both account and fund should be PUEV capable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Both account and fund should be PUEV capable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte et le fonds devraient tous deux supporter PUEV.")); }

        // Actions
	};
}



