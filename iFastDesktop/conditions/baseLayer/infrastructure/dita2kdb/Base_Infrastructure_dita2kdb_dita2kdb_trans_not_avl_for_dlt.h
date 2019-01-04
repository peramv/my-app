#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_trans_not_avl_for_dlt : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_trans_not_avl_for_dlt() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_trans_not_avl_for_dlt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TRANS_NOT_AVL_FOR_DLT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction not available for deletion.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction not available for deletion.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transaction not available for deletion.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction ne peut être supprimée. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



