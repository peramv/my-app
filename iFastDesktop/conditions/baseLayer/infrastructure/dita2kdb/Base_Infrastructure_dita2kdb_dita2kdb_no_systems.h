#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_no_systems : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_no_systems() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_no_systems() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_SYSTEMS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No systems or management companies were returned.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No systems or management companies were returned.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurden keine Systeme oder Management-Unternehmen ausgegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se devolvieron sistemas o compañías administradoras.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun système ni aucune entreprise de gestion n'ont été renvoyés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen systemen of beheerbedrijven gegenereerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



