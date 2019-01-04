#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_password_denied_too_short : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_password_denied_too_short() { }
		~CIFast_IFast_ifastdbrkr_err_password_denied_too_short() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PASSWORD_DENIED_TOO_SHORT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Password must be at least 4 characters in length.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Passwort verweigert – Passwort muss mindestens 4 Schriftzeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña debe tener al menos 4 caracteres")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – le mot de passe doit contenir au moins 4 caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord moet ten minste vier tekens lang zijn")); }

        // Actions
	};
}



