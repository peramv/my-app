#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_a90_rec_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_a90_rec_not_found() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_a90_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A90_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Financial institution information not found (A90).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Financial institution information not found (A90).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Finanzinstitut-Information nicht gefunden (A90).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre la institución financiera (A90).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur l'institution financière est introuvable (A90).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens financiële instelling zijn niet gevonden (A90)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



