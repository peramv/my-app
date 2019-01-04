#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_error_in_binary_search : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_error_in_binary_search() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_error_in_binary_search() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_ERROR_IN_BINARY_SEARCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access denied. Passed logoff time.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Acces refuse. Temps de deconnexion ecoule.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert. Abmeldezeit überschritten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Acceso denegado. Pasó el tiempo de desconexión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accès refusé. Délai de fermeture de session dépassé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegang geweigerd. Afmeldtijd is verstreken")); }

        // Actions
	};
}



