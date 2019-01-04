#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_system_down : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_system_down() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_system_down() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_SYSTEM_DOWN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("System is down.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("System is down.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System ist außer Betrieb.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema está desactivado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Système hors service")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem is uit de lucht")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



