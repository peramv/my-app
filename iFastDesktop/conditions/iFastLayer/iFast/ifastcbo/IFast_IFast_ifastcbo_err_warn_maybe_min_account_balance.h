#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_maybe_min_account_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_maybe_min_account_balance() { }
		~CIFast_IFast_ifastcbo_err_warn_maybe_min_account_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MAYBE_MIN_ACCOUNT_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account balance may be less than minimum:  %MINIMUM_BAL%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontostand für %FUND% und %CLASS%kann unter dem Minimum liegen:  %MINIMUM_BAL%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo de la cuenta para el %FUND% y la  %CLASS% puede ser inferior al mínimo:  %MINIMUM_BAL%. .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du compte pourrait être inférieur au minimum : %MINIMUM_BAL%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountsaldo voor %FUND% en CLASS% mag minder zijn dan het minimum:  %MINIMUM_BAL%")); }

        // Actions
	};
}



