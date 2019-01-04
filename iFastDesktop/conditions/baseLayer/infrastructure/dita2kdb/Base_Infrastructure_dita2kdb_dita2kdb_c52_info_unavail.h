#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_c52_info_unavail : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_c52_info_unavail() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_c52_info_unavail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_C52_INFO_UNAVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account 1099R multiple tax jurisdictions reporting table unavailable.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account 1099R multiple tax jurisdictions reporting table unavailable.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account 1099R multiple tax jurisdictions reporting table unavailable.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La table de déclaration des multiples juridictions fiscales 1099R du compte est disponible. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



