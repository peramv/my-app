#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_f16_rec_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_f16_rec_not_found() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_f16_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_F16_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pru-Bache 12-b1 management options information not found (F16).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pru-Bache 12-b1 management options information not found (F16).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pru-Bache 12-b1 Managementoptions-Information nicht gefunden (F16).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre opciones de administración Pru-Bache 12-b1 (F16).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur les options de gestion Pru-Bache 12-b1 est introuvable (F16)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens beheeropties Pru-Bache 12-b1 zijn niet gevonden (F16)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



