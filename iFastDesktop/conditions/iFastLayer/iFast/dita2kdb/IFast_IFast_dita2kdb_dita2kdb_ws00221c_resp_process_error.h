#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_process_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_process_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_process_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_PROCESS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied. No session record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Access denied. No session record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert. Kein Sitzungseintrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado. No hay registro de sesión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé. Aucun enregistrement de session.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd. Geen sessierecord")); }

        // Actions
	};
}



