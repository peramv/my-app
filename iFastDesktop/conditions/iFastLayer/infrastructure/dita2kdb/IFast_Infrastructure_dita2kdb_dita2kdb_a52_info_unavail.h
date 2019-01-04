#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_a52_info_unavail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_a52_info_unavail() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_a52_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A52_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund literals information is unavailable (A52).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund literals information is unavailable (A52).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Literals-Information nicht verfügbar (A52).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información de Fund literals no está disponible (A52).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur les libellés de fonds n'est pas disponible (A52).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens Fund Literals zijn niet beschikbaar (A52)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später nochmals  oder wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try again later or contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Réessayez plus tard ou communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later nog eens of neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



