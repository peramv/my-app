#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_zip_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ZIP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Units not allowed for Net Redemptions.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Units not allowed for Net Redemptions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anteile für Netto-Tilgungen nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten unidades para rescates netos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités non autorisées pour les rachats nets")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheden zijn niet toegestaan voor netto aflossingen")); }

        // Actions
	};
}



