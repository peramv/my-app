#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_investor_grp : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_investor_grp() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_investor_grp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_INVESTOR_GRP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid investor group id.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid investor group id.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid investor group id.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de groupe d'investisseurs invalide. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify investor group id and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Verify investor group id and re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify investor group id and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de groupe d'investisseurs et réessayez.")); }
	};
}



