#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_invalid_root_element_name : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_invalid_root_element_name() { }
		~CBase_Infrastructure_xparser_err_invalid_root_element_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ROOT_ELEMENT_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD change password failed. New password is too similar.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD change password failed. New password is too similar.\n\nAWD Message: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kennwortänderung in AWD ist fehlgeschlagen. Das neue Kennwort ist dem alten zu ähnlich. %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cambio de contraseña de AWD falló. La contraseña nueva es demasiado similar.\n\nMensaje de AWD: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de changement de mot de passe AWD. Le nouveau mot de passe est trop semblable à l'ancien. \n\n Message AWD : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wijzigen AWD-wachtwoord is mislukt. Het nieuwe wachtwoord lijkt te veel op het oude.\n\nAWD-bericht: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter a new password.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a new password.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie ein neues Kennwort ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Escriba una contraseña nueva.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez un nouveau mot de passe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een nieuw wachtwoord op")); }
	};
}



