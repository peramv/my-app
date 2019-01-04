#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_srvbase_err_maximum_connections : public CConditionObject
	{
	public:
		CBase_Ifds_srvbase_err_maximum_connections() { }
		~CBase_Ifds_srvbase_err_maximum_connections() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAXIMUM_CONNECTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("srvbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Connection refused. Maximum connections has been reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Connexion refusee. Le nombre maximum de connexions a ete atteint.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wert liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Conexión rechazada. Se ha alcanzado el número máximo de conexiones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Connexion refusée. Le nombre maximal de connexions a été atteint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbinding geweigerd. Maximumaantal verbindingen is bereikt.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Reessayez.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie den Wert erneut ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Vuelva a intentarlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Essayez de nouveau.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later opnieuw.")); }
	};
}



