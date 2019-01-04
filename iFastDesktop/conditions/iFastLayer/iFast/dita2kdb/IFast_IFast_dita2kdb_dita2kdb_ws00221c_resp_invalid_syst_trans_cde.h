#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_syst_trans_cde : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_syst_trans_cde() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_syst_trans_cde() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SYST_TRANS_CDE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash' is not a valid fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cash' is not a valid fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("\"Bargeld\" ist kein gültiger Fonds.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("\"Efectivo\" no es un fondo válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Comptant n'est pas un fonds valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Contant' is geen geldig fonds")); }

        // Actions
	};
}



