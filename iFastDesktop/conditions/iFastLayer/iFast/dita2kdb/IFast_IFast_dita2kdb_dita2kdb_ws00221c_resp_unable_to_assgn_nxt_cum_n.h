#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_nxt_cum_n : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_nxt_cum_n() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_unable_to_assgn_nxt_cum_n() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_UNABLE_TO_ASSGN_NXT_CUM_N")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Fund and Class entered for this Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Fund and Class entered for this Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige/r Fonds und Klasse für dieses Konto eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo un fondo y clase no válidos para esta cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds et classe saisis invalides pour ce compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig fonds en ongeldige categorie opgegeven voor dit account")); }

        // Actions
	};
}



