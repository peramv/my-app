#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_fid_account : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_fid_account() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_fid_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FID_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun agent pour le courtier %broker% et la succursale %branch%.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Selectionnez un autre courtier ou une autre succursale.")); }
	};
}



