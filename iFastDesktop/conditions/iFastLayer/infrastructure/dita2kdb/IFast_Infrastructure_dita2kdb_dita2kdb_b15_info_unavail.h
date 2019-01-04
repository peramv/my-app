#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_b15_info_unavail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_b15_info_unavail() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_b15_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B15_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("NASU social code options not unavailable (B15).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("NASU social code options not unavailable (B15).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("NASU-Sozialcode-Optionen nicht verfügbar (B15).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las opciones de código social NASU no están disponibles (B15).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les options de code social de réglage de nouveau compte sont disponibles (B15).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opties sociale codes NASU zijn niet beschikbaar (B15)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später nochmals  oder wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez plus tard ou communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later nog eens of neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



