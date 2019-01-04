#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_bal_may_be_less_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_bal_may_be_less_min() { }
		~CIFast_IFast_ifastdbrkr_err_acct_bal_may_be_less_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_BAL_MAY_BE_LESS_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account balance may be less than minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Saldo kann unter dem Minimum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo de la cuenta puede ser inferior al mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du compte peut être inférieur au minimum.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountsaldo kan lager zijn dan minimum")); }

        // Actions
	};
}



