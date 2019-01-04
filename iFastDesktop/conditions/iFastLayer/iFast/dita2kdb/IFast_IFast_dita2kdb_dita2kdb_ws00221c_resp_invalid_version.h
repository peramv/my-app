#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_version : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_version() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only \"E\", \"S\", \"M\" and \"X\" are valid values.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only \"E\", \"S\", \"M\" and \"X\" are valid values.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur \"E\", \"S\", \"M\" und \"X\" sind gültige Werte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo \"E\", \"S\", \"M\" y \"X\" son valores válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les seules valeurs valides sont E, S, M et X.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen  'E, 'S', 'M' en 'X' zijn geldige waarden")); }

        // Actions
	};
}



