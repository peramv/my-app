#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_swp_payoption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_swp_payoption() { }
		~CIFast_IFast_ifastcbo_warn_swp_payoption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SWP_PAYOPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SWP cannot be set up when there is an existing  RRIF with Pay Option  GWA or LWA.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP ne peut pas être réglé lorsqu'un FERR existe avec l'option de paiement MRV ou un MRG.")); }

        // Actions
	};
}



