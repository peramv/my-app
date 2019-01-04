#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_pre_agreement : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_pre_agreement() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_pre_agreement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PRE_AGREEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Connection refused. Maximum connections has been reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Connexion refusee. Le nombre maximum de connexions a ete atteint.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Conexión rechazada. Se ha alcanzado el número máximo de conexiones.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbinding geweigerd. Maximumaantal verbindingen is bereikt.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try again.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Reessayez.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Vuelva a intentarlo.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later opnieuw.")); }
	};
}



