#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_no_password_entered : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_no_password_entered() { }
		~CIFast_Infrastructure_ifastgui_gui_no_password_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_PASSWORD_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Password has expired.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Password has expired.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Kennwort ist nicht mehr gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La contraseña ha caducado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le mot de passe a expiré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wachtwoord is vervallen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Type a new password.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Type a new password.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie ein neues Kennwort ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Type a new password.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Tapez un nouveau mot de passe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Typ een nieuw wachtwoord")); }
	};
}



