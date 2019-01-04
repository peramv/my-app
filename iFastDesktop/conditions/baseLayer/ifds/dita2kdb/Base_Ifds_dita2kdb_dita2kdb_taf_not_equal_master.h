#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_taf_not_equal_master : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_taf_not_equal_master() { }
		~CBase_Ifds_dita2kdb_dita2kdb_taf_not_equal_master() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TAF_NOT_EQUAL_MASTER")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please select broker and branch first.")); }

        // Actions
	};
}



