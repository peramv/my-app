#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_new_password_confirmation_no_match : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_new_password_confirmation_no_match() { }
		~CIFast_Infrastructure_ifastgui_gui_new_password_confirmation_no_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password is too similar.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Password is too similar.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Kennwort ist zu ähnlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La contraseña es demasiado similar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe est trop similaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord vertoont teveel gelijkenis met vorige wachtwoord")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Type a new password and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Type a new password and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie ein neues Kennwort ein und führen Sie eine Neueingabe durch.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Type a new password and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Tapez un nouveau mot de passe et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Typ een nieuw wachtwoord en voer dit opnieuw in")); }
	};
}



