#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_erisa_prohibited_fund_cannot_be_traded_in_erisa_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_erisa_prohibited_fund_cannot_be_traded_in_erisa_account() { }
		~CIFast_IFast_ifastcbo_err_erisa_prohibited_fund_cannot_be_traded_in_erisa_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ERISA_PROHIBITED_FUND_CANNOT_BE_TRADED_IN_ERISA_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not eligible to trade in ERISA prohibited Fund/Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas admissible aux transactions dans un fonds/une classe interdite par L'ERISA.")); }

        // Actions
	};
}



