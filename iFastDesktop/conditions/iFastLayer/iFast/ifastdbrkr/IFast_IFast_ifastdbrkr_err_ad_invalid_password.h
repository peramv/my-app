#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_ad_invalid_password : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_ad_invalid_password() { }
		~CIFast_IFast_ifastdbrkr_err_ad_invalid_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_INVALID_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Invalid password.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse - Mot de passe invalide")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Ungültiges Kennwort")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Contraseña no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – mot de passe invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Ongeldig wachtwoord")); }

        // Actions
	};
}



