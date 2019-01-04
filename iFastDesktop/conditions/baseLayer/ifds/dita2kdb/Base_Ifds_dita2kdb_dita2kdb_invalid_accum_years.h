#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_accum_years : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_accum_years() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_accum_years() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ACCUM_YEARS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Notification error occured to VM private connection.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Unbekanntes Zugriffsprofil")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Notification error occured to VM private connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une notification d'erreur s'est produite dans la connexion privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Notification error occured to VM private connection")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



