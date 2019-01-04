#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pd_password_must_be_at_least : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pd_password_must_be_at_least() { }
		~CIFast_IFast_ifastdbrkr_err_pd_password_must_be_at_least() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PD_PASSWORD_MUST_BE_AT_LEAST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Password must be at least %threshold% characters in length.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Le nombre minimum de caracteres du mot de passe doit être %threshold%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwort muss mindestens %threshold% Schriftzeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - La contraseña debe tener al menos %threshold% caracteres.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – le mot de passe doit contenir au moins %threshold% caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord moet ten minste %threshold% tekens lang zijn")); }

        // Actions
	};
}



