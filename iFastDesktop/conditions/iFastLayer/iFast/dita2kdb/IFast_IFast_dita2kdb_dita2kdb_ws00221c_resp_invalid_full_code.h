#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_full_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_full_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_full_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FULL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Code must have RRIF Flag on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund Code must have RRIF Flag on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für den Fondscode muss das RRIF-Kennzeichen aktiviert sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de fondo debe tener RRIFFlag activado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal RRIF du code de fonds doit être activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De RRIF-vlag moet zijn aangezet voor de fondscode")); }

        // Actions
	};
}



