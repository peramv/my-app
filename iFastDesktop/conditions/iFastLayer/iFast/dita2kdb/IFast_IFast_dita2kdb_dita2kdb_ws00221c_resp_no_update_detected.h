#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_update_detected : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_update_detected() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_no_update_detected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_NO_UPDATE_DETECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Deposit ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Deposit ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Depot-ID.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de depósito no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig deposito-ID")); }

        // Actions
	};
}



