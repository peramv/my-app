#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_taf_not_equal_master : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_taf_not_equal_master() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_taf_not_equal_master() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_TAF_NOT_EQUAL_MASTER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("User Maturity date must be earlier or equal to calculated Legal Maturity Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer-Fälligkeitsdatum muss <= sein als das gesetzliche Fälligkeitsdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento del usuario debe ser <= a la fecha de vencimiento legal calculada")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum gebruiker moet eerder zijn dan of gelijk aan berekende wettelijke vervaldatum")); }

        // Actions
	};
}



