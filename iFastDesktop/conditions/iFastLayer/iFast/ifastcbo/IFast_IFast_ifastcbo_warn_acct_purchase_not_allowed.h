#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_purchase_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_purchase_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_acct_purchase_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_PURCHASE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account: Purchase not allowed for Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte : achat non autorisé pour le fonds")); }

        // Actions
	};
}



