#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_eventsem_open_fail : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_eventsem_open_fail() { }
		~CBase_Ifds_dicore_dicore_eventsem_open_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_EVENTSEM_OPEN_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Untergeordnete Sitzung konnte nicht erstellt werden.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
	};
}



