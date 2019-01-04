#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_for_institutional_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_for_institutional_account() { }
		~CIFast_IFast_ifastcbo_warn_ams_setup_not_allowed_for_institutional_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMS_SETUP_NOT_ALLOWED_FOR_INSTITUTIONAL_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS set-up not allowed for Institutional Account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage du service de gestion de portefeuille n'est pas autorisé pour un compte institutionnel.")); }

        // Actions
	};
}



