#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_min_init_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_min_init_purchase() { }
		~CIFast_IFast_ifastcbo_err_acct_min_init_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_MIN_INIT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account: Less than minimum Initial Purchase amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte : inférieur au montant d'achat initial minimal")); }

        // Actions
	};
}



