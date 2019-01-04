#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_special_redemption_no : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_special_redemption_no() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_ach_special_redemption_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ACH_SPECIAL_REDEMPTION_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Data Found")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Données introuvables")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Daten gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune donnée n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen gegevens gevonden")); }

        // Actions
	};
}



