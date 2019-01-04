#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_useriderr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_useriderr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_dfhresp_useriderr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_DFHRESP_USERIDERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUND% and %CLASS% not wire order eligible.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les transferts telegraphiques ne sont pas autorisés pour %FUND%, %CLASS%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUND% und %CLASS% sind nicht für telegrafische Aufträge geeignet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FUND% y %CLASS% no son aptos para órdenes de transferencia cablegráfica")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% et la classe %CLASS% ne sont pas admissibles aux ordres électroniques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FUND% en %CLASS% komen niet in aanmerking voor telegrafische orders")); }

        // Actions
	};
}



