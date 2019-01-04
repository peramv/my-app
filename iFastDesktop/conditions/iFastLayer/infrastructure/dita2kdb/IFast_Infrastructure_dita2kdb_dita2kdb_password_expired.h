#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_password_expired : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_password_expired() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_password_expired() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_PASSWORD_EXPIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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
		virtual DString GetAction_ES_ES() const { return DString(I_("Escriba una contraseña nueva.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Tapez un nouveau mot de passe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Typ een nieuw wachtwoord")); }
	};
}



