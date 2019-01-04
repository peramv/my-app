#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_no_holdings_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_no_holdings_for_fund() { }
		~CIFast_IFast_ifastcbo_err_acct_no_holdings_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NO_HOLDINGS_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has no holdings for this fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account has no holdings for this fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account has no holdings for this fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'a aucun portefeuille pour ce fonds.")); }

        // Actions
	};
}



