#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ia_brk_brnch_slsrep_not_same_with_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ia_brk_brnch_slsrep_not_same_with_account() { }
		~CIFast_IFast_ifastcbo_warn_ia_brk_brnch_slsrep_not_same_with_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker/Branch/Sales Rep of Investor Authorization and Account are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier/l'unité de service/le représentant des ventes de l'autorisation et du compte de l'investisseur sont différents.")); }

        // Actions
	};
}



