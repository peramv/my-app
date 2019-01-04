#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawdi_diawdi_logon_invalid_new_password : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawdi_diawdi_logon_invalid_new_password() { }
		~CIFast_Infrastructure_diawdi_diawdi_logon_invalid_new_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_INVALID_NEW_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD change password failed. New password is invalid.\n\n")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD change password failed. New password is invalid.\n\n")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kennwortänderung in AWD ist fehlgeschlagen. Das neue Kennwort ist ungültig.\n\n")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cambio de contraseña de AWD falló. La contraseña nueva no es válida.\n\n")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de changement de mot de passe AWD. Nouveau mot de passe invalide. \n\n")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wijzigen AWD-wachtwoord is mislukt. Nieuwe wachtwoord is ongeldig.\n\n")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a new password.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a new password.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie ein neues Kennwort ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Escriba una contraseña nueva.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez un nouveau mot de passe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een nieuw wachtwoord op")); }
	};
}



