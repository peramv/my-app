#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_password_denied_change_no_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_password_denied_change_no_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_password_denied_change_no_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PASSWORD_DENIED_CHANGE_NO_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password denied - Change Password not allowed for user.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Mot de passe refuse - Option Modifier mot de passe interdite a l'utilisateur")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Kennwortänderung für Benutzer nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Contraseña denegada - No se permite cambiar la contraseña al usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mot de passe invalide – l'utilisateur n'est pas autorisé à changer le mot de passe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord geweigerd - Wachtwoord wijzigen niet toegestaan voor gebruiker")); }

        // Actions
	};
}



