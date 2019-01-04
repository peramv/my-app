#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tran_type : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tran_type() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_tran_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TRAN_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse is older than shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spouse should  not be older than shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehepartner ist älter als der Aktionär.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cónyuge es mayor que el accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint est plus âgé que l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Echtgenoot of echtgenote is ouder dan aandeelhouder")); }

        // Actions
	};
}



