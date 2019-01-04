#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dealer : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dealer() { }
		~CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dealer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_OPER_NOT_AUTH_DEALER")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured waiting for signal from VM connection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registrierter Adressenstandard nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error occured waiting for signal from VM connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de l'attente d'un signal de la connexion privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Error occured waiting for signal from VM connection.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



