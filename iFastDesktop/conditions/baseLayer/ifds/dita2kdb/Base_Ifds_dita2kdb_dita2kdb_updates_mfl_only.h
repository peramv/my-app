#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_updates_mfl_only : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_updates_mfl_only() { }
		~CBase_Ifds_dita2kdb_dita2kdb_updates_mfl_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_UPDATES_MFL_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. %CMD% command not found.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se encontró el comando %CMD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Opdracht %CMD% is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



