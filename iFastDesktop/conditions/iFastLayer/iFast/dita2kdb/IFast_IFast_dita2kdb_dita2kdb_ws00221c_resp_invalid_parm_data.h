#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_parm_data : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_parm_data() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_parm_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PARM_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No pending trades found for the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No pending trades found for the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine schwebenden Handel für das Konto gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron operaciones pendientes para la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune transaction en suspens n'a été trouvée pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen in behandeling zijnde transacties gevonden voor het account")); }

        // Actions
	};
}



