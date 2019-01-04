#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_multi_c52_states : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_multi_c52_states() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_multi_c52_states() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_MULTI_C52_STATES")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple 1099R tax jurisdiction reporting states defined.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Multiple 1099R tax jurisdiction reporting states defined.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Multiple 1099R tax jurisdiction reporting states defined.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("De multiples états de déclaration de juridiction fiscale 1099R sont définis. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



