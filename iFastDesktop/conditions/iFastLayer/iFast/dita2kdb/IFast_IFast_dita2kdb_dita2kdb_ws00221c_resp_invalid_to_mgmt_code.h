#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_mgmt_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_mgmt_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_to_mgmt_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_TO_MGMT_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Tax Type rules for this combination of Pension Jurisdiction and Tax Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Tax Type rules for this combination of Pension Jurisdiction and Tax Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Steuerart-Regeln für diese Kombination von Renten-Rechtssprechung und Steuerart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay reglas de tipo tributario para esta combinación de jurisdicción de jubilación y tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucune règle de type d'imposition pour cette combinaison de juridiction de retraite et de type d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen regels voor het belastingtype voor deze combinatie van pensioenrechtsgebied en belastingtype")); }

        // Actions
	};
}



