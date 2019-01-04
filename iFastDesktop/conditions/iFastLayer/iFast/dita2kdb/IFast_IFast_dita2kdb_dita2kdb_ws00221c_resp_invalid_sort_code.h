#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sort_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sort_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_sort_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_SORT_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has been coded as assigned. No redemptions available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account has been coded as assigned. No redemptions available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto wurde als zugewiesen kodiert. Keine Tilgungen verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta se ha codificado como asignada. No hay rescates disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte a été codé comme Mis en garantie. Aucun rachat disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is gecodeerd als toegewezen. Er is geen aflossing mogelijk")); }

        // Actions
	};
}



