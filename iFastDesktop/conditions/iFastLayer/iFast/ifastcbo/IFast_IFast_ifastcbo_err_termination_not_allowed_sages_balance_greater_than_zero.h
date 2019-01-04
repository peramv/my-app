#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_termination_not_allowed_sages_balance_greater_than_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_termination_not_allowed_sages_balance_greater_than_zero() { }
		~CIFast_IFast_ifastcbo_err_termination_not_allowed_sages_balance_greater_than_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TERMINATION_NOT_ALLOWED_SAGES_BALANCE_GREATER_THAN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption of accumulated income is not allowed due to available notional balances in the account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat du revenu accumulé n'est pas autorisé en raison de l'existence d'un solde de subvention.")); }

        // Actions
	};
}



