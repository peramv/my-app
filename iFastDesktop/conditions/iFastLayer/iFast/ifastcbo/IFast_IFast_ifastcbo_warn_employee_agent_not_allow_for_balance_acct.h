#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_employee_agent_not_allow_for_balance_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_employee_agent_not_allow_for_balance_acct() { }
		~CIFast_IFast_ifastcbo_warn_employee_agent_not_allow_for_balance_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund relationship cannot be changed to %ACCOUNT_TYPE% when account balance > 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La relation avec le fonds ne peut être changée pour %ACCOUNT_TYPE% lorsque le solde du compte est supérieur à zéro.")); }

        // Actions
	};
}



