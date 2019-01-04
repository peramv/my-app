#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_password_denied_too_long : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_password_denied_too_long() { }
		~CIFast_IFast_ifastdbrkr_err_password_denied_too_long() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PASSWORD_DENIED_TOO_LONG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Password can only be 12 characters in length.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Passwort verweigert – Passwort kann nur 12 Schriftzeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña debe tener al menos 12 caracteres")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – le mot de passe ne peut contenir plus de 12 caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord mag slechts 12 tekens lang zijn")); }

        // Actions
	};
}



