#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_partial_exemption_scope_exist_acct_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_partial_exemption_scope_exist_acct_fund_class() { }
		~CIFast_IFast_ifastcbo_err_full_partial_exemption_scope_exist_acct_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_PARTIAL_EXEMPTION_SCOPE_EXIST_ACCT_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full/Partial Exemption exists for account-fund-class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il existe des exemptions totales et partielles pour les comptes de cette catégorie de fonds.")); }

        // Actions
	};
}



