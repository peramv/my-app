#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_corr_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_corr_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_corr_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CORR_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only 'I' and 'E' is valid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only 'I' and 'E' is valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur \"I\" und \"E\" sind gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo 'I' y 'E' son opciones válidas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls I et E sont valides.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Alleen 'I' en 'E' zijn geldig")); }

        // Actions
	};
}



