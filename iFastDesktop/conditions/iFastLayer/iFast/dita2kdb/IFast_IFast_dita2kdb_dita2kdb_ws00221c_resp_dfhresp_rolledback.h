#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_rolledback : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_rolledback() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_rolledback() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_ROLLEDBACK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% and class %CLASS% balance for account %ACCTNUM% is zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le solde de %ACCTNUM% est nul")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%ACCTNUM% hat ein Nullsaldo.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%ACCTNUM% tiene saldo cero")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du fonds %FUND% et de la classe %CLASS% pour le compte %ACCTNUM% est nul.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%ACCTNUM% heeft een saldo van nul")); }

        // Actions
	};
}



