#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_b08_record_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_b08_record_not_found() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_b08_record_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B08_RECORD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DCSC management plan information not found (B08).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("DCSC management plan information not found (B08).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DCSC-Managementplan-Information nicht gefunden (B08).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la información del plan de administración de DCSC (B08).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le régime de gestion DCSC est introuvable (B08).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens DCSC-beheerplan zijn niet gevonden (BO8)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



