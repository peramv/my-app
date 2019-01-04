#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tax_exempt_auth_should_be_updated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tax_exempt_auth_should_be_updated() { }
		~CIFast_IFast_ifastcbo_warn_tax_exempt_auth_should_be_updated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAX_EXEMPT_AUTH_SHOULD_BE_UPDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Exemption Authorization should be updated for W8/W9 by user.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’utilisateur doit mettre à jour toute autorisation d’exonération fiscale applicable aux formulaires W8/W9.")); }

        // Actions
	};
}



