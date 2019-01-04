#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_purch_nav_acct_bel_fund_nav_deposit_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_purch_nav_acct_bel_fund_nav_deposit_type() { }
		~CIFast_IFast_ifastcbo_err_purch_nav_acct_bel_fund_nav_deposit_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PURCH_NAV_ACCT_BEL_FUND_NAV_DEPOSIT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only deposit type 27 is allowed for BEL funds purchase in a NAV Share account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only deposit type 27 is allowed for BEL funds purchase in a NAV Share account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le code de dépôt 27 est autorisé pour l'achat de fonds avec frais de rachat dans un compte de parts à la valeur de l'actif net.")); }

        // Actions
	};
}



