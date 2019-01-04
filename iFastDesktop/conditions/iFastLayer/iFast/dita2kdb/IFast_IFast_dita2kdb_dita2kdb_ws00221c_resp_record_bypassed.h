#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_record_bypassed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_record_bypassed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_record_bypassed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_RECORD_BYPASSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date cannot be set backwards.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de definir la date d'effet retrospectivement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum darf nicht rückwirkend festgelegt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia no puede definirse como una fecha pasada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur ne peut être réglée antérieurement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De ingangsdatum kan niet met terugwerkende kracht worden ingesteld")); }

        // Actions
	};
}



