#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_min_allowable_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_min_allowable_purchase() { }
		~CIFast_IFast_ifastcbo_warn_acct_min_allowable_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_MIN_ALLOWABLE_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account: Less than minimum subsequent Purchase amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte : inférieur au montant d'achat subséquent minimal")); }

        // Actions
	};
}



