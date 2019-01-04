#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_paf_bucket : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_paf_bucket() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_paf_bucket() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PAF_BUCKET")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de trouver des criteres de recherche.")); }

        // Actions
	};
}



