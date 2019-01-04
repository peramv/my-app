#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_insuff_collected_shrs : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_insuff_collected_shrs() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_insuff_collected_shrs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INSUFF_COLLECTED_SHRS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Currency must be %SYS_CURRENCY%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La devise doit être %SYS_CURRENCY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Währung muss %SYS_CURRENCY% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La divisa debe ser %SYS_CURRENCY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie doit être %SYS_CURRENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Valuta moet %SYS_CURRENCY% zijn")); }

        // Actions
	};
}



