#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_system_id_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_system_id_error() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_system_id_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTEM_ID_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a system ID error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is a system ID error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt einen System-ID-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un error de identificación del sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une erreur de code de système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout bij het systeem-ID")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



