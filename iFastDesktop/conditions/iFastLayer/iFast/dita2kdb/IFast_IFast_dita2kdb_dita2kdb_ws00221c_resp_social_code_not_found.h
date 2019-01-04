#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_found() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_social_code_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_SOCIAL_CODE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one month must be turned on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins un mois doit être active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Monat muss aktiviert sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe activarse al menos un mes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un mois doit être activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste een maand zijn aangezet")); }

        // Actions
	};
}



