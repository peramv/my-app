#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_new_password_confirmation_no_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_new_password_confirmation_no_match() { }
		~CIFast_IFast_ifastgui_gui_new_password_confirmation_no_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("New password and confirmation do not match.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le nouveau mot de passe et la confirmation ne correspondent pas")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das neue Kennwort und die Bestätigung stimmen nicht überein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La contraseña nueva y la confirmación no coinciden")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nouveau mot de passe et la confirmation diffèrent.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het nieuwe wachtwoord en de bevestiging komen niet overeen")); }

        // Actions
	};
}



