#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_rein_dollar : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_rein_dollar() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_rein_dollar() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REIN_DOLLAR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured waiting for signal from VM private connection.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Eintrag mit den Kommentaren des Aktionärs konnte nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error occured waiting for signal from VM private connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de l'attente d'un signal de la connexion privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Error occured waiting for signal from VM private connection.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



