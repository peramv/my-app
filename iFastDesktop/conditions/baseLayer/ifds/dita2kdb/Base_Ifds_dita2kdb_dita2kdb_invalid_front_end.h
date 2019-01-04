#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_front_end : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_front_end() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_front_end() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FRONT_END")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Il reste des donnees non enregistrees.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Enregistrez les donnees et reiterez l'action.")); }
	};
}



