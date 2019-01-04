#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unable_to_change_acct_portfolio : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unable_to_change_acct_portfolio() { }
		~CIFast_IFast_ifastcbo_err_unable_to_change_acct_portfolio() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_CHANGE_ACCT_PORTFOLIO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has either processed or pending trade, unable to change account's portfolio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte comporte une transaction traitée ou en suspens; impossible de changer le portefeuille du compte.")); }

        // Actions
	};
}



