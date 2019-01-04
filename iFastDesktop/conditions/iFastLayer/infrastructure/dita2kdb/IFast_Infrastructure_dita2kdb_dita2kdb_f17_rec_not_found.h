#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_f17_rec_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_f17_rec_not_found() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_f17_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_F17_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pru-Bache 12-b1 account level trade accumulation information not found (F17).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pru-Bache 12-b1 account level trade accumulation information not found (F17).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pru-Bache 12-b1 Handelszuwachs auf  Kontolevel-Information nicht gefunden (F17).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre acumulación de operaciones a nivel de la cuenta Pru-Bache 12-b1 (F17).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur l'accumulation Pru-Bache 12-b1 est introuvable (F17).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens handelsaccumulatie accountniveau Pru-Bache 12-b1 zijn niet gevonden (F17)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos introducidos. Si los datos son correctos, notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



