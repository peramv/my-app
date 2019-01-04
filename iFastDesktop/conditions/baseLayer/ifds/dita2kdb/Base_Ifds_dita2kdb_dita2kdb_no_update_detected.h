#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_no_update_detected : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_no_update_detected() { }
		~CBase_Ifds_dita2kdb_dita2kdb_no_update_detected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_UPDATE_DETECTED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun numero d'actionnaire ou de compte valide n'a ete saisi.")); }

        // Actions
	};
}



