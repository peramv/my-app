﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_record_unavail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_record_unavail() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_record_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RECORD_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Record is unavailable.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Record is unavailable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Datensatz ist nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record is niet beschikbaar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een medewerker van de klantendienst en meld dit bericht")); }
	};
}



