#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_changed_by_diff_oper : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_changed_by_diff_oper() { }
		~CBase_Ifds_dita2kdb_dita2kdb_changed_by_diff_oper() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_CHANGED_BY_DIFF_OPER")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are %DAYS% days remaining until the user is required to change the password.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Il reste %DAYS% avant que l'utilisateur ne doive modifier le mot de passe.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Mit diesem Profil heute kein Zugriff")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Quedan %DAYS% días para que el usuario deba cambiar la contraseña.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur devra changer de mot de passe dans %DAYS% jours.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er resteren nog %DAYS% dagen totdat de gebruiker zijn wachtwoord moet wijzigen.")); }

        // Actions
	};
}



