#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redemp_contrary_client_guaguard_protection : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redemp_contrary_client_guaguard_protection() { }
		~CIFast_IFast_ifastcbo_warn_redemp_contrary_client_guaguard_protection() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDEMP_CONTRARY_CLIENT_GUAGUARD_PROTECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption is contrary to client guarantee guard protection setting rules.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant du rachat excède le montant autorisé en vertu du MRG/MRV.")); }

        // Actions
	};
}



