#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_b07_rec_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_b07_rec_not_found() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_b07_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B07_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DCSC purchase accumulation cross-reference information not found (B07).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("DCSC purchase accumulation cross-reference information not found (B07).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DCSC-Kauf-Zuwachs-Verweis-Information nicht gefunden (B07).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la información de referencia cruzada de acumulación de compras de DCSC (B07).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le renvoi interne d'accumulation d'achat DCSC est introuvable (B07).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Referentiegegevens DCSC-aankoopaccumulatie zijn niet gevonden (BO7)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos introducidos. Si los datos son correctos, notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}



