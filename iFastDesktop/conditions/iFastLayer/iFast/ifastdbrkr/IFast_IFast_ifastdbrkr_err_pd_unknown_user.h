#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_unknown_user : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_unknown_user() { }
		~CIFast_IFast_ifastdbrkr_err_pd_unknown_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_UNKNOWN_USER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Unknown user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Utilisateur inconnu")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Unbekannter Benutzer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - Usuario desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – utilisateur inconnu")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Onbekende gebruiker")); }

        // Actions
	};
}



