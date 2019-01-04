#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_contrib_year_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_contrib_year_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_contrib_year_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CONTRIB_YEAR_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A value for Minimum Withdraw Age is mandatory.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A value for Minimum Withdraw Age is mandatory.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Wert für das minimale Abbuch-Alter ist obligatorisch.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Es obligatorio introducir un valor para la edad de retiro mínima.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge de retrait minimal est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een waarde voor minimumleeftijd voor opname is verplicht")); }

        // Actions
	};
}



