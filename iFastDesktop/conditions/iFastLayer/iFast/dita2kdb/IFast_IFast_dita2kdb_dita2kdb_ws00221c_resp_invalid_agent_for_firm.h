#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_agent_for_firm : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_agent_for_firm() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_agent_for_firm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_AGENT_FOR_FIRM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entire account has been assigned. No redemption available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entire account has been assigned. No redemption available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das gesamte Konto wurde zugewiesen. Keine Tilgung verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha asignado toda la cuenta. No hay rescate disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte a été entièrement mis en garantie. Aucun rachat disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige account is toegewezen. Er is geen aflossing mogelijk")); }

        // Actions
	};
}



