#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_no_a53_for_verify_dte : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_no_a53_for_verify_dte() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_no_a53_for_verify_dte() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_A53_FOR_VERIFY_DTE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Price not found for this date (A53).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Price not found for this date (A53).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Preis für dieses Datum nicht gefunden. (A53).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el precio para esta fecha (A53).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Prix introuvable pour cette date (A53)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Prijs is niet gevonden voor deze datum (A53)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify price information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify price information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Preisinformationen. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la información de precio. Si los datos son correctos, notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur le prix. Si la saisie est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de prijsgegevens. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



