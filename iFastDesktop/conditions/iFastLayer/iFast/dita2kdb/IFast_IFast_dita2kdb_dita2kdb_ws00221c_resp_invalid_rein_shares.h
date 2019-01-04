#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_shares : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_shares() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_rein_shares() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_REIN_SHARES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one or more months must be active for a %FREQUENCY% frequency.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Un mois au moins doit être actif pour une frequence %FREQUENCY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein oder mehrere Monate müssen für eine %FREQUENCY% -Häufigkeit aktiv sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe estar activo al menos uno o más meses para una frecuencia de %FREQUENCY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un ou plusieurs mois doivent être actifs pour une fréquence %FREQUENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moeten ten minste een of meer maanden actief zijn voor een %FREQUENCY% frequentie")); }

        // Actions
	};
}



