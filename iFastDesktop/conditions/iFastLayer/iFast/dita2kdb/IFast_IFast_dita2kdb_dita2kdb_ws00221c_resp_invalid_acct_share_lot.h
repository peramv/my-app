#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_share_lot : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_share_lot() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_acct_share_lot() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_ACCT_SHARE_LOT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unit-Detl record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unit-Detl record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unit-Detl-Eintrag nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Unit-Detl")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement de détail d'unité introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Unit-Detl is niet gevonden")); }

        // Actions
	};
}



