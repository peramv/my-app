#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_not_eligible_money_in_age_less_than_minimum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_not_eligible_money_in_age_less_than_minimum() { }
		~CIFast_IFast_ifastcbo_err_acct_not_eligible_money_in_age_less_than_minimum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NOT_ELIGIBLE_MONEY_IN_AGE_LESS_THAN_MINIMUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not eligible for Money-In, age is less than eligibility criteria.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas admissible au CELI, en raison de la date de naissance et du territoire fiscal.")); }

        // Actions
	};
}