#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_remainingprincipal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_remainingprincipal() { }
		~CIFast_IFast_ifastcbo_warn_alloc_amt_exceeds_investment_remainingprincipal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ALLOC_AMT_EXCEEDS_INVESTMENT_REMAININGPRINCIPAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sum of allocation amounts exceeds the remaining principal of the investment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La somme des montants de répartition excède le capital restant de l'investissement.")); }

        // Actions
	};
}



