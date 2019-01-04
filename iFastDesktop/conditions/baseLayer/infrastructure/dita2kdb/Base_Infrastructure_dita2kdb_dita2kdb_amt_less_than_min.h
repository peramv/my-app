#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_amt_less_than_min : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_amt_less_than_min() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_amt_less_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AMT_LESS_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entered amount is less than the minimum allowed.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entered amount is less than the minimum allowed.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entered amount is less than the minimum allowed.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi est inférieur au minimum autorisé. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify amount and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Verify amount and re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify amount and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le montant et réessayez.")); }
	};
}



