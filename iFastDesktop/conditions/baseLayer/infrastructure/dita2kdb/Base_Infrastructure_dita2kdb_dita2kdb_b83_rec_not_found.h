#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_b83_rec_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_b83_rec_not_found() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_b83_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_B83_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("YTD account totals record not found.  CICS return code is %rc%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("YTD account totals record not found.  CICS return code is %rc%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("YTD account totals record not found.  CICS return code is %rc%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des totaux du montant de cumul annuel jusqu'à ce jour est introuvable. Le code de renvoi CICS est %rc%.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
	};
}



