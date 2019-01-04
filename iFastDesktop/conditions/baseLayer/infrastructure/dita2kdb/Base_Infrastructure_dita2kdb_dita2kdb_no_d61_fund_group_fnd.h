#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_no_d61_fund_group_fnd : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_no_d61_fund_group_fnd() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_no_d61_fund_group_fnd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_D61_FUND_GROUP_FND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid fund group number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid fund group number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid fund group number.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de groupe de fonds invalide. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify fund group number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Verify fund group number and re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify fund group number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro du groupe de fonds et réessayez.")); }
	};
}



