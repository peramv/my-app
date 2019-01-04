#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_auth_but_no_desc : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_auth_but_no_desc() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_auth_but_no_desc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_AUTH_BUT_NO_DESC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dealer funds record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Dealer funds record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Händler-Fondseintrag nicht verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de fondos del agente no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des fonds du courtier n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record handelaarsfonds is niet beschikbaar")); }

        // Actions
	};
}



