#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_mgmts_not_equal : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_mgmts_not_equal() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_exch_mgmts_not_equal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_EXCH_MGMTS_NOT_EQUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are current fund balances for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There are current fund balances for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto liegen aktuelle Fonds-Saldos vor.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta tiene saldos en el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des soldes de fonds courants pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn huidige fondssaldi voor dit account")); }

        // Actions
	};
}



