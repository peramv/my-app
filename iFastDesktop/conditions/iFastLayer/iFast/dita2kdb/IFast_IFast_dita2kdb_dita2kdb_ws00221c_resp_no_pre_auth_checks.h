#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_pre_auth_checks : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_pre_auth_checks() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_pre_auth_checks() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NO_PRE_AUTH_CHECKS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Deposit Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Deposit Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Depot-Typ")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de depósito no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig depositotype")); }

        // Actions
	};
}



