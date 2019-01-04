#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_available_to_current_acct_portfolio : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_available_to_current_acct_portfolio() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_available_to_current_acct_portfolio() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_AVAILABLE_TO_CURRENT_ACCT_PORTFOLIO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUNDNAME% %CLASS% is not a valid fund/class combination for the group to which this account belongs and for account current portfolio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La combinaison fonds/classe %FUNDNAME% %CLASS% est invalide pour le groupe duquel fait partie ce compte et pour le portefeuille actuel du compte.")); }

        // Actions
	};
}



