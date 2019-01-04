#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_b15_rec_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_b15_rec_not_found() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_b15_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B15_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("NASU social code options not found (B15).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("NASU social code options not found (B15).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("NASU-Sozialcode-Optionen nicht gefunden (B15).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron las opciones de código social NASU (B15).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les options de code social de réglage de nouveau compte sont introuvables (B15).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opties sociale codes NASU zijn niet gevonden (B15)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



