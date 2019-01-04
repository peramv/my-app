#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_acct_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_acct_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_acct_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ACCT_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Could not send data to host.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Could not send data to host.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Daten konnten nicht an Host gesendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudieron enviar los datos al host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'envoyer des données à l'hôte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens konden niet worden verzonden naar host")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



