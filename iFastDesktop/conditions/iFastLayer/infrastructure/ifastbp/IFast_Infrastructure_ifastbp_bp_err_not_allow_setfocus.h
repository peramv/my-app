#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastbp_bp_err_not_allow_setfocus : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastbp_bp_err_not_allow_setfocus() { }
		~CIFast_Infrastructure_ifastbp_bp_err_not_allow_setfocus() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NOT_ALLOW_SETFOCUS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was not successful. Password has expired.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was not successful. Password has expired.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war nicht erfolgreich. Das Kennwort ist nicht mehr gültig.\n\nAWD-Meldung: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD no fue exitosa. La contraseña ha caducado.\n\nMensaje de AWD: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD. Mot de passe expiré. \n\n Message AWD : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is niet gelukt. Wachtwoord is verlopen\n\n AWD-bericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Change password.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Change password.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Ändern Sie das Kennwort")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Change password.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Changez le mot de passe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Wijzig het wachtwoord")); }
	};
}



