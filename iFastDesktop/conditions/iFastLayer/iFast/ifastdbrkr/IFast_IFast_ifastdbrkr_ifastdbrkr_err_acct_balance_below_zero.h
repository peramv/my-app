#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_balance_below_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_balance_below_zero() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_balance_below_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ACCT_BALANCE_BELOW_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account balance has gone below zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account balance has gone below zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du compte est inférieur à zéro.")); }

        // Actions
	};
}



