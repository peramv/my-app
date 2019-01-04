#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_password_expired : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_password_expired() { }
		~CIFast_IFast_dita2kdb_dita2kdb_password_expired() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_PASSWORD_EXPIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No password entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun mot de passe n'a ete saisi")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Kennwort eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo la contraseña")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun mot de passe n'a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen wachtwoord opgegeven")); }

        // Actions
	};
}



