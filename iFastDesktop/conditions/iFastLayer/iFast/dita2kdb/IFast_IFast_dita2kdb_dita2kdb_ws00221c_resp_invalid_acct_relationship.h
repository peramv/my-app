#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_relationship : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_relationship() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_relationship() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCT_RELATIONSHIP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate from tables is %RATE_SYS_CALC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate from tables is %RATE_SYS_CALC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz aus den Tabellen ist %RATE_SYS_CALC%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa de las tablas es %RATE_SYS_CALC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux des tables est de %RATE_SYS_CALC%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief uit tabellen is %RATE_SYS_CALC%")); }

        // Actions
	};
}



