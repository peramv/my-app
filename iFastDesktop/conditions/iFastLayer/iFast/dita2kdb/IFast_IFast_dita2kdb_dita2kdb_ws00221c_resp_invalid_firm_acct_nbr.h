#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_acct_nbr : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_acct_nbr() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_firm_acct_nbr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FIRM_ACCT_NBR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account FC re-balance Stop Flag is active.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account FC re-balance Stop Flag is active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stopp-Kennzeichen für Konto FC-Neuausgleich ist aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El flag de detención de rebalanceo FC de la cuenta está activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal d'arrêt de rebalancement de monnaie étrangère du compte est actif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eindvlag voor nieuwe saldering buitenlandse inhoud van account is actief")); }

        // Actions
	};
}



