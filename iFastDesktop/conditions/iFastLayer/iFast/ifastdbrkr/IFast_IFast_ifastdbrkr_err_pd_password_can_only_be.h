#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_password_can_only_be : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_password_can_only_be() { }
		~CIFast_IFast_ifastdbrkr_err_pd_password_can_only_be() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_PASSWORD_CAN_ONLY_BE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Password can only be %threshold% characters in length.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Le nombre de caracteres du mot de passe doit être %threshold%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwort kann nur %threshold% Schriftzeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña sólo puede tener %threshold% caracteres.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – le mot de passe ne peut contenir plus de %threshold% caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord mag slechts %threshold% tekens lang zijn")); }

        // Actions
	};
}



