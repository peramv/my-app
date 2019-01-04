#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_acct_to_upd : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_acct_to_upd() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_no_acct_to_upd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_NO_ACCT_TO_UPD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied - Unknown response type:<Response Type>.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Accese deneied - Unknow response type:<Response Type>.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – unbekannte Antwortart: <Response Type>.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado - Tipo de respuesta desconocido:<Response Type>")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé – type de réponse inconnu : <Response Type>")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd - Onbekend responstype:<responstype>")); }

        // Actions
	};
}



