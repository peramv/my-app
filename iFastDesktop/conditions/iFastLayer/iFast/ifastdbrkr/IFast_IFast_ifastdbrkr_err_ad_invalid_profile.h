#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_invalid_profile : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_invalid_profile() { }
		~CIFast_IFast_ifastdbrkr_err_ad_invalid_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_INVALID_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Invalid profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Profil invalide")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Ungültiges Profil")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Perfil no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – profil invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Ongeldig profiel")); }

        // Actions
	};
}



