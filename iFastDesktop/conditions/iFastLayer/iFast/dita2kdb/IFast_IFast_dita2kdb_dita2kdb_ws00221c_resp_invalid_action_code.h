#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_action_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_action_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_action_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACTION_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax types rules have not yet been set up.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Tax types rules have not yet been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerarten-Regeln wurden noch nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Aún no se han configurado las reglas de tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les règles de types d'imposition n'ont pas encore été réglées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen regels voor belastingtypes ingesteld")); }

        // Actions
	};
}



