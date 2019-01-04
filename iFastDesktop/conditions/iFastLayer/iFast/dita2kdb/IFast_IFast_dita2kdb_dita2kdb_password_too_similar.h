#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_password_too_similar : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_password_too_similar() { }
		~CIFast_IFast_dita2kdb_dita2kdb_password_too_similar() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_PASSWORD_TOO_SIMILAR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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



